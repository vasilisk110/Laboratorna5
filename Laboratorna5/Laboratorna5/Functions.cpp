#include "Functions.h"

int getSize(string filename) {
	string str = "";
	ifstream fin(filename);
	int count = 0;
	while (!fin.eof()) {
		getline(fin, str);
		count++;
	}
	fin.close();
	return count;
}
string last_line(string filename)
{
	ifstream fin;
	string lastLine;
	fin.open(filename);
	if (fin.is_open()) {
		fin.seekg(-1, ios_base::end);

		bool keepLooping = true;
		while (keepLooping) {
			char ch;
			fin.get(ch);
			if ((int)fin.tellg() <= 1) {
				fin.seekg(0);
				keepLooping = false;
			}
			else if (ch == '\n') {
				keepLooping = false;
			}
			else {
				fin.seekg(-2, ios_base::cur);
			}
		}

		getline(fin, lastLine);
		fin.close();
	}
	return lastLine;
}
string optimize(string& part) {
	for (int i = 0; i < part.size(); i++) {
		if (isspace(part[i])) {
			part.erase(i, 1);
			i--;
		}
	}

	string val = part.substr(0, part.find('='));
	part = part.substr(part.find('=') + 1);
	return val;
}

void delSpaces(string& str) {
	for (int i = 0; i < str.size(); i++) {
		if (isspace(str[i])) {
			str.erase(i, 1);
			i--;
		}
	}
}

int priority(char oper) {
	if (oper == '+' || oper == '-')
		return 1;
	if (oper == '*' || oper == '/')
		return 2;
	if (oper == '^')
		return 3;
}

int polsk(string phrase, string& ans) {
	string chars;
	stack<int> tmp;
	stack<int> result;

	// Заполняем стек символов (сhars)
	for (int i = 0; i < phrase.size(); i++)
	{
		if (isdigit(phrase[i])) {
			chars.push_back(phrase[i]);

		}
		else {
			chars.push_back(' ');
			while (!tmp.empty() && priority(phrase[i]) <= priority(tmp.top()))
			{
				chars.push_back(tmp.top());
				tmp.pop();
			}
			tmp.push(phrase[i]);

		}
	}
	while (!tmp.empty()) {
		chars.push_back(tmp.top());
		tmp.pop();
	}
	for (int i = 0; i < chars.size(); i++)
	{
		if (isdigit(chars[i]))
		{
			double num = double(chars[i] - '0');
			for (++i; isdigit(chars[i]) && i < chars.size(); i++) {
				num *= 10; num += double(chars[i] - '0');
			}
			result.push(num);
			ans = ans + to_string((int)num) + " ";
			if (chars[i] != ' ') {
				i--;
			}
		}
		else {
			ans = ans + (chars[i]) + " ";
			double a = result.top();
			result.pop();
			double b = result.top();
			result.pop();
			switch (chars[i]) {
			case '+':
				result.push(a + b);
				break;
			case '-':
				result.push(b - a);
				break;
			case '*':
				result.push(a * b);
				break;
			case '/':
				if (a == 0) {
					cout << "Error! Can't be divided by zero!" << endl;
					return 1;
				}
				result.push(double(b / a));

				break;
			case '^':
				result.push(double(pow(b, a)));
				break;
			}
		}
	}
	return result.top();
}