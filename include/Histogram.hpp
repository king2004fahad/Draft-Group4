#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <cstddef>
#include <vector>

// A histogram divides numerical values into groups called bins.
// Each bin stores its lower limit, upper limit, and number of values.
struct HistogramBin {
public:
    HistogramBin(const HistogramBin&) = default;
    HistogramBin(HistogramBin&&) noexcept = default;
    HistogramBin& operator=(const HistogramBin&) = delete;
    HistogramBin& operator=(HistogramBin&&) = delete;

    double lower() const noexcept { return lower_; }
    double upper() const noexcept { return upper_; }
    std::size_t count() const noexcept { return count_; }

private:
    friend class Histogram;

    HistogramBin(double lower, double upper, std::size_t count)
        : lower_(lower), upper_(upper), count_(count) {}

    double lower_;
    double upper_;
    std::size_t count_;
};

class Histogram {
public:
    // The rest of the library will use this public interface.
    static std::vector<HistogramBin> build(
        const std::vector<double>& data,
        std::size_t binCount = 10
    );
};

#endif
