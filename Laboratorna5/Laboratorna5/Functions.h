#pragma once


#include <iostream> 
#include <string>
#include <sstream>
#include <stack>
#include <fstream>

#define MAX 1000 // Мах размер стека


using namespace std;

struct node
{
	string value;
	node* left, * right;
};


void delSpaces(string& str);
int priority(char oper);
int getSize(string filename);
int polsk(string phrase, string& ans);
string optimize(string& part);
string last_line(string filename);


bool isOperator(char c);
int toInt(string s);
int eval(node* root);
void inorder(node* t);
node* newNode(int v);
node* constructTree(string postfix);



