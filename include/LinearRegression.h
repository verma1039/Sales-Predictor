#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

class LinearRegression {
private:
    double slope;
    double intercept;
    bool trained;

public:
    LinearRegression();

    void fit(const std::vector<double>& x, const std::vector<double>& y);
    double predict(double x) const;
    double r2_score(const std::vector<double>& x, const std::vector<double>& y) const;
    double mae(const std::vector<double>& x, const std::vector<double>& y) const;
    double rmse(const std::vector<double>& x, const std::vector<double>& y) const;
};

#endif
