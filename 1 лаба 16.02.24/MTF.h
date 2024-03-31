#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

int search(char input_char, string& list);
void moveToFront(int curr_index, string& list);
int* mtfEncode(string& input_text, string& list, int* output_arr);