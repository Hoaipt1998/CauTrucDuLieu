using namespace std;
#include<iostream>
#include<string>
#include"postfix.h"

void Input(string& EXP);
void Program(string EXP, double& RESULT);
void Output(double RESULT);

void deleteSpace(string& str);
bool check(string EXP);
bool isoperator(char s);
bool isbracket(char s);

int main()
{
	string EXP; double RESULT(0);
	Input(EXP);
	Program(EXP, RESULT);
	Output(RESULT);
	return 0;
}

void Input(string& EXP)
{
	cout << "Enter: ";
	getline(cin, EXP);
}

void Output(double RESULT)
{
	cout << "Result: " << RESULT << endl;
}

void Program(string EXP, double& RESULT)
{
	deleteSpace(EXP);
	if (!check(EXP)) { cout << "Expression is wrong!" << endl; return; }

	postfix* post = new postfix();
	RESULT = post->evaluate(post->convert(EXP));
}

void deleteSpace(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		while (str[i] == ' ' && i < str.length()) { str.erase(i, 1); }
	}
}

bool check(string EXP)
{
	//check valid math character
	for (int i = 0; i < EXP.length(); i++)
	{
		if (!isdigit(EXP[i]) && !isoperator(EXP[i]) && !isbracket(EXP[i]) && EXP[i] != '.') return false;
	}
	//check float number
	if (EXP[0] == '.' || EXP[EXP.length() - 1] == '.') return false;
	int count = 0;
	for (int i = 0; i < EXP.length(); i++)
	{
		if (isdigit(EXP[i])) { count++; }
		if (EXP[i] == '.' && (!isdigit(EXP[i - 1]) || !isdigit(EXP[i + 1]))) return false;
	}
	if (count == 0) return false;
	//check valid operator
	if (isoperator(EXP[0])) return false;
	if (isoperator(EXP[EXP.length() - 1])) return false;
	for (int i = 1; i < EXP.length() - 1; i++)
	{
		if (isoperator(EXP[i]))
		{
			if (!isdigit(EXP[i - 1]) && !isbracket(EXP[i - 1])) return false;
			if (!isdigit(EXP[i + 1]) && !isbracket(EXP[i + 1])) return false;
		}
	}
	//check valid braket
	int o = 0, c = 0;
	for (int i = 0; i < EXP.length(); i++)
	{
		if (EXP[i] == '(') o++;
		if (EXP[i] == ')') c++;
	}
	if (o != c) return false;

	return true;
}

bool isoperator(char s)
{
	if (s == '^' || s == '*' || s == '/' || s == '+' || s == '-') return true;
	return false;
}

bool isbracket(char s)
{
	if (s == '(' || s == ')') return true;
	return false;
}