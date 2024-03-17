#include "MTF.h"

string MTF::encode(string str)
{
	fillSymbolTable();
	vector<int> output;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		for (int i = 0; i < 27; i++)
		{
			if (*it == symbolTable[i])
			{
				output.push_back(i);
				moveToFront(i);
				break;
			}
			if (*it == 0x02) {
				output.push_back(0x02 * 100);
				break;
			}
			if (*it == 0x03) {
				output.push_back(0x03 * 100);
				break;
			}
		}
	}
	string r;
	for (vector<int>::iterator it = output.begin(); it != output.end(); it++)
	{
		ostringstream ss;
		ss << *it;
		r += ss.str() + " ";
	}
	return r;
}

string MTF::decode(string str)
{
	fillSymbolTable();
	istringstream iss(str); vector<int> output;
	copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter<vector<int> >(output));
	string r;
	for (vector<int>::iterator it = output.begin(); it != output.end(); it++)
	{
		if (*it == 200) {
			r.push_back(0x02);
			continue;
		}
		if (*it == 300) {
			r.push_back(0x03);
			continue;
		}
		r.append(1, symbolTable[*it]);
		moveToFront(*it);
	}
	return r;
}

void MTF::moveToFront(int i)
{
	char t = symbolTable[i];
	for (int z = i - 1; z >= 0; z--)
		symbolTable[z + 1] = symbolTable[z];

	symbolTable[0] = t;
}

void MTF::fillSymbolTable()
{
	for (int x = 0; x < 26; x++) symbolTable[x] = x + 'a';
	symbolTable[26] = ' ';
}
