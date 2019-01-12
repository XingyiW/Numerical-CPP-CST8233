/*******************************************************************************************************************************************
Filename: ass1.cpp
Version: 1.0
Author: Xingyi Wu
Student No: 040 887 028
Course Name/Number: CST8233 Numerical Computing
Lab Sect: 304
Assignment #: 1
Assignment name: Cantenary Function
Due Date: Sun 14 October 2018
Submission Date: Sat 13 October 2018
Professor: Andrew Tyler
Purpose: Investigate a Maclaurin series approximation to the Catenary function.
*******************************************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

/***********************************************************************************
Function Name: main
Purpose: The catenary function (the inverted arch) is a hyperbolic cosine 
         function that can be written as a combination of exponentials :
         y = a cosh(x/a) = a(e^(x/a) + e^(-x/a))/2
In parameters: void
Out parameters: none
Version: 1.0
Author: Xingyi Wu
***********************************************************************************/
int main(void) {

	int option; /* menu option variable */

	/* loop menu until quit (2) */
	do {
		cout << "**********************************\n\t Catenary Series \t\n1. Evaluate the function\n2. Quit\n**********************************\n";
		cin >> option;

		/* evaluate the catenary function */
		if (option == 1)
		{
			int power = 0;                 /* power of x */
			double low_x = 0.0;            /* low value of x */
			double high_x = 0.0;           /* high value of x */
			double a = 0.0;                /* value of scale factor */
			double x = 0.0;                /* value of x */
			double y = 0.0;                /* value of series*/
			double num[20];                /* array to hold each term */
			double t = 0.0;                /* value of truncate*/
			double truncate_error = 0.0;   /* value of truncate error */
			double exact_value = 0.0;      /* exact value calculated by math lib */

			/* input value for power of x */
			cout << "\tEVALUATING THE CATENARY SERIES APPROXIMATION\n\n";
			cout << "Please enter the highest power of x in the catenary series (0, 2, 4, 6, 8, or 10): ";
			while (!(cin >> power) || power < 0 || power>10 || power % 2 != 0) {
				cout << "Invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			/* input value for low x */
			cout << "Please enter low x - in the range -10.0 to 0.0: ";
			while (!(cin >> low_x) || low_x < -10.0 || low_x > 0.0) {
				cout << "Invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			/* input value for high x */
			cout << "Please enter high x - in the range 0.0 to +10.0: ";
			while (!(cin >> high_x) || high_x < 0.0 || high_x > +10.0) {
				cout << "Invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			/* input value for scale factor */
			cout << "\nPlease enter the scale factor the range 0.0 to +10.0: ";
			while (!(cin >> a) || a < 0.0 || a > +10.0) {
				cout << "Invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cout << fixed;
			cout.precision(6);
			cout << "\nCATENARY SERIES TO x^" << power << " from x = " << setprecision(6) << low_x << " to x = " << setprecision(6) << high_x << endl;
			cout << "  x\t\t Series\t\t  Exact\t\tExact % Error\tTrunc. % Error\n";

			cout << scientific;
			cout.precision(6);

			/* calucation for series, exact value, the margin of exact error and the margin of truncate error  */
			for (int i = 0; i <= 10; i++) {
				int temp = power;
				y = 0.0;
				x = low_x + (((high_x - low_x) / 10) * i);

				/* value of loop times based on power of x */
				int n = power / 2; 
				for (int k = 0; k <= n; k++) {
					/* series calculation */
					switch (temp) {
					case 0: num[k] = a * 1; break;
					case 2: num[k] = a *(((x / a)*(x / a)) / (2 * 1)); break;
					case 4: num[k] = a *(((x / a)*(x / a)*(x / a)*(x / a)) / (4 * 3 * 2 * 1)); break;
					case 6: num[k] = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (6 * 5 * 4 * 3 * 2 * 1)); break;
					case 8: num[k] = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)); break;
					case 10: num[k] = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)); break;
					case 12: num[k] = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (12 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)); break;
					}
					y += num[k];
					temp = temp - 2;
				}

				/* truncate calculation */
				switch (power) {
				case 0: t = a *(((x / a)*(x / a)) / (2 * 1)); break;
				case 2: t = a *(((x / a)*(x / a)*(x / a)*(x / a)) / (4 * 3 * 2 * 1)); break;
				case 4: t = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (6 * 5 * 4 * 3 * 2 * 1)); break;
				case 6: t = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)); break;
				case 8: t = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)); break;
				case 10: t = a *(((x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)*(x / a)) / (12 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)); break;
				}

				truncate_error = 100 * t / y;
				exact_value = (a * (exp(x / a) + exp(-(x / a)))) / 2;

				cout << setprecision(3) << showpos << x << "\t " << setprecision(5) << noshowpos << y << "\t " << exact_value << "\t " << 100 * (exact_value - y) / exact_value << "\t " << truncate_error << endl;
			}
		}
		else {
			cout << "Please enter a valid option\n";
			cout << "\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (option != 2);
	return 0;
}
