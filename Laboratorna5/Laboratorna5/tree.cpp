#include "Functions.h"

bool isOperator(char c)
{
	if (c == '+' || c == '-' ||
		c == '*' || c == '/' ||
		c == '^')
		return true;
	return false;
}

int toInt(string s)
{
	int num = 0;
	if (s[0] != '-')
		for (int i = 0; i < s.length(); i++)
			num = num * 10 + (int(s[i]) - 48);
	else
		for (int i = 1; i < s.length(); i++)
		{
			num = num * 10 + (int(s[i]) - 48);
			num = num * -1;
		}

	return num;
}
int eval(node* root)
{
	// empty tree  
	if (!root)
		return 0;

	// leaf node i.e, an integer  
	if (!root->left && !root->right)
		return toInt(root->value);

	// Evaluate left subtree  
	int l_val = eval(root->left);

	// Evaluate right subtree  
	int r_val = eval(root->right);

	// Check which operator to apply  
	if (root->value == "+")
		return l_val + r_val;

	if (root->value == "-")
		return l_val - r_val;

	if (root->value == "*")
		return l_val * r_val;

	return l_val / r_val;
}

void inorder(node* t)
{
	if (t)
	{
		inorder(t->left);
		cout << t->value;
		inorder(t->right);
	}
}

node* newNode(int v)
{
	node* temp = new node;
	temp->left = temp->right = NULL;
	temp->value = v;
	return temp;
};

node* constructTree(string postfix)
{
	stack<node*> st;
	node* t, * t1, * t2;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (!isOperator(postfix[i]))
		{
			t = newNode(postfix[i]);
			st.push(t);
		}
		else
		{
			t = newNode(postfix[i]);
			t1 = st.top();
			st.pop();
			t2 = st.top();
			st.pop();

			t->right = t1;
			t->left = t2;

			st.push(t);
		}
	}

	t = st.top();
	st.pop();

	return t;
}