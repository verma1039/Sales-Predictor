#include "LinearRegression.h"
#include <iostream>
#include <numeric>  // for std::accumulate
#include <cmath>    // for std::pow

// Constructor
LinearRegression::LinearRegression() : slope(0.0), intercept(0.0), trained(false) {}

// Train the model (Calculate m and c)
void LinearRegression::fit(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        std::cerr << "Error: Training data dimensions do not match!" << std::endl;
        return;
    }

    double n = static_cast<double>(x.size());
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_xx = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
    }

    double numerator = (n * sum_xy) - (sum_x * sum_y);
    double denominator = (n * sum_xx) - (sum_x * sum_x);

    if (denominator == 0) {
        std::cerr << "Error: Denominator is zero. Cannot fit model." << std::endl;
        return;
    }

    slope = numerator / denominator;
    intercept = (sum_y - (slope * sum_x)) / n;
    trained = true;
}

// Predict single value
double LinearRegression::predict(double x) const {
    if (!trained) {
        std::cerr << "Warning: Model not trained." << std::endl;
        return 0.0;
    }
    return (slope * x) + intercept;
}

// Predict vector
std::vector<double> LinearRegression::predict(const std::vector<double>& x) const {
    std::vector<double> preds;
    if (!trained) return preds;
    
    preds.reserve(x.size());
    for (double val : x) {
        preds.push_back(predict(val));
    }
    return preds;
}

// Calculate R^2 Score
double LinearRegression::score(const std::vector<double>& x, const std::vector<double>& y_true) const {
    if (!trained) return 0.0;
    
    double n = static_cast<double>(y_true.size());
    double mean_y = std::accumulate(y_true.begin(), y_true.end(), 0.0) / n;

    double ssr = 0.0; // Residual sum of squares
    double sst = 0.0; // Total sum of squares

    for (size_t i = 0; i < n; ++i) {
        double y_pred = predict(x[i]);
        ssr += std::pow(y_true[i] - y_pred, 2);
        sst += std::pow(y_true[i] - mean_y, 2);
    }

    if (sst == 0) return 0.0;
    return 1.0 - (ssr / sst);
}

// Print Equation
void LinearRegression::printEquation() const {
    if(trained) {
        std::cout << ">>> Model Equation: Sales = " << slope << " * (Ad Spend) + " << intercept << std::endl;
    }
}