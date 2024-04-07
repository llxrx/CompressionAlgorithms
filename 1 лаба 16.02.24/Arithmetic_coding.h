#pragma once
#include "library.h"

using namespace std;
class Arithmetic_Coding {
private:
	vector<double> c;
	vector<double> d;
	string byte;
	string final_str;

public:
	map<char, double>Probability(string& str);
	string Arithmetic_Encoder(string& str);
	void Arithmetic_DeCoding();
};
