#include "Histogram.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

// I find the range and bin width before counting the values.
std::vector<HistogramBin> Histogram::build(
    const std::vector<double>& data,
    std::size_t binCount
) {
    if (data.empty()) {
        throw std::invalid_argument("Histogram requires at least one data value.");
    }

    if (binCount == 0) {
        throw std::invalid_argument("Histogram bin count must be greater than zero.");
    }

    // Non-finite values make range and bin-index calculations unreliable.
    for (double value : data) {
        if (!std::isfinite(value)) {
            throw std::invalid_argument("Histogram values must be finite.");
        }
    }

    double minValue = *std::min_element(data.begin(), data.end());
    double maxValue = *std::max_element(data.begin(), data.end());

    if (minValue == maxValue) {
        std::vector<HistogramBin> bins;
        bins.push_back(HistogramBin(minValue, maxValue, data.size()));
        return bins;
    }

    double binWidth = (maxValue - minValue) / static_cast<double>(binCount);

    std::vector<HistogramBin> bins;
    bins.reserve(binCount);

    for (std::size_t i = 0; i < binCount; ++i) {
        double lower = minValue + static_cast<double>(i) * binWidth;
        double upper = (i == binCount - 1)
            ? maxValue
            : minValue + static_cast<double>(i + 1) * binWidth;

        bins.push_back(HistogramBin(lower, upper, 0));
    }

    // A value on the final boundary must still count in the last bin.
    for (double value : data) {
        std::size_t index = static_cast<std::size_t>(
            (value - minValue) / binWidth
        );

        if (index >= binCount) {
            index = binCount - 1;
        }

        ++bins[index].count_;
    }

    return bins;
}
