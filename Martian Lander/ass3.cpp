/*******************************************************************************************************************************************
Filename: ass3.cpp
Version: 1.0
Author: Xingyi Wu
Student No: 040 887 028
Course Name/Number: CST8233 Numerical Computing
Lab Sect: 304
Assignment #: 3
Assignment name: Martian Lander
Due Date: Sun 02 December 2018
Submission Date: Sun 02 December 2018
Professor: Andrew Tyler
Purpose: Solve Ordinary differential Equations (ODEs) in real-time for a planetary lander flight simulator.
*******************************************************************************************************************************************/
#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

void calc();
void readFile();

class game {
	string name;
	int mins;
	int secs;
	int mils;
	int num_bounce;

public: 
	/* default constructor */
	game(string a, int b, int c, int d, int e) : name (a), mins(b), secs(c), mils(d), num_bounce(e){}

	/* compare with each users bounce and time to see whose record is the best */
	int differencemins(game &ob)
	{
		int diff = ob.num_bounce - this->num_bounce;
		if (diff == 0) {
			diff = ob.mins - this->mins;
			if (diff == 0) {
				diff = ob.secs - this->secs;
			}if (diff == 0) {
				diff = ob.mils - this->mils;
			}
		}
		return diff;
	}

	/* print username and conresponding records */
	void display() {
	    cout << name << "\t"<< setw(17) << mins << setw(20) << secs << setw(18) << mils << setw(20) << num_bounce << endl;
	}
};

/*****************************************************************************************************************************
Function Name: main
Purpose: main menu and call assocated functions
In parameters: none
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
int main() {
	char selection;
	bool running = true;
	while (running)
	{
		cout << "MENU\n 1. repeat the simulation\n 2. Quit\n" << endl;
		cin >> selection;

		switch (selection)
		{
		case '1':
			calc();
			break;
		
		case '2':
			running = false;
			readFile();
			break;
		default:
			break;
		}
	}
	return 0;
}

/*****************************************************************************************************************************
Function Name: calc
Purpose: to calculate the velocity, time and distance by differential equations formula
In parameters: none
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
void calc() {

	double previous = GetTickCount(); // ending time
	double current, delta, delta_ms, totalTime = 0; // gaming time
	double g = 3.7, c = 0.13, a = 8.3, vmax = 46; // constance value 
	double dvt, dvt1 =0; // result of step 1 differential equations formula
	double v = 0; // velocity
	double v1 = 0; // derivative of velocity
	double x = 1000; // distance to the surface
	double B = 0; // burn fuel
	double BR = 100; // burn reserve
	int key=0, oneKey = 0; // keyboards
	bool burnout = true; // to check fuel burning 
	bool running = true; // to check game is running
	int bounce =0; // number of bounces 
	bool header = true; // to control header is printed
	string username; // string user name 

	/* loop till landed */
	while (running)
	{
		current = GetTickCount(); 
		delta = current - previous;
		delta_ms = delta / 1000;
		totalTime += delta;

		/* differential equations formular 
		 * dv/dt = g – c*(v + a*(v/vmax)3) – B
         * v = dx/dt
		*/
	    dvt = g - c * (v + a* pow((v / vmax), 3)) - B; // g
		v1 = v + dvt * delta_ms; // y'
		dvt1 = g - c * (v1 + a* pow((v1 / vmax), 3)) - B; //g'
		v = v + (dvt + dvt1) / 2 * delta_ms; // y
		x = x - (v + v1) / 2 * delta_ms;

		/* if keyboard: W and E to control the fuel burn */
		if (_kbhit()) {

			key = _getch();
			
			switch (key) {
			case 'w': 
				if (burnout) B += 1; // increase burning fuel 
				oneKey = key;
				header = false;
			    break;

			case 'e': 
				if (B > 0) B -= 1; // decrese burning fuel 
				oneKey = key;
				header = false;
				break;

			case 'q':
				running = false; // exit
				oneKey = key;
				break;

			default:
				key = oneKey;  // other key are not working 
				break;
			}
		}

		/* if burning fuel */
		if (burnout) {
			/* burn reserved is less than zero */
			if (BR <= 0) {
				burnout = false;
				BR = 0;
				B = 0;
			}
			else if (B >0 && BR >0) {
				if (key == 'w') {
					cout << "W was pressed - increase burn: ";
				}
				else if ( key == 'e'){
					cout << "E was pressed - decrease burn: ";
				}
				/* burn reserve is decreased by time */
				BR -= ( B * delta_ms);
			}
			else if (key == 'e') {
				cout << "E was pressed - decrease burn: ";
			}
		}

		/* if win the game */ 
		if ( x >= 0 && x < 1 && v >=0 && v < 1 ) {
			running = false;
			system("CLS");
			cout << "User name:";
			cin >> username;
			cout << endl;

			/* save each users records to a file "result.txt" */
			ofstream outfile;
			outfile.open("result.txt", ios::app);
			outfile << username << " " << ((int)totalTime / 1000 / 60) << " " << ((int)totalTime / 1000 % 60) << " " << (int)totalTime % 1000 << " " << bounce;
			outfile.close();
		}

		/* if bouncing, velocity turns negative */
		if (x <= 0) {
			if (v > 1) {
				bounce++;
				v = v*(-1);
			}
		}
		
		/* print the header when game is initiated */
		if (header) 
		cout << "******************************* STARTING DESCENT **************************************" << endl;
		
		/* print all running records  */
		cout << ": BURN = " << setprecision(3) << fixed << B << "; BURN RESERVE = " << BR << endl;
		cout << "MINUTE = " << ((int)totalTime / 1000 / 60) << "; SECOND = " << ((int)totalTime / 1000 % 60) << "; MILLISECOND = " << (int)totalTime%1000 << endl;
		cout << "SPEED OF DESCENT = " << v << "m/s" << endl;
		cout << "HEIGHT ABOVE MARTIAN SURFACE = " << x << "meters" << endl;
		cout << "NUMBER OF BOUNCES = " << bounce << endl;

		Sleep(50);

		system("CLS"); // clean the screen 
		
		/* set current time back to previous time */
		previous = current;
	}
}

/*****************************************************************************************************************************
Function Name: readFile
Purpose: to read in the records from the file "result.txt" and sort each record and print in order of the best-to-worst 
In parameters: none
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*****************************************************************************************************************************/
void readFile() {

	system( "CLS");

	vector<game> ob; // vector to store each user record 
	ifstream myFile; // readin file 
	string temp_name; // temporary username 
	int temp_mins, temp_secs, temp_mils, temp_bounce = 0; // temporary game records

	// open the file
	myFile.open("result.txt", ifstream::in);

	// read-in file and store each record
	if (myFile.is_open()) {
		while (!myFile.eof()) {
			myFile >> temp_name >> temp_mins >> temp_secs >> temp_mils >> temp_bounce;
			ob.emplace_back(temp_name, temp_mins, temp_secs, temp_mils, temp_bounce);
		}
	}
	// close file
	myFile.close();

	/* bubble sort */
	for (int i = 0; i < (signed)ob.size() - 1; i++)
	{
		for (int j = 0; j < (signed)ob.size() - i - 1; j++)
		{
			if (ob[j].differencemins(ob[j+1]) < 0)
			{
				game temp = ob[j];
				ob[j] = ob[j+1];
				ob[j+1] = temp;
			}
		}
	}

	/* display the best-to-worst */
	cout << "\n************************************************Top ranking**********************************************" << endl;
	cout << "\nName\t" << setw(20) <<"Minutes" << setw(20) << "Seconds" << setw(20) << "Milliseconds" << setw(20) << "Bounce_Number" << endl;
	for (int k = 0; k < (signed)ob.size(); k++) {
		ob[k].display();
	}
}

