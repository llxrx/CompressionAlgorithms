#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

class class_MTF
{
public:
	string mtf_encode(string str, string& s)
	{
		fillSymbolTable();
		vector<int> output;
		for (string::iterator it = str.begin(); it != str.end(); it++)
		{
			for (int i = 0; i < 256; i++)
			{
				if (*it == symbolTable[i])
				{
					output.push_back(i);
					moveToFront(i);
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
			s += ss.str();
		}
		return r;
	}

	string mtf_decode(string str)
	{
		fillSymbolTable();
		istringstream iss(str); vector<int> output;
		copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter<vector<int> >(output));
		string r;
		for (vector<int>::iterator it = output.begin(); it != output.end(); it++)
		{
			r.append(1, symbolTable[*it]);
			moveToFront(*it);
		}
		return r;
	}

private:
	void moveToFront(int i)
	{
		char t = symbolTable[i];
		for (int z = i - 1; z >= 0; z--)
			symbolTable[z + 1] = symbolTable[z];

		symbolTable[0] = t;
	}

	void fillSymbolTable()
	{
		for (int x = 0; x < 256; x++)
			symbolTable[x] = x;
	}

	char symbolTable[256];
};

//char symbolTable[26];
//string mtf_encode(string str);
//string mtf_decode(string str);

/*
int search(char input_char, string& list);

string moveToFront(int curr_index, string& list);
string moveToFrontForDecoder(int curr_index, string& list);

vector<int> mtfEncode(string& input_text, string& list, vector<int> output_arr);
string mtfDecode(string& initial_list, vector<int>& encoded_data);

string mtf_dec(string& symbolTable, vector<int>& output);
*/