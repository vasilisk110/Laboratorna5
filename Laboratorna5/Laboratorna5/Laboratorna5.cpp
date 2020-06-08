#include "Functions.h"

int main()
{
	string phrase, part, filename, val, polskz;
	filename = "input.txt";
	int size = getSize(filename);
	ifstream fin(filename);
	string** values = new string * [size - 1];

	for (int i = 0; i < size - 1; i++) {
		values[i] = new string[2];
	}

	for (int i = 0; i < size - 1; i++)
	{
		polskz = "";
		getline(fin, part, ';');
		val = optimize(part);

		polsk(part, polskz);
		delSpaces(polskz);

		node* tree = constructTree(polskz);

		values[i][0] = val;
		values[i][1] = to_string(eval(tree));
	}



	string lastline = last_line(filename).substr(0, last_line(filename).length() - 1);

	for (int i = 0; i < size - 1; i++)
	{
		int start = lastline.find(values[i][0]);
		lastline.replace(start, values[i][0].length(), values[i][1]);
	}



	cout << "Result: " << polsk(lastline, polskz) << endl;


	fin.close();
	system("pause");
}