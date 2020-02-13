#include "tokenizer.h"

#include<iostream>


struct MyTree {
	char inChar;
	MyTree* left, *right;
};

bool isConnector(char c)
{
	if(c == "&&"  || c == "||")
		return true;
	return false;	
}

MyTree* newNode(char c)
{
	MyTree* temp = new MyTree;
	temp->left = temp->right = nullptr;
	temp->inChar = c;
	return temp;
}

MyTree* makeTree(char table<Token*>)
{
	stack<MyTree *> st;
	MyTree *t, *t1, *t2;
	
	for(int i = 0; i < table.size(); i++)
	{
		if(!isConnector(table.at(i))
		{
			t = newNode(table.at(i));
			st.push(t);		
		}
		else
		{
			t = newNode(table.at(i));
			
			t1 = st.top();
			st.pop();
			t2 = st.top();
			st.pop()

			t->right = t1;
			t->left = t2;

			st.push(t);	
		}
	}

	t = st.top();
	st.pop();

	return t;
}
