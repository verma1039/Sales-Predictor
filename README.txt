Sales Prediction using Linear Regression (C++)

This project implements linear regression from scratch to predict sales based on advertising spend.

Approach:
- Ordinary Least Squares linear regression
- 80/20 train-test split

Evaluation Metrics:
- R² Score
- Mean Absolute Error (MAE)
- Root Mean Squared Error (RMSE)

Usage:
g++ src/main.cpp src/LinearRegression.cpp -Iinclude -o sales_app
./sales_app data/sample.csv

Limitations:
- Single feature regression
- No external libraries
