#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "LinearRegression.h"

int main() {
    std::vector<double> ad_spend;
    std::vector<double> sales;
    int data_count = 0;

    std::cout << "============================================" << std::endl;
    std::cout << "      Sales Predictor (Linear Regression)   " << std::endl;
    std::cout << "============================================" << std::endl;

    // --- 1. Input Phase ---
    std::cout << "How many historical data records do you have? ";
    while(!(std::cin >> data_count) || data_count < 2) {
        std::cout << "Please enter a valid number (minimum 2 records needed): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\nEnter Historical Data:" << std::endl;
    std::cout << "(e.g., If you spent $1000 on ads and sold 500 units, enter: 1000 500)" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    for(int i = 0; i < data_count; ++i) {
        double x_val, y_val;
        std::cout << "Record " << (i + 1) << " [Ad Spend] [Sales]: ";
        std::cin >> x_val >> y_val;
        ad_spend.push_back(x_val);
        sales.push_back(y_val);
    }

    // --- 2. Training Phase ---
    std::cout << "\n[System] Training Sales Prediction Model..." << std::endl;
    LinearRegression model;
    model.fit(ad_spend, sales);
    model.printEquation();

    // --- 3. Evaluation Phase ---
    double r2 = model.score(ad_spend, sales);
    std::cout << "[System] Model Accuracy (R^2): " << std::fixed << std::setprecision(4) << r2 << std::endl;

    // --- 4. Prediction Phase ---
    std::cout << "\n============================================" << std::endl;
    std::cout << "           Interactive Prediction           " << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Enter a planned Ad Spend to see predicted Sales." << std::endl;
    std::cout << "Type -1 to exit." << std::endl;
    
    double user_spend;
    while(true) {
        std::cout << "\nPlanned Ad Spend ($): ";
        if(!(std::cin >> user_spend) || user_spend == -1) break;
        
        double predicted_sales = model.predict(user_spend);
        std::cout << ">> Predicted Sales Volume: " << std::setprecision(2) << predicted_sales << " units";
    }

    std::cout << "\nExiting Application..." << std::endl;
    return 0;
}