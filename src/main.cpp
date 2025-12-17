#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include "LinearRegression.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: sales_app <data.csv>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::vector<double> x, y;
    std::string line;

    // Read CSV
    while (getline(file, line)) {
        std::stringstream ss(line);
        double a, b;
        char comma;
        if (ss >> a >> comma >> b) {
            x.push_back(a);
            y.push_back(b);
        }
    }

    if (x.size() < 2) {
        std::cerr << "Error: Not enough data points.\n";
        return 1;
    }

    // Shuffle data
    std::vector<size_t> indices(x.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::mt19937 rng(42);
    std::shuffle(indices.begin(), indices.end(), rng);

    std::vector<double> x_shuffled, y_shuffled;
    for (size_t i : indices) {
        x_shuffled.push_back(x[i]);
        y_shuffled.push_back(y[i]);
    }

    // Train/Test split (80/20)
    size_t split = static_cast<size_t>(0.8 * x_shuffled.size());
    std::vector<double> x_train(x_shuffled.begin(), x_shuffled.begin() + split);
    std::vector<double> y_train(y_shuffled.begin(), y_shuffled.begin() + split);
    std::vector<double> x_test(x_shuffled.begin() + split, x_shuffled.end());
    std::vector<double> y_test(y_shuffled.begin() + split, y_shuffled.end());

    // Train model
    LinearRegression model;
    model.fit(x_train, y_train);

    // Training range
    auto minmax = std::minmax_element(x_train.begin(), x_train.end());
    double min_train = *minmax.first;
    double max_train = *minmax.second;

    std::cout << "\nValid Ad Spend Range: "
              << min_train << " to " << max_train << std::endl;

    // Metrics
    std::cout << "\n--- Training Metrics ---\n";
    std::cout << "R2   : " << model.r2_score(x_train, y_train) << std::endl;
    std::cout << "MAE  : " << model.mae(x_train, y_train) << std::endl;
    std::cout << "RMSE : " << model.rmse(x_train, y_train) << std::endl;

    std::cout << "\n--- Testing Metrics ---\n";
    std::cout << "R2   : " << model.r2_score(x_test, y_test) << std::endl;
    std::cout << "MAE  : " << model.mae(x_test, y_test) << std::endl;
    std::cout << "RMSE : " << model.rmse(x_test, y_test) << std::endl;

    // Prediction loop
    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        double spend;
        std::cout << "\nEnter planned ad spend: ";
        std::cin >> spend;

        if (spend < min_train || spend > max_train) {
            std::cout << "[Warning] Ad spend is outside training range.\n"
                      << "Prediction is an extrapolation and may be unreliable.\n";
        }

        std::cout << "Predicted Sales: "
                  << model.predict(spend) << std::endl;

        std::cout << "Check again? (y/n): ";
        std::cin >> choice;
    }

    std::cout << "Exiting application.\n";
    return 0;
}
