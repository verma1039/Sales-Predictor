#include "LinearRegression.h"
#include <cmath>
#include <numeric>

LinearRegression::LinearRegression()
    : slope(0.0), intercept(0.0), trained(false) {}

void LinearRegression::fit(const std::vector<double>& x, const std::vector<double>& y) {
    double n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
    }

    slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
    intercept = (sum_y - slope * sum_x) / n;
    trained = true;
}

double LinearRegression::predict(double x) const {
    return slope * x + intercept;
}

double LinearRegression::r2_score(const std::vector<double>& x, const std::vector<double>& y) const {
    double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
    double ssr = 0, sst = 0;

    for (size_t i = 0; i < y.size(); ++i) {
        ssr += std::pow(y[i] - predict(x[i]), 2);
        sst += std::pow(y[i] - mean_y, 2);
    }
    return 1.0 - (ssr / sst);
}

double LinearRegression::mae(const std::vector<double>& x, const std::vector<double>& y) const {
    double error = 0;
    for (size_t i = 0; i < y.size(); ++i)
        error += std::abs(y[i] - predict(x[i]));
    return error / y.size();
}

double LinearRegression::rmse(const std::vector<double>& x, const std::vector<double>& y) const {
    double error = 0;
    for (size_t i = 0; i < y.size(); ++i)
        error += std::pow(y[i] - predict(x[i]), 2);
    return std::sqrt(error / y.size());
}
