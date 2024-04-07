#pragma once
#include "library.h"

using namespace std;

//string Coder_Run_Len_Encoding(string& str);
string Coder_Run_Len_Encoding(string& str, float* compression_Rate_in_percent);
string Coder_Run_Len_Encoding(string& str);
string Decoder_Run_Len_Encoding(const string& encoded_str);
bool Equal_Text(string& str, const string& decoded_str);
string Start_RLE(string& str, string *cod, float *comp_Rate);