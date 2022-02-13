#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>

auto palette(int i, int max_i) {
    static const auto characters = " .:-=+*#%@";
    i = std::clamp(i, 0, max_i);
    int index = (i * 9) / max_i;
    if (!(index < 10 && index >= 0)) {
        std::cout << index << "\n";
        std::cout << i << "\n";
        exit(0);
    }
    return characters[index];
}

auto upward_shift(int i, int max_i) {
    return sqrt(i) * sqrt(max_i);
}

auto log_shift(int i) {
    return log(i) * 145.0;
}

auto mandlebrot(size_t xdim, size_t ydim) {

    constexpr int max_iteration = 1000;
    std::vector<int> iter_counts;
    iter_counts.reserve(xdim * ydim);

    for (size_t ypos = 0; ypos < ydim; ypos++) {
        std::cout << "|";
        for (size_t xpos = 0; xpos < xdim; xpos++) {
            const double x0 = (double)xpos / (double)xdim * 3.5 - 2.5;
            const double y0 = (double)ypos / (double)ydim * 2.0 - 1.0;

            double x = 0;
            double y = 0;

            int iteration = 0;
            while (x * x + y * y <= 2 * 2 && iteration < max_iteration) {
                double xtemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtemp;
                iteration++;
            }
            iter_counts.push_back(iteration);
            char color = palette(log_shift(iteration) /*upward_shift(iteration, max_iteration)*/, max_iteration);
            // plot(Px, Py, color);
            std::cout << color;
        }
        std::cout << "|\n";
    }
    std::ranges::sort(iter_counts);
    auto max_count = *std::ranges::max_element(iter_counts);
    auto min_count = *std::ranges::min_element(iter_counts);
    auto avg_count = std::accumulate(iter_counts.begin(), iter_counts.end(), 0) / iter_counts.size();
    auto median = iter_counts[iter_counts.size() / 2];
    std::cout << "max: " << max_count << "\n";
    std::cout << "min: " << min_count << "\n";
    std::cout << "avg: " << avg_count << "\n";
    std::cout << "med: " << median << "\n";
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        mandlebrot(48, 16);
        // mandlebrot(1200, 300); // biggest possible zoom on windows terminal 1200 300
    } else if (argc == 3) {
        mandlebrot(atol(argv[1]), atol(argv[2]));
    }
    return 0;
}
