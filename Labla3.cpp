#include "pch.h"
#include <iostream>
using namespace std;

// Your function
double calculate_func(double x)
{
	return (pow(x, 4) - 8.14*pow(x, 3) - 6.3*pow(x, 2) + 125.08*x - 175.84);
}

// Finding root
double root(double(*f) (double), double a1, double b1, double epsilon)
{
	short int i = 0;
	double _x = 1;
	while (abs(f(b1) - f(a1)) > epsilon)
	{
		_x = a1 - ((f(a1) * (b1-a1)) / (f(b1) - f(a1)));
		if ((f(a1) * f(_x)) > 0) a1 = _x;
		else b1 = _x;
		i++; 
		if (i > 50) break;
	}
	return _x;
}

int main()
{
	// Checking borders
	double left_border, right_border, eps = 0.0001;
	cout << "Write borders to find out only one root\n\n\n";
	do
	{
		cout << "Write left border: ";
		cin >> left_border;
		cout << "Write right border: ";
		cin >> right_border;
		
		cout << "F(a) = " << calculate_func(left_border) << "\nF(b) = " << calculate_func(right_border) << endl;
		if (calculate_func(left_border) == 0) {cout << "Your left border is a root\n\n";}
		if (calculate_func(right_border) == 0) {cout << "Your right border is a root\n\n";}
		if (calculate_func(left_border)*calculate_func(right_border) >= 0 || abs(right_border - left_border) > 6) {cout << "Please write another borders\n\n";}
	
	} while (calculate_func(left_border)*calculate_func(right_border) >= 0 || abs(right_border - left_border) > 6);
	
	// Result and exit
	cout << "\nRoot is " << root(calculate_func, left_border, right_border, eps) << "\n\n";

	system("pause");
	return 0;
} 