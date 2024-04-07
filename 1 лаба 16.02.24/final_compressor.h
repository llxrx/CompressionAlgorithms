#pragma once
#include "library.h"
#include "RLE.h"
#include "BTW.h"
#include "MTF.h"
#include "Arithmetic_coding.h"
#include "Entropia.h"
#include "Huffman Coding.h"
#include "fast_BWT.h"

using namespace std;

template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	template<typename F>
	static typename TimeT::rep execution(F const& func)
	{
		auto start = std::chrono::system_clock::now();
		func();
		auto duration = std::chrono::duration_cast<TimeT>(
			std::chrono::system_clock::now() - start);
		return duration.count();
	}
};

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

	string file_name;
	string strh;
	string str;
	
	fstream final_of;
	fstream RLE_of;
	fstream BWT_of;
	fstream MTF_of;
	fstream Huff_of;
	fstream RLE_decoder_of;
	fstream BWT_decoder_of;
	fstream MTF_decoder_of;
	fstream Huff_decoder_of;
public:
	final_comp();
	~final_comp();

	
	void BWT();
	void Huffman_algorithm_HA();
	void Arithmetic_algorithm_AC();
	void Run_Length_encoding_RLE();
	void BWT_RLE();
	void BWT_MTF_RLE_HA();
	void BWT_MTF_AC();
	void BWT_MTF_RLE_AC();
	void LZ77_encoding();
	void LZ77_HA();
	void LZ77_AC();
};