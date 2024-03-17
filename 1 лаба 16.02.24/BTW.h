#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void rotate(string& a);
string bwt(const string& s);
string ibwt(const string& r);
string makePrintable(const string& s);
string Coder_Burrows_Wheeler_Transform(string& s);
string DeCoder_Burrows_Wheeler_Transform(string& s, string& t);
string Start_BWT(string& str);