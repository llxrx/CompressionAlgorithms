#pragma once
#ifndef BWT_H
#define BWT_H

#include <string>
#include <vector>
#include <forward_list>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "BinaryFile.h"

using namespace std;

string BWT_encode(string source);
string BWT_decode(string encoding);

#endif