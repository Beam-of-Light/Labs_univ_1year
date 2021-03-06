#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

bool checking(string n)
{
	bool t;
	for (int i = 0; i < n.length(); i++)
	{
		if (isdigit(n[i]))
			t = true;
		else
			return false;
	}
	return t;
}

void write_number(int num[], string n)
{
	for (int i = 0; i < n.length(); i++)
		num[i] = (int)n[i] - 48;
}

void reverse(int num[], int size)
{
	for (int i = 0, t; i < size / 2; ++i)
	{
		t = num[i];
		num[i] = num[size - i - 1];
		num[size - i - 1] = t;
	}
}

void addition(int num01[], int num02[], int length, string n)
{
	num01[length] = 0;

	for (int i = 0; i < n.length(); i++)
		num01[i] += num02[i];
	for (int i = 0; i < length; i++)
	{
		num01[i + 1] += (num01[i] / 10);
		num01[i] %= 10;
	}

	while (num01[length] == 0)
		length--;
	reverse(num01, length + 1);
	for (int i = 0; i <= length; i++)
		cout << num01[i];
	cout << endl;
}

int main()
{
	// Writing data
	string n1, n2;

	cout << "Write 1-st number:" << endl;
	cin >> n1;
	while (!(checking(n1))) /*checking 1-st number*/
	{
		cout << "Error. Write 1-st number please:" << endl;
		cin >> n1;
	}
	int *num_1 = new int[n1.length() + 1];

	cout << "Write 2-nd number:" << endl;
	cin >> n2;
	while (!(checking(n2))) /*checking 2-nd number*/
	{
		cout << "Error. Write 2-nd number please:" << endl;
		cin >> n2;
	}
	int *num_2 = new int[n2.length() + 1];

	//String to int array
	write_number(num_1, n1);
	write_number(num_2, n2);

	//Reverse
	reverse(num_1, n1.length());
	reverse(num_2, n2.length());

	//Addition
	cout << "\nAddition:" << endl;
	n1.length() > n2.length() ? addition(num_1, num_2, n1.length(), n2) : addition(num_2, num_1, n2.length(), n1);
	if (n1 == n2 && n1 == "0") cout << "0" << endl;

	//Exit
	delete[] num_1;
	delete[] num_2;
	system("pause");
	return 0;
}