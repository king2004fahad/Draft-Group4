#include "Histogram.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>
int main() {
    auto bins = Histogram::build({1, 2, 3, 4}, 2);
    assert(bins.size() == 2);
    assert(bins[0].count() == 2 && bins[1].count() == 2);
    auto same = Histogram::build({5, 5, 5}, 4);
    assert(same.size() == 1 && same[0].count() == 3);
    bool threw = false;
    try { Histogram::build({1, 2}, 0); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    threw = false;
    try { Histogram::build({1, std::numeric_limits<double>::infinity()}, 2); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    std::cout << "Histogram tests passed.\n";
}