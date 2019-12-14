#pragma once
#include"node.h"

class stack
{
private: node* Top;

public:

	stack() 
	{
		this->Top = new node();
	}

	~stack() {}

	void create()
	{
		this->Top = NULL;
	}

	node* createNode(elementType val)
	{
		node* n = new node();
		n->data = val;
		n->next = NULL;
		return n;
	}

	bool isEmpty()
	{
		if (this->Top == NULL) return true;
		return false;
	}

	void push(elementType val)
	{
		node* n = createNode(val);
		if (isEmpty())
		{
			this->Top = n;
		}
		else
		{
			n->next = this->Top;
			this->Top = n;
		}
	}

	elementType pop()
	{
		elementType val;
		if (!isEmpty())
		{
			if (this->Top->next == NULL)
			{
				val = this->Top->data;
				this->Top = NULL;
			}
			else
			{
				node* n = this->Top;
				this->Top = this->Top->next;
				val = n->data;
				delete n;
			}
		}
		return val;
	}

	elementType top()
	{
		if (!isEmpty())
		{
			return this->Top->data;
		}
	}
};

