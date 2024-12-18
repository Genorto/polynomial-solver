#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

int getSign(double val, double eps) {
    if (val > eps) {
        return 1;
    } else if (val < -eps) {
        return -1;
    }
    return 0;
}

std::vector<std::pair<double, int>> getDerivative(std::vector<std::pair<double, int>> polynomial) {
    polynomial.pop_back();
    for (auto& au : polynomial) {
        au.first *= au.second;
        --au.second;
    }
    return polynomial;
}

double getValue(std::vector<std::pair<double, int>> polynomial, double x_val) {
    double result = 0;
    for (auto au : polynomial) {
        result += au.first * pow(x_val, au.second);
    }
    return result;
}

std::vector<double> getRoots(std::vector<std::pair<double, int>> polynomial,
    double a_lim, double b_lim, double eps) {
    std::vector<double> result;
    if (polynomial[0].second == 1) {
        double x_curr = -polynomial[1].first / polynomial[0].first;
        if (a_lim - eps <= x_curr && x_curr <= b_lim + eps) {
            result.push_back(x_curr);
        }
    } else {
        std::vector<double> extremes;
        extremes.push_back(a_lim);
        for (auto au : getRoots(getDerivative(polynomial), a_lim, b_lim, eps)) {
            extremes.push_back(au);
        }
        extremes.push_back(b_lim);
        for (int it = 0; it < static_cast<int>(extremes.size()) - 1; ++it) {
            double left = extremes[it], right = extremes[it + 1];
            int left_sign = getSign(getValue(polynomial, left), eps);
            int right_sign = getSign(getValue(polynomial, right), eps);
            if (left_sign * right_sign >= 0) {
                if (left_sign == 0) {
                    result.push_back(left);
                } else if (right_sign == 0) {
                    result.push_back(right);
                }
                continue;
            }
            while (right - left >= eps) {
                double mid = (left + right) / 2;
                if (left_sign * getSign(getValue(polynomial, mid), eps) > 0) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            result.push_back((left + right) / 2);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

int main() {
    int num;
    std::cin >> num;
    std::vector<std::pair<double, int>> polynomial;
    for (int it = num; it >= 0; --it) {
        double multiplier;
        std::cin >> multiplier;
        polynomial.push_back({ multiplier, it });
    }
    double a_lim, b_lim, eps = 0.000000001;
    std::cin >> a_lim >> b_lim;
    b_lim -= eps;
    std::vector<double> result = getRoots(polynomial, a_lim, b_lim, eps);
    for (auto au : result) {
        std::cout << std::fixed << std::setprecision(6) << au << " ";
    }
}
