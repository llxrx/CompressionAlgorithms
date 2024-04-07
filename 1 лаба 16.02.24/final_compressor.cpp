#include "final_compressor.h"

final_comp::final_comp() 
{
	file_name_in.emplace(1, file_in.enwik7);
	file_name_in.emplace(2, file_in.test);
	file_name_in.emplace(3, file_in.Russian_text);
	file_name_in.emplace(4, file_in.image);
	file_name_in.emplace(5, file_in.raw_white_black);
	file_name_in.emplace(6, file_in.raw_grey);

	
	final_of.open("output_files/FINAL.txt", ios::out);
	RLE_of.open("output_files/RLE.txt", ios::out);
	BWT_of.open("output_files/BWT.txt", ios::out);
	MTF_of.open("output_files/MTF.txt", ios::out);
	Huff_of.open("output_files/HUFF.txt", ios::out);
	RLE_decoder_of.open("output_files/RLE_decoder.txt", ios::out);
	BWT_decoder_of.open("output_files/BWT_decoder.txt", ios::out);
	MTF_decoder_of.open("output_files/MTF_decoder.txt", ios::out);
	Huff_decoder_of.open("output_files/HUFF_decoder.txt", ios::out);
	if (!final_of.is_open() || !RLE_of.is_open() || !BWT_of.is_open() || !RLE_decoder_of.is_open() || !BWT_decoder_of.is_open()) cerr << "ERROR OPEN FILE!";

	cout << "Choose file\n";
	cout << "1 - RLE\n";
	cout << "2 - BWT + RLE\n";
	cout << "3 - BWT + MTF + RLE\n";
	cout << "4 - Huffmam\n";
	cout << "5 - BWT + MTF + RLE + HA\n";
	cout << "6 - BWT\n";
	cout << "Your Choose: ";
	cin >> choose_file;

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
	case 4:
		Huffman_algorithm_HA();
		break;
	case 5:
		BWT_MTF_RLE_HA();
		break;
	case 6:
		BWT();
		break;
	}
}

final_comp::~final_comp() {
	final_of.close();
	RLE_of.close();
	BWT_of.close();
	RLE_decoder_of.close();
	BWT_decoder_of.close();
}

void final_comp::BWT()
{
	locale h;
	string cod;
	string encoded;
	string decoded;

	auto time_coder = 0;
	auto time_decoder = 0;

	unsigned int block_size_1 = 1000;
	unsigned int block_size_2 = 1000;
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

		time_coder += measure<>::execution([&]() { encoded = BWT_encode(cod); });
		//encoded = BWT_encode(cod);
		BWT_of << encoded << endl;

		time_decoder += measure<>::execution([&]() { decoded = BWT_decode(encoded); });
		//decoded = BWT_decode(encoded);
		BWT_decoder_of << decoded << endl;

		final_of << decoded;

		cod.clear();
		encoded.clear();
		decoded.clear();
		strh.clear();
	}
	cout << "Coder BWT: " << time_coder << " ms" << "\n";
	cout << "Decoder BWT: " << time_decoder << " ms" << "\n";
}

void final_comp::Huffman_algorithm_HA()
{
	Huffman_Class huff;

	auto time_coder = 0;
	auto time_decoder = 0;

	string encodedString, decodedString;
	huff.calcFreq(str, str.length());
	huff.HuffmanCodes(str.length());
	cout << "Character With there Frequencies:\n";
	for (auto v = huff.codes.begin(); v != huff.codes.end(); v++)
		cout << v->first << ' ' << v->second << endl;

	for (auto i : str) encodedString += huff.codes[i];

	cout << "\nEncoded Huffman data:\n" << encodedString << endl;

	// Function call
	decodedString = huff.decode_file(huff.minHeap->top(), encodedString);
	cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
}

void final_comp::Run_Length_encoding_RLE() {
	// RLE
	int size;
	int choice;
	string cod;
	//string str = Open_file_RLE(&size, &choice);
	string decoder = Start_RLE(str, &cod, &comp_Rate);
	RLE_of << cod << endl;
	RLE_decoder_of << decoder << endl;
}

void final_comp::BWT_RLE() {
	string str_end;
	string cod;
	string asd;
	string BWT;
	string RLE;
	string RLE_Res;
	string str_h;

	//string RLE_encode;
	//string BWT_encode;
	string compress_final;

	auto time_coder_BWT = 0;
	auto time_decoder_BWT = 0;
	auto time_coder_RLE = 0;
	auto time_decoder_RLE = 0;
	

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

		time_coder_BWT += measure<>::execution([&]() { BWT = BWT_encode(cod); });
		//BWT = BWT_encode(cod);
		BWT_of << BWT << endl;

		time_coder_RLE += measure<>::execution([&]() { RLE = Coder_Run_Len_Encoding(BWT, &comp_Rate); });
		//RLE = Coder_Run_Len_Encoding(BWT, &comp_Rate);
		RLE_of << RLE << endl;

		RLE_Res = Decoder_Run_Len_Encoding(RLE);
		RLE_decoder_of << RLE_Res << endl;

		str_h = BWT_decode(RLE_Res);
		BWT_decoder_of << str_h << endl;

		str_end.append(str_h);
		final_Rate += comp_Rate;

		cod.clear();
		RLE.clear();
		BWT.clear();
		RLE_Res.clear();
		strh.clear();
		str_h.clear();
	}
	//Equal_Text(str, str_end);

	cout << "Coder BWT: " << time_coder_BWT << " ms" << "\n";
	cout << "Coder RLE: " << time_coder_RLE << " ms" << "\n";

	cout << "Compression Rate: " << (1 - ((float)str_end.length()/ (float)str.length())) * 100 << "%";
	
	final_of << str_end << endl;
}

void final_comp::BWT_MTF_RLE_HA()
{
	string str_end;
	string cod;
	string asd;

	string BWT;
	string RLE;
	string RLE_dec;
	string BWT_dec;
	string MTF;
	string MTF_dec;

	Huffman_Class huff;
	string encodedString;
	string decodedString;
	string compress_Huff;

	auto time_coder_BWT = 0;
	auto time_decoder_BWT = 0;
	auto time_coder_MTF = 0;
	auto time_decoder_MTF = 0;
	auto time_coder_RLE = 0;
	auto time_decoder_RLE = 0;
	auto time_coder_HA = 0;
	auto time_decoder_HA = 0;

	//string mtf_decode;

	string list;

	class_MTF mtf;

	for (size_t i = 0; i < 256; i++) {
		list.push_back((char)i);
	}


	unsigned int block_size_1 = 1000;
	unsigned int block_size_2 = 1000;
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

		time_coder_BWT += measure<>::execution([&]() { BWT = BWT_encode(cod); });
		//BWT = BWT_encode(cod);
		BWT_of << BWT << endl;

		vector<int> output_arr;

		//cout << "Move to Front Transform: ";
		string* sre = new string;
		time_coder_MTF += measure<>::execution([&]() { MTF = mtf.mtf_encode(BWT, *sre); });
		//MTF = mtf.mtf_encode(BWT, *sre);
		MTF_of << MTF << endl;

		time_coder_RLE += measure<>::execution([&]() { RLE = Coder_Run_Len_Encoding(*sre); });
		//RLE = Coder_Run_Len_Encoding(*sre);
		RLE_of << RLE << endl;

		//Huffman
		time_coder_HA += measure<>::execution([&]() { huff.calcFreq(RLE, RLE.length()); });
		//huff.calcFreq(RLE, RLE.length());
		time_coder_HA += measure<>::execution([&]() { huff.HuffmanCodes(RLE.length()); });
		//huff.HuffmanCodes(RLE.length());

		for (char i : RLE) {
			encodedString.append(huff.codes[i]);
		}
		//cout << "\nEncoded Huffman data:\n" << encodedString << endl;

		time_coder_HA += measure<>::execution([&]() { compress_Huff = huff.saveHuffCode(encodedString); });
		//compress_Huff = huff.saveHuffCode(encodedString); //saveHuffCode ничего не возвращает!
		Huff_of << compress_Huff << endl;

		decodedString = huff.decode_file(huff.minHeap->top(), encodedString);
		//cout << "\nDecoded Huffman Data:\n" << decodedString << endl;

		//end Huffman

		//cout << "Compression Rate: " << (1 - ((float)(encodedString.length() / 8) / (float)str.length())) * 100 << "%";

		RLE_dec = Decoder_Run_Len_Encoding(decodedString);
		RLE_decoder_of << RLE_dec << endl;

		MTF_dec = mtf.mtf_decode(MTF);
		MTF_decoder_of << MTF_dec << endl;


		//BWT_dec = DeCoder_Burrows_Wheeler_Transform(str, MTF_dec);
		BWT_dec = BWT_decode(MTF_dec);
		BWT_decoder_of << BWT_dec << endl;

		final_of << BWT_dec;

		cod.clear();
		encodedString.clear();
		decodedString.clear();
		compress_Huff.clear();
		strh.clear();
	}
	cout << "Coder BWT: " << time_coder_BWT << " ms" << "\n";
	cout << "Coder MTF: " << time_coder_MTF << " ms" << "\n";
	cout << "Coder RLE: " << time_coder_RLE << " ms" << "\n";
	cout << "Coder HA: " << time_coder_HA << " ms" << "\n";

	cout << "Compression Rate: " << (1 - ((float)(encodedString.length() / 8) / (float)str.length())) * 100 << "%";

	/*
	for (size_t i = 0; i < 1; i++) {
		BWT = BWT_encode(str);
		BWT_of << BWT << endl;

		vector<int> output_arr;

		cout << "Move to Front Transform: ";
		string* sre = new string;
		MTF = mtf.mtf_encode(BWT, *sre);
		MTF_of << MTF << endl;

		RLE = Coder_Run_Len_Encoding(*sre);
		RLE_of << RLE << endl;

		//Huffman
		Huffman_Class huff;
		string encodedString, decodedString;
		huff.calcFreq(RLE, RLE.length());
		huff.HuffmanCodes(RLE.length());

		cout << "Character With there Frequencies:\n";

		for (auto v = huff.codes.begin(); v != huff.codes.end(); v++) cout << v->first << ' ' << v->second << endl;
		for (auto i : RLE) encodedString += huff.codes[i];
		cout << "\nEncoded Huffman data:\n" << encodedString << endl;

		huff.saveHuffCode(encodedString);

		decodedString = huff.decode_file(huff.minHeap.top(), encodedString);
		cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
		//end Huffman

		cout << "Compression Rate: " << (1 - ((float)(encodedString.length() / 8) / (float)str.length())) * 100 << "%";

		RLE_dec = Decoder_Run_Len_Encoding(decodedString);
		RLE_decoder_of << RLE_dec << endl;

		MTF_dec = mtf.mtf_decode(MTF);
		MTF_decoder_of << MTF_dec << endl;


		//BWT_dec = DeCoder_Burrows_Wheeler_Transform(str, MTF_dec);
		BWT_dec = BWT_decode(MTF_dec);
		BWT_decoder_of << BWT_dec << endl;
	}
	*/
}

void final_comp::BWT_MTF_RLE_AC() {
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

		//RLE_of << RLE;
		//BWT_of << BWT;
		//RLE_decoder_of << RLE_dec;
		//BWT_decoder_of << BWT_dec;
		//final_of << RLE;

		//for (size_t i = 0; i < mtf_arr.size(); i++) END1 << mtf_arr[i];
	}
}