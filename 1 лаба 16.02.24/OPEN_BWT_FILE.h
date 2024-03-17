#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

string Open_file_RLE(int *size, int *choose_file);
string Open_file_BWT(int size, int *choose_file);