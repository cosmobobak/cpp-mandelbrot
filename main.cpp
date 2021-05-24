#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

auto palette(int i, int max_i) {
    static const auto characters = " .:-=+*#%@";
    i = std::min(i, max_i);
    i = std::max(i, 0);
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

auto mandlebrot(int xdim, int ydim) {
    // std::vector<std::vector<int>> counts(ydim, std::vector<int>(xdim));

    constexpr int max_iteration = 1000;

    for (size_t ypos = 0; ypos < ydim; ypos++) {
        std::cout << "|";
        for (size_t xpos = 0; xpos < xdim; xpos++) {
            double x0 = (double)xpos / (double)xdim * 3.5 - 2.5;
            double y0 = (double)ypos / (double)ydim * 2.0 - 1.0;

            double x = 0;
            double y = 0;

            int iteration = 0;
            while (x * x + y * y <= 2 * 2 && iteration < max_iteration) {
                double xtemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtemp;
                iteration++;
            }
            char color = palette(log_shift(iteration) /*upward_shift(iteration, max_iteration)*/, max_iteration);
            // plot(Px, Py, color);
            std::cout << color;
        }
        std::cout << "|\n";
    }
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        mandlebrot(48, 16);
        // mandlebrot(1200, 300); // biggest possible zoom on windows terminal
    } else if (argc == 3) {
        mandlebrot(atoi(argv[1]), atoi(argv[2]));
    }
    return 0;
}
