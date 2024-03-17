#pragma once
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

class MTF
{
public:
	char symbolTable[27];
	string encode(string str);
	string decode(string str);

private:
	void moveToFront(int i);
	void fillSymbolTable();
	
};