[1] SYSTEM REQUIREMENTS

To run this project, your computer must have a C++ compiler installed.

Windows Users:

You need "MinGW-w64" or "G++".

If not installed, download "MSYS2" from https://www.msys2.org/

Install the toolchain using the MSYS2 terminal:
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain

Mac Users:

Open Terminal and type: xcode-select --install

Linux Users:

Open Terminal and type: sudo apt install g++

[2] PROJECT FILES

Ensure all three files are in the same folder:

main.cpp             (The user interface and input handler)

LinearRegression.cpp (The math and logic implementation)

LinearRegression.h   (The header/definition file)

[3] HOW TO RUN (Step-by-Step)

Open your Terminal or Command Prompt (or VS Code Terminal).

Navigate (cd) to the folder containing these files.

COMPILE:
Copy and paste the following command to build the application:

g++ main.cpp LinearRegression.cpp -o sales_app

(If successful, a new file named 'sales_app.exe' will appear).

RUN:
Type the following command to start the program:

./sales_app

[4] HOW TO USE THE APP

When the program starts, it will ask for the number of historical
data records you possess (e.g., enter '5').

Enter the data pairs in the format: [Ad Spend] [Sales]

Example Data for testing:
Record 1: 23 651
Record 2: 26 762
Record 3: 30 856
Record 4: 34 1063
Record 5: 43 1190

The Model will train and show you the Accuracy Score.

Finally, enter a "Planned Ad Spend" (e.g., 50) to see the
predicted sales volume.