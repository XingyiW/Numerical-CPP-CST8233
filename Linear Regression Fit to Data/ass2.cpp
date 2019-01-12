/*******************************************************************************************************************************************
Filename: ass1.cpp
Version: 1.0
Author: Xingyi Wu
Student No: 040 887 028
Course Name/Number: CST8233 Numerical Computing
Lab Sect: 304
Assignment #: 2
Assignment name: Linear Regression Fit to Data 
Due Date: Sun 11 November 2018
Submission Date: Sun 11 November 2018
Professor: Andrew Tyler
Purpose: Fit data using linear regression least squares method for both a Linear function and a Power Law function. 
*******************************************************************************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;
void readFile(int& a, vector<double> &b, vector <double> &c);
void power_law(int a, vector<double> x, vector<double> y);
void linear(int a, vector<double> x, vector<double> y);

/*****************************************************************************************************************************
Function Name: main
Purpose: main menu and call assocated functions
In parameters: void
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
int main(void) {

	int counter ;
	char selection;
	bool running = true;

	while (running)
	{
		counter = 0;
		vector<double> x;
		vector <double> y;

		cout << "\tLEAST_SQUARES LINEAR REGRESSION\nMENU\n 1. Linear Fit\n 2. Power Law Fit\n 3. Quit\n" << endl;
		cin >> selection;

		switch (selection)
		{
		case '1':
			readFile(counter, x, y);
			linear(counter, x, y);
			break;
		case '2':
			readFile(counter, x, y);
			power_law(counter, x, y);
			break;
		case '3':
			running = false;
			break;
		}
	}
	return 0;
}

/*****************************************************************************************************************************
Function Name: readFile
Purpose: to open and read a file 
In parameters: int& a, vector<double> &b, vector <double> &c
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
void readFile(int& a, vector<double> &b, vector <double> &c) {

	double year;
	double level;
	ifstream myFile;
	string fileName;

	cout << "Please enter the name of the file to open:";
	cin >> fileName;

	// open the file
	myFile.open(fileName, ifstream::in);

	if (myFile.is_open()) {
		while (!myFile.eof()) {
			// read the first column
			myFile >> year;
			// append each readin value to a vector
			b.emplace_back(year);
			// read the second column
			myFile >> level;
			// append each readin value to a vector
			c.emplace_back(level);
			a++;
		}
		cout << "There are " << a << " records." << endl;
	}
	// close file
	myFile.close();
}

/*****************************************************************************************************************************
Function Name: sum_x
Purpose: to iterator the first column of file which is the value of x and sum
In parameters: vector<double> x
Out parameters: double sum_year
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_x(vector<double> x) {
	double sum_year = 0;
	for (vector<double> ::iterator it = x.begin(); it != x.end(); it++) {
		sum_year += *it;
	}
	return sum_year;
}

/*****************************************************************************************************************************
Function Name: sum_lnx
Purpose: to iterator the first column of file which is the value of x and sum log(x)
In parameters: vector<double> x
Out parameters: double sum_lnyear
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_lnx(vector<double> x) {
	double sum_lnyear = 0;
	for (vector<double> ::iterator it = x.begin(); it != x.end(); it++) {
		sum_lnyear += log(*it);
	}
	return sum_lnyear;
}

/*****************************************************************************************************************************
Function Name: sum_y
Purpose: to iterator the second column of file which is the value of y and sum
In parameters: vector<double> y
Out parameters: double sum_level
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_y(vector<double> y) {
	double sum_level = 0;
	for (vector<double> ::iterator it = y.begin(); it != y.end(); it++) {
		sum_level += *it;
	}
	return sum_level;
}

/*****************************************************************************************************************************
Function Name: sum_lny
Purpose: to iterator the first column of file which is the value of x and sum log(y)
In parameters: vector<double> y
Out parameters: double sum_lnlevel
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_lny(vector<double> y) {
	double sum_lnlevel = 0;
	for (vector<double> ::iterator it = y.begin(); it != y.end(); it++) {
		sum_lnlevel += log(*it);
	}
	return sum_lnlevel;
}

/*****************************************************************************************************************************
Function Name: sum_xx
Purpose: to iterator the first column of file which is the value of x and sum x^2
In parameters: vector<double> x
Out parameters: double sum_years
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_xx(vector<double> x) {
	double sum_years = 0;
	for (vector<double> ::iterator it = x.begin(); it != x.end(); it++) {
		sum_years += pow(*it,2);
	}
	return sum_years;
}

/*****************************************************************************************************************************
Function Name: sum_lnxx
Purpose: to iterator the first column of file which is the value of x and sum (log(x))^2
In parameters: vector<double> x
Out parameters: double sum_lnyears
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_lnxx(vector<double> x) {
	double sum_lnyears = 0;
	for (vector<double> ::iterator it = x.begin(); it != x.end(); it++) {
		sum_lnyears += pow(log(*it), 2);
	}
	return sum_lnyears;
}

/*****************************************************************************************************************************
Function Name: sum_xy
Purpose: to iterator the first column of file which is the value of x and sum (x*y)
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double sum_xMy
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_xy(int a, vector<double> x, vector<double> y) {
	double sum_xMy = 0;

	for (int i = 0; i < a; i++) {
		sum_xMy += x[i] * y[i];
	}
	return sum_xMy;
}

/*****************************************************************************************************************************
Function Name: sum_lnxy
Purpose: to iterator the first column of file which is the value of x and sum (log(x)*log(y))
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double sum_lnxMlny
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double sum_lnxy(int a, vector<double> x, vector<double> y) {
	double sum_lnxMlny = 0;

	for (int i = 0; i < a; i++) {
		sum_lnxMlny += log(x[i]) * log(y[i]);
	}
	return sum_lnxMlny;
}

/*****************************************************************************************************************************
Function Name: delta
Purpose: delta = counter*Sxx - (Sx)^2
In parameters: int a, vector<double> x
Out parameters: double d
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double delta(int a, vector<double> x) {
	double d;
	return d = (a * (sum_xx(x))) - pow(sum_x(x), 2);
}

/*****************************************************************************************************************************
Function Name: delta_ln
Purpose: delta = counter*S((lnx)^2) - (Slnx)^2
In parameters: int a, vector<double> x
Out parameters: double d
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double delta_ln(int a, vector<double> x) {
	double d;
	return d = (a * (sum_lnxx(x))) - pow(sum_lnx(x), 2);
}

/*****************************************************************************************************************************
Function Name: m
Purpose: double m = (SSxy - SxSy) / delta
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double m
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double m(int a, vector<double> x, vector<double> y) {
	double result_m;
	return result_m = ((a * (sum_xy(a, x, y))) - ((sum_x(x)) * (sum_y(y)))) / delta(a, x);
}

/*****************************************************************************************************************************
Function Name: m_ln
Purpose: double m_ln = (SS(lnx*lny) - S(lnx)S(lny)) / delta
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double result_m_ln
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double m_ln(int a, vector<double> x, vector<double> y) {
	double result_m_ln;
	return result_m_ln = ((a * (sum_lnxy(a, x, y))) - ((sum_lnx(x)) * (sum_lny(y)))) / delta_ln(a, x);
}

/*****************************************************************************************************************************
Function Name: c
Purpose: c = (SxxSy - SxSxy) /delta
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double result_c
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double c(int a, vector<double> x, vector<double> y) {
	double result_c;
	return result_c = (((sum_xx(x)) * (sum_y(y))) - ((sum_x(x))*(sum_xy(a, x, y)))) / delta(a, x);
}

/*****************************************************************************************************************************
Function Name: c_ln
Purpose: c = (S(lnx*lnx)Slny - SlnxS(lnx*lny)) /delta
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double result_c_ln
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double c_ln(int a, vector<double> x, vector<double> y) {
	double result_c_ln;
	return result_c_ln = (((sum_lnxx(x)) * (sum_lny(y))) - ((sum_lnx(x))*(sum_lnxy(a, x, y)))) / delta_ln(a, x);
}

/*****************************************************************************************************************************
Function Name: power_law_a
Purpose: a = e^c_ln
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double result_a
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
double power_law_a(int a, vector<double> x, vector<double> y) {
	double result_a;
	return result_a = exp(c_ln(a,x,y));
}

/****************************************************************************************************************************************
Function Name: predict_powerLaw
Purpose: predict in power law, offer the user the option of interpolating/ extrapolating the databy including 
         the (1960, 316.5) offsets to the formula you calculate.
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double result_input
Version: 1.0
Author: Xingyi Wu
****************************************************************************************************************************************/
void predict_powerLaw(int a, vector<double> x, vector<double> y) {
	int input_x;
	double result_input;
	do {
		cout << "Please enter the year to interpolate/extrapolate to: ";
	} while (!(cin >> input_x));
	
	result_input = (power_law_a(a, x, y) * pow((input_x - 1960), m_ln(a, x, y))) + 316.5;

	cout << "The power law interpolated/extrapolated CO2 level in the year " << setprecision(1) <<(double)input_x << setprecision(2) << " is " << result_input << endl;

}

/****************************************************************************************************************************************
Function Name: predict_Linear
Purpose: predict in linear, offer the user the option of interpolating/ extrapolating the databy including
         the (1960, 316.5) offsets to the formula you calculate.
In parameters: int a, vector<double> x, vector<double> y
Out parameters: double result_input
Version: 1.0
Author: Xingyi Wu
****************************************************************************************************************************************/
void predict_Linear(int a, vector<double> x, vector<double> y) {
	int input_x;
	double result_input;
	do {
		cout << "Please enter the year to interpolate/extrapolate to: ";
	} while (!(cin >> input_x));

	result_input = (m(a, x, y) * (input_x - 1960) + c(a, x, y)) + 316.5;

	cout << "The linear interpolated/extrapolated CO2 level in the year " << setprecision(1) << (double) input_x << setprecision(2) << " is " << result_input << endl;

}

/****************************************************************************************************************************************
Function Name: power_law
Purpose: secondary menu to choose the prediction by power_law formular or back to main menu
In parameters: int a, vector<double> x, vector<double> y
Out parameters: none
Version: 1.0
Author: Xingyi Wu
****************************************************************************************************************************************/
void power_law(int a, vector<double> x, vector<double> y) {
	cout<< fixed;
	cout.precision(2);
	cout << "y = " <<  power_law_a(a, x, y) << "x^" <<  m_ln(a, x, y) << endl;

	char selection;
	bool running = true;
	while (running)
	{
		cout << "MENU\n 1. Interpolate/Extrapolate\n 2. Main Menu\n " << endl;
		cin >> selection;

		switch (selection)
		{
		case '1':
			predict_powerLaw(a, x, y);
			break;
		case '2':
			running = false;
			break;
		}
	}
}

/****************************************************************************************************************************************
Function Name: linear
Purpose: secondary menu to choose the prediction by linear formular or back to main menu
In parameters: int a, vector<double> x, vector<double> y
Out parameters: none
Version: 1.0
Author: Xingyi Wu
****************************************************************************************************************************************/
void linear(int a, vector<double> x, vector<double> y) {
	cout << fixed;
	cout.precision(2);
	cout << "y = " << m(a, x, y) << " *x + " << c(a, x, y) << endl;

	char selection;
	bool running = true;
	while (running)
	{
		cout << "MENU\n 1. Interpolate/Extrapolate\n 2. Main Menu\n " << endl;
		cin >> selection;

		switch (selection)
		{
		case '1':
			predict_Linear(a, x, y);
			break;
		case '2':
			running = false;
			break;
		}
	}
}

