#pragma once
#include <iostream>
#include <chrono>
#include <locale>
#include <map>
#include <fstream>
#include "RLE.h"
#include "BTW.h"
#include "OPEN_BWT_FILE.h"
#include "MTF.h"
#include "Arithmetic_coding.h"
#include "Entropia.h"

struct file_name_enum_in {
	string enwik7 = "Text_files/enwik7.txt";
	string test = "Text_files/test.txt";
	string Russian_text = "Text_files/Russian_Text.txt";
	string image = "image_files/house.bmp";
	string raw_white_black = "image_files/image_5.bmp";
	string raw_grey = "image_files/image_1.bmp";
};

class final_comp {
private:
	file_name_enum_in file_in;

	map<int, string> file_name_in;
	map<int, string> file_name_out;

	float comp_Rate = 0.0f;

	unsigned int choose_file;
public:
	ofstream final_of;
	ofstream RLE_of;
	ofstream BWT_of;
	ofstream RLE_decoder_of;
	ofstream BWT_decoder_of;

	final_comp();
	~final_comp();

	void Huffman_algorithm_HA();
	void Arithmetic_algorithm_AC();
	void Run_Length_encoding_RLE();
	void BWT_RLE();
	void BWT_MTF_RLE();
	void BWT_MTF_AC();
	void BWT_MTF_RLE_HA();
	void BWT_MTF_RLE_AC();
	void LZ77_encoding();
	void LZ77_HA();
	void LZ77_AC();
};