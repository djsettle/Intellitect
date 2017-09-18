// Intellitect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

void linearRegression(double x[], double y[], int n) { // x is PH, y is ORP and n is number of values
	double sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0, a, b;
	for (int i = 0; i < n - 1; i++) {
		sumx += x[i];
		sumx2 += (x[i] * x[i]);
		sumy += + y[i];
		sumxy += (x[i] * y[i]);
	}
	a = ((sumx2*sumy - sumx*sumxy) / (n*sumx2 - sumx*sumx)); // gradient
	b = ((n*sumxy - sumx*sumy) / (n*sumx2 - sumx*sumx)); // intercept

	cout.precision(9); // to show more precision
	cout << "Gradient = " << a << " & Intercept = " << b << endl;
}

int main()
{
	int time[2000];
	double pH[2000], ORP[2000];
	bool first = false;
	int count = 0, count2 = 0, inTime = 0;
	double phMax = 0.0, phMin = 1000.0, orpMax = 0.0, orpMin = 1000.0,
		phSum = 0.0, orpSum = 0.0, phMean = 0.0, orpMean = 0.0, phSD = 0.0, orpSD = 0.0;

	ifstream data("pH_ORP_data.csv"); // reads csv file
	string line;
	while (getline(data, line)) { // loops though each line of the file
		if (first) {
			stringstream lineStream(line);
			string cell;
			while (getline(lineStream, cell, ',')) { // parses each line if there is a comma
				switch (count2) { // switch then puts the data in the right array
				case 0: {
					int t = stoi(cell); time[count] = t; break; 
				}
				case 1: {
					double p = stod(cell); pH[count] = p; break;
				}
				case 2: {
					double o = stod(cell); ORP[count] = o; break;
				}
				default: {
					cout << "error" << endl; break;
				}
				}
				++count2;
			}
			count2 = 0;
			++count;
		}
		else
			first = true;
	}

	cout << "Please Enter a time to find the given values (between 1-2000) : ";
	cin >> inTime;
	if (inTime >= 1 && inTime <= 2000) {
		cout.precision(9);
		cout << fixed << "PH value: " << pH[inTime - 1] << " ORP value: ";
		cout.precision(7);
		cout << ORP[inTime - 1] << endl << endl;
	}
	else
		cout << "Sorry that isn't a integer between 1-2000" << endl << endl;

	for (int i = 0; i <= 1999; i++) {
		if (pH[i] > phMax) phMax = pH[i];
		if (pH[i] < phMin) phMin = pH[i];
		if (ORP[i] > orpMax) orpMax = ORP[i];
		if (ORP[i] < orpMin) orpMin = ORP[i];
		phSum += pH[i];
		orpSum += ORP[i];
	}

	phMean = phSum / 2000.0;
	orpMean = orpSum / 2000.0;
	for (int i = 0; i <= 1999; i++) {
		phSD += pow(pH[i] - phMean, 2);
		orpSD += pow(ORP[i] - orpMean, 2);
	}

	// outputs
	linearRegression(pH, ORP, 2000);
	cout << "The maximum PH is : " << phMax << endl;
	cout << "The minimum PH is : " << phMin << endl;
	cout << "The maximum ORP is : " << orpMax << endl;
	cout << "The minimum ORP is : " << orpMin << endl;
	cout << "The mean of the PH is : " << phMean<< endl;
	cout << "The mean of the ORP is : " << orpMean << endl;
	cout << "The standard deviation of the PH is : " << sqrt(phSD / 2000) << endl;
	cout << "The standard deviation of the ORP is : " << sqrt(orpSD / 2000) << endl;

    return 0;
}

