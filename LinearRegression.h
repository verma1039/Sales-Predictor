#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

/*
 * Class: LinearRegression
 * Interface definition for the regression model.
 */
class LinearRegression {
private:
    double slope;     // m
    double intercept; // c
    bool trained;     // Flag to ensure model is trained before prediction

public:
    // Constructor
    LinearRegression();

    // Train the model using vectors of X (Ad Spend) and Y (Sales)
    void fit(const std::vector<double>& x, const std::vector<double>& y);

    // Predict a single Y value given X
    double predict(double x) const;

    // Predict a list of Y values
    std::vector<double> predict(const std::vector<double>& x) const;

    // Calculate the R-squared accuracy score
    double score(const std::vector<double>& x, const std::vector<double>& y_true) const;

    // Display the mathematical equation
    void printEquation() const;
};

#endif