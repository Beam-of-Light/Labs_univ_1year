#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef short int sint;

int main()
{
	sint N, k;
	vector<sint> a/*= {20, 11, 5, 5, 1}*/;
	string plus_minus;

	cout << "Write elements number:\t";
	cin >> N;
	cout << "Write elements:\n";
	
	for (sint i = 0; i < N; i++)
	{
		cin >> k;
		a.push_back(k);
	}
	
	sint result = a[0];
	for (sint i = 1; i < a.size(); i++)
	{
		if (abs(0 - result + a[i]) > abs(0 - result - a[i]))
		{
			result += a[i];
			plus_minus[i] = '+';
		}
		else 
		{
			result -= a[i];
			plus_minus[i] = '-';
		}
	}

	if (result == 0)
	{
		cout << "Result:" << endl;
		for (sint i = 0, j = 1; j < a.size(); i++, j++)
		{
			cout << a[i] << " " << plus_minus[j] << " ";
		}
		cout << a[a.size()-1] << " = 0\n\n";
	}
	else cout << "No solution\n\n";

	system("pause");
	return 0;
} 