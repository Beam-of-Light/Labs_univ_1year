#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s1, s2;
	int max = 0, elements_number = 0, left = -1, one_element;
	bool is_common_element = false;

	cout << "Write 1-st and 2-nd strings:\n";
	getline(cin, s1);
	getline(cin, s2);

	for (int i = 0; i < s1.length(); i++)
	{
		for (int j = 0; j < s2.length(); j++) 
		{
			while (s1[i + elements_number] == s2[j + elements_number])
			{
				if (max < elements_number)
				{
					max = elements_number;
					left = i;
				}
				if (s1[i] == s2[j])
				{
					is_common_element = true;
					one_element = i;
				}
				elements_number++;
			}
			elements_number = 0;
		}
	}

	if (max > 0)
	{
		cout << "\nCommon elements:\n";
		for (int i = left; i <= left + max; i++) cout << s1[i];
	}
	else if (is_common_element)
	{
		cout << "\nCommon elements:\n" << s1[one_element];
	}
	else if (!is_common_element) cout << "\nNo common elements";
	cout << "\n\n";

	system("pause");
	return 0;
}
