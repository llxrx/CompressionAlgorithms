#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

map<char, double>Probability(string& str);
double Arithmetic_Coding(string &str);
void Arithmetic_DeCoding(double message, string& str, map<char, double> mmap);