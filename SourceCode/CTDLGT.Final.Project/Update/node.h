#pragma once
using namespace std;
#include<string>
#define elementType string

class node
{
private:
public:
	elementType data;
	node* next;

	node(){}
	~node(){}
};