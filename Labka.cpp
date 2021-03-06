#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	// Writing data
	int number, num_system = 0, last = 0;
	int digits[499];
	char a;

	cout << "Write your number:\n";
	cin >> number;

	// Choose num_system
	while (num_system > 9 || num_system < 2)
	{
		cout << "Choose your number system from 2 to 9:\n";
		cin >> num_system;
	}

	// Checking number
	if (number > 0 || number < 0)
	{
		number > 0 ? a = '+' : a = '-';
		number = abs(number);

		while (number > 0)
		{
			digits[last] = number % num_system;
			number /= num_system;
			last++;
		}

		cout << "\nResult is:\n";
		if (a == '-') cout << a ;

		for (int i = last; i; i--)
		{
			cout << digits[i - 1];
		}

		cout << "\n";
	}
	else
	{
		cout << "\nResult is:\n0\n";
	}

	system("pause");
	return 0;
}