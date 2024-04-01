#include "final_compressor.h"

final_comp::final_comp() {
	file_name_in.emplace(1, file_in.enwik7);
	file_name_in.emplace(2, file_in.test);
	file_name_in.emplace(3, file_in.Russian_text);
	file_name_in.emplace(4, file_in.image);
	file_name_in.emplace(5, file_in.raw_white_black);
	file_name_in.emplace(6, file_in.raw_grey);

	final_of.open("output_files/FINAL.txt", ios::out);
	RLE_of.open("output_files/RLE.txt", ios::out);
	BWT_of.open("output_files/BWT.txt", ios::out);
	RLE_decoder_of.open("output_files/RLE_decoder.txt", ios::out);
	BWT_decoder_of.open("output_files/BWT_decoder.txt", ios::out);

	cout << "Choose file\n";
	cout << "1 - RLE\n";
	cout << "2 - BWT + RLE\n";
	cout << "3 - BWT + MTF + RLE\n";
	cout << "Your Choose: ";
	cin >> choose_file;

	switch (choose_file) {
	case 1:
		Run_Length_encoding_RLE();
		break;
	case 2:
		BWT_RLE();
		break;
	case 3:
		BWT_MTF_RLE_AC();
		break;
	}
}

final_comp::~final_comp() {

}

void final_comp::Run_Length_encoding_RLE() {
	unsigned int choose;
	string file_name;
	string strh;
	string str;

	cout << "Choose file\n";
	cout << "1 - enwik7\n";
	cout << "2 - test\n";
	cout << "3 - Russian_text\n";
	cout << "4 - image\n";
	cout << "5 - raw white-black\n";
	cout << "6 - raw grey\n";
	cout << "Your Choose: ";
	cin >> choose;

	file_name = file_name_in[choose];

	ifstream FILE(file_name, ios::in);

	while (!FILE.eof()) {
		getline(FILE, strh);
		str += strh;
		if (!FILE.eof()) {
			str += '\n';
		}
	}
	cout << "file lenght - " << str.length() << "\n";


	// RLE
	int size;
	int choice;
	string cod;
	//string str = Open_file_RLE(&size, &choice);
	Start_RLE(str, &cod, &comp_Rate);
}

void final_comp::BWT_RLE() {
	string str;
	string strh;
	string file_name;
	unsigned int choose;

	cout << "Choose file\n";
	cout << "1 - enwik7\n";
	cout << "2 - test\n";
	cout << "3 - Russian_text\n";
	cout << "4 - image\n";
	cout << "5 - raw white-black\n";
	cout << "6 - raw grey\n";
	cout << "Your Choose: ";
	cin >> choose;

	file_name = file_name_in[choose];

	ifstream FILE(file_name, ios::in);

	while (!FILE.eof()) {
		getline(FILE, strh);
		str += strh;
		if (!FILE.eof()) {
			str += '\n';
		}
	}
	cout << "file lenght - " << str.length() << "\n";

	string str_end;
	string cod;
	string asd;
	string BWT;
	string RLE;
	string RLE_Res;
	string str_h;

	float final_Rate = 0.0f;

	unsigned int block_size_1 = 500;
	unsigned int block_size_2 = 500;
	unsigned int size = str.length() / block_size_1;
	unsigned int real_size = str.length() - (size * block_size_1);
	bool flag;
	if (real_size != 0) flag = true;
	else flag = false;

	for (size_t i = 0; i < size + 1; i++) {
		if (flag == true && i == size) {
			block_size_2 = real_size;
		}
		for (int j = (i * block_size_1); j < ((i * block_size_1) + block_size_2); j++) {
			cod.push_back(str[j]);
		}

		BWT = Coder_Burrows_Wheeler_Transform(cod);
		BWT_of << BWT;
		
		RLE = Coder_Run_Len_Encoding(BWT, &comp_Rate);
		RLE_of << RLE;

		RLE_Res = Decoder_Run_Len_Encoding(RLE);
		RLE_decoder_of << RLE_Res;

		str_h = DeCoder_Burrows_Wheeler_Transform(str, RLE_Res);
		BWT_decoder_of << str_h;

		str_end.append(str_h);
		final_Rate += comp_Rate;

		cod.clear();
		BWT.clear();
		RLE_Res.clear();
		strh.clear();
	}
	//Equal_Text(str, str_end);
	cout << "Final Compression Rate - " << (final_Rate / size) << "%" << "\n";
	
	final_of << str_end;

	final_of.close();
	RLE_of.close();
	BWT_of.close();
	RLE_decoder_of.close();
	BWT_decoder_of.close();
}

void final_comp::BWT_MTF_RLE_AC() {
	string str;
	string strh;
	string file_name;
	unsigned int choose;

	cout << "Choose file\n";
	cout << "1 - enwik7\n";
	cout << "2 - test\n";
	cout << "3 - Russian_text\n";
	cout << "4 - image\n";
	cout << "5 - raw white-black\n";
	cout << "6 - raw grey\n";
	cout << "Your Choose: ";
	cin >> choose;

	file_name = file_name_in[choose];

	ifstream FILE(file_name, ios::in);

	while (!FILE.eof()) {
		getline(FILE, strh);
		str += strh;
		if (!FILE.eof()) {
			str += '\n';
		}
	}
	cout << "file lenght - " << str.length() << "\n";

	string str_end;
	string cod;
	string asd;

	string BWT;
	string RLE;
	string RLE_dec;
	string BWT_dec;
	string MTF;
	string MTF_dec;

	//string mtf_decode;

	string list;

	class_MTF mtf;

	for (size_t i = 0; i < 256; i++) {
		list.push_back((char)i);
	}

	for (size_t i = 0; i < 1; i++) {
		BWT = Coder_Burrows_Wheeler_Transform(str);

		vector<int> output_arr;

		cout << "Move to Front Transform: ";
		string* sre = new string;
		MTF = mtf.mtf_encode(BWT, *sre);

		/*
		vector<int> mtf_arr = mtfEncode(BWT, list, output_arr);

		string mtf_arr_str;

		for (size_t i = 0; i < mtf_arr.size(); i++) {
			mtf_arr_str.append(to_string(mtf_arr[i]));
		}
		*/

		
		RLE = Coder_Run_Len_Encoding(*sre);
		RLE_dec = Decoder_Run_Len_Encoding(RLE);

		MTF_dec = mtf.mtf_decode(MTF);

		//mtf_decode = mtf_dec(list, mtf_arr);
		//mtf_decode = mtfDecode(list, mtf_arr);

		BWT_dec = DeCoder_Burrows_Wheeler_Transform(str, MTF_dec);

		RLE_of << RLE;
		BWT_of << BWT;
		RLE_decoder_of << RLE_dec;
		BWT_decoder_of << BWT_dec;
		final_of << RLE;

		//for (size_t i = 0; i < mtf_arr.size(); i++) END1 << mtf_arr[i];
	}
}
