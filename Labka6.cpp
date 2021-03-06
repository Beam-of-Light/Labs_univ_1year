//Reverse Polish notation
#include "pch.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//Prototype
void reverse(string&, short int, short int);
void push_var(string&, int);
bool is_operator(char&);
void stack_push_exit(stack<char>&, string&);
bool check_unary(string&, short int&, short int&, char);
bool unary(string&, short int&, stack<char>&);
void check_exp(string&, short int&, string&, stack<char>&);
bool check_num(string&, short int&, string&);
void check_var(string&, short int&, string&, vector<string>&, vector<int>&);
void check_operator(string&, short int&, string&, stack<char>&);
short int priority(char);

enum {fourth_priority, third_priority, second_priority, first_priority};

short int var_number = 0;
int main()
{
	string entrance, exit;
	getline(cin, entrance);
	stack<char> operators;
	stack<int> calc;
	vector<string> string_var;
	vector<int> int_var;

	//Checking
	for (short int i = 0; i <= entrance.length(); i++)
	{
		if (i == 0) /*unary*/
		{
			if (!(unary(entrance, --i, operators)))
			{
				cout << "\nSyntacsis error\n1\n";
				return 0;
			}
			i++;
		}
		while ((entrance[i] == ' ' || entrance[i] == '\t') && i < entrance.length()) i++; /*Space*/
		if (isdigit(entrance[i])) /*num*/
		{
			if (!(check_num(entrance, i, exit)))
			{
				cout << "\nSyntacsis error\n2\n";
				return 0;
			}
		}
		else if (entrance[i] == 'e' && entrance[i + 1] == 'x' && entrance[i + 2] == 'p') /*exp*/
			check_exp(entrance, i, exit, operators);
		else if (entrance[i] == '_' || isalpha(entrance[i])) /*variable*/
			check_var(entrance, i, exit, string_var, int_var);
		else if (entrance[i] == '(') /*(*/
		{
			operators.emplace('(');
			if (entrance[i + 1] == '+' || entrance[i + 1] == '-')
			{
				if (!(unary(entrance, i, operators))) /*unary*/
				{
					cout << "\nSyntacsis error\n3\n";
					return 0;
				}
			}
		}
		else if (is_operator(entrance[i])) /*operator*/
		{
			check_operator(entrance, i, exit, operators);
			if (!(unary(entrance, i, operators))) /*unary*/
			{
				cout << "\nSyntacsis error\n4\n";
				return 0;
			}

		}
		else if (entrance[i] == ')') /*)*/
		{
			bool t = true;
			while (t)
			{
				if (operators.empty()) break;
				if (operators.top() == '(')
				{
					operators.pop();
					t = false;
					if (priority(operators.top()) > fourth_priority)
						stack_push_exit(operators, exit);
					break;
				}
				stack_push_exit(operators, exit);
			} 
			if (t)
			{
				cout << "\nSyntacsis error\n5\n";
				return 0;
			}
		}
		else if (entrance[i] == '\0') /*push stack to exit*/
		{
			while (!(operators.empty()))
			{
				if (operators.top() == '(')
				{
					cout << "\nSyntacsis error\n6\n";
					return 0;
				}
				stack_push_exit(operators, exit);
			}
		}
		else
		{
			cout << "\nSyntacsis error\n7\n";
			return 0;
		}
	}

	//Exit string
	cout << "\n\nPolish notation: ";
	for (short int i = 0; i < exit.length(); i++)
		cout << exit[i];
	cout << "\n\n";

	//Calculating
	for (short int i = 0; i != exit.length(); i++)
	{
		if (isdigit(exit[i]))
		{
			string temp;
			while (isdigit(exit[i]))
			{
				temp.push_back(exit[i]);
				i++;
			}
			stringstream stream(temp);
			int va;
			stream >> va;
			calc.emplace(va);
		}
		if (is_operator(exit[i]))
		{
			if (!(calc.empty()))
			{
				int a = calc.top();
				calc.pop();
				if (calc.empty())
				{
					cout << "\nSyntacsis error\n\n";
					return 0;
				}
				switch (exit[i])
				{
				case '+': calc.top() = calc.top() + a;
					break;
				case '-': calc.top() = calc.top() - a;
					break;
				case '/': calc.top() = calc.top() / a;
					break;
				case '*': calc.top() = calc.top() * a;
					break;
				}
			}
			else 
			{
				cout << "\nSyntacsis error\n\n";
				return 0;
			}
		}
		else if (exit[i] == 'e')
		{
			if (!(calc.empty()))
				calc.top() = exp(calc.top());
			else 
			{
				cout << "\nSyntacsis error\n\n";
				return 0;
			}
		}
		else if (exit[i] == '~')
			if (!(calc.empty()))
				calc.top() = calc.top() * -1;
			else
			{
				cout << "\nSyntacsis error\n\n";
				return 0;
			}
	}

	int res = calc.top();
	calc.pop();
	if (calc.empty())
		cout << "Result: " << res << "\n\n";
	else 
	{
		cout << "\nSyntacsis error\n\n";
		return 0;
	}

	system("pause");
	return 0;
}



//Functions
void reverse(string &ex, short int begin, short int end)
{
	int k = begin + (end - begin) / 2;
	end--;
	for (int t; begin < k; begin++, end--)
	{
		t = ex[begin];
		ex[begin] = ex[end];
		ex[end] = t;
	}
}

void push_var(string &ex, int va)
{
	short int begin = ex.length();
	short int end = begin;
	do
	{
		ex.push_back((va % 10) + '0');
		va /= 10;
		end++;
	} while (va != 0);

	reverse(ex, begin, end);
	ex.push_back(' ');
}

bool is_operator(char &c)
{
	if (c == '/' || c == '*' || c == '+'|| c == '-')
		return true;
	else
		return false;
}

void stack_push_exit(stack<char> &op, string &ex)
{
	ex.push_back(op.top());
	ex.push_back(' ');
	op.pop();
}

bool check_unary(string &entr, short int &i, short int& counter, char c)
{
	bool t = false;
	int k = i + 1;
	while (!t)
	{
		if (entr[k] == c)
		{
			counter++;
			k++;
			continue;
		}
		else if (entr[k] == ' ' || entr[k] == '\t')
		{
			k++;
			continue;
		}
		else if (entr[k] == '(' || isalnum(entr[k]))
		{
			t = true;
			i = k - 1;
			return t;
		}
		else return t;
	}
}

bool unary(string &entr, short int &i, stack<char> &op)
{
	short int j = i, counter = 0;
	if (check_unary(entr, j, counter, '-'))
	{
		while (i < i + counter)
		{
			op.emplace('~');
			counter--;
		}
		i = j;
		return true;
	}
	else if (check_unary(entr, j = i, counter, '+'))
	{
		i = j;
		return true;
	}
	else return false;
}

void check_exp(string &entr, short int &i, string &ex, stack<char> &op)
{
	bool t = false;
	int k = i + 3;
	while (!t)
	{
		if (entr[k] == '(')
		{
			t = true;
			i = k;
			break;
		}
		else if (entr[k] == ' ' || entr[k] == '\t')
		{
			k++;
			continue;
		}
		else break;
	}
	if (t)
	{
		while (!(op.empty() || first_priority > priority(op.top())))
			stack_push_exit(op, ex);
		op.emplace('e');
		op.emplace('(');
	}
}

bool check_num(string &entr, short int &i, string &ex)
{
	bool t = false;
	int k = i + 1;
	while (!t)
	{
		if (entr[k] >= '0' && entr[k] <= '9') k++;
		else if (entr[k] == ' ' || entr[k] == '\t' || is_operator(entr[k]) || entr[k] == '\0' || entr[k] == ')')
			t = true;
		else break;
	}
	if (t)
	{
		for(; i < k; i++) ex.push_back(entr[i]);
		ex.push_back(' ');
	}
	i--;
	return t;
}

void check_var(string &entr, short int &i, string &ex, vector<string> &string_var, vector<int> &int_var)
{
	bool t = false;
	short int k = i + 1;
	while (!t)
	{
		if (entr[k] == '_' || isalnum(entr[k]))
			k++;
		else if (entr[k] == ' ' || entr[k] == '\t' || is_operator(entr[k]) || entr[k] == '\0')
			t = true;
		else break;
	}
	if (t)
	{
		bool check = false;
		string temporary;

		for (short int j = i; j < k; j++)
			temporary.push_back(entr[j]);

		for (short int j = 0; j < var_number && var_number != 0; j++)
		{
			if (string_var[j] == temporary)
			{
				push_var(ex, int_var[j]);
				check = true;
				i = k - 1;
				break;
			}
		}
		
		if (!(check))
		{
			int va;
			for (; i < k; i++)
				cout << entr[i];
			do
			{
				cout << " = > ";
				cin >> va;
			} while (va < 0);

			int_var.push_back(va);
			string_var.push_back(temporary);
			push_var(ex, va);
			var_number++;
			i--;
		}
	}
}

void check_operator(string &entr, short int &i, string &ex, stack<char> &op)
{
	while (!(op.empty() || priority(entr[i]) > priority(op.top())))
		stack_push_exit(op, ex);
	op.emplace(entr[i]);
}

short int priority(char c)
{
	switch (c)
	{
	case 'e': return first_priority;
	case '~': return second_priority;
	case '/': return third_priority;
	case '*': return third_priority;
	case '+': return fourth_priority;
	case '-': return fourth_priority;
	}
}
