#pragma once
#include"stack.h"
#include<vector>
#include<math.h>

class postfix
{
private:
	string getString(char x)
	{
		string s(1, x);
		return s;
	}

	bool isoperator(char s)
	{
		if (s == '^' || s == '*' || s == '/' || s == '+' || s == '-') return true;
		return false;
	}

	bool isNumber(string s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (!isdigit(s[i]) && s[i] != '.') return false;
		}
		return true;
	}

	int rank(string s)
	{
		if (s == "^") return 3;
		if (s == "*" || s == "/") return 2;
		if (s == "+" || s == "-") return 1;
		if (s == "(") return 0;
	}


public:
	postfix() {}
	~postfix() {}

	vector<string> convert(string infixexp)
	{
		vector<string> POST;
		stack* ST = new stack(); ST->create();

		int i = 0;
		while (i < infixexp.length())
		{
			//Is float operand
			if (isdigit(infixexp[i]))
			{
				int j = i;
				while (isdigit(infixexp[j]) || infixexp[j] == '.') j++;
				string number = infixexp.substr(i, j - i);
				POST.push_back(number);
				i = j - 1;
			}
			//Is bracket
			else if (infixexp[i] == '(') ST->push(getString(infixexp[i]));
			else if (infixexp[i] == ')')
			{
				while (!ST->isEmpty() && ST->top() != "(") POST.push_back(ST->pop());
				ST->pop();
			}
			//Is operator
			else if (isoperator(infixexp[i]))
			{
				string op = getString(infixexp[i]);
				if (ST->isEmpty()) { ST->push(op); }
				else 
				{
					while (!ST->isEmpty() && rank(op) <= rank(ST->top())) POST.push_back(ST->pop());
					ST->push(op);
				}
			}
			i++;
		}

		while (!ST->isEmpty()) POST.push_back(ST->pop());
		return POST;
	}

	double evaluate(vector<string> postfixexp)
	{
		double result;

		stack* oprand = new stack();

		for (auto i = postfixexp.begin(); i != postfixexp.end(); i++)
		{
			if (isNumber(*i))
			{
				oprand->push(*i);
			}
			else
			{
				double num1 = stod(oprand->pop());
				double num2 = stod(oprand->pop());

				string op = *i;
				if		(op == "+") oprand->push(to_string(num2 + num1));
				else if (op == "-") oprand->push(to_string(num2 - num1));
				else if (op == "*") oprand->push(to_string(num2 * num1));
				else if (op == "/") oprand->push(to_string(num2 / num1));
				else if (op == "^") oprand->push(to_string(pow(num2, num1)));
			}
		}

		result = stod(oprand->pop());
		return result;
	}
};

