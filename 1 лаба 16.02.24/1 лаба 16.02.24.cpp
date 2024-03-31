#include <iostream>
#include <chrono>
#include <locale>
#include "RLE.h"
#include "BTW.h"
#include "OPEN_BWT_FILE.h"
#include "MTF.h"
#include "Arithmetic_coding.h"
#include "Entropia.h"

struct file_name_enum {
	string enwik7 = "Text_files/enwik7.txt";
	string test = "Text_files/test.txt";
	string Russian_text = "Text_files/Russian_Text.txt";
	string image = "image_files/house.bmp";
	string raw_white_black = "image_files/image_5.bmp";
	string raw_grey = "image_files/image_1.bmp";
};

int main() {
	file_name_enum f;
	map<int, string> file_name_map;
	file_name_map.emplace(1, f.enwik7);
	file_name_map.emplace(2, f.test);
	file_name_map.emplace(3, f.Russian_text);
	file_name_map.emplace(4, f.image);
	file_name_map.emplace(5, f.raw_white_black);
	file_name_map.emplace(6, f.raw_grey);



	float comp_Rate;
	unsigned int choose_file;
	cout << "Choose file\n";
	cout << "1 - RLE\n";
	cout << "2 - BWT + RLE\n";
	cout << "3 - MTF\n";
	cout << "Your Choose: ";
	cin >> choose_file;

	switch (choose_file) {
	case 1: {
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

		file_name = file_name_map[choose];

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
		break;
	}
	case 2: {
		ofstream END_BWT("output_files/END_BWT.bmp", ios::out);
		ofstream END("output_files/END.bmp", ios::out);
		ofstream END1("output_files/END.txt", ios::out);
		ofstream final("output_files/FINAL.txt", ios::out);

		string str;
		string strh;
		string file_name;
		unsigned int choose;
		file_name_enum f_n_e;

		cout << "Choose file\n";
		cout << "1 - enwik7\n";
		cout << "2 - test\n";
		cout << "3 - Russian_text\n";
		cout << "4 - image\n";
		cout << "5 - raw white-black\n";
		cout << "6 - raw grey\n";
		cout << "Your Choose: ";
		cin >> choose;

		file_name = file_name_map[choose];

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
			string BWT = Coder_Burrows_Wheeler_Transform(cod);
			string RLE_Res = Start_RLE(BWT, &asd, &comp_Rate);
			final_Rate += comp_Rate;
			
			string strh = DeCoder_Burrows_Wheeler_Transform(str, RLE_Res);
			str_end.append(strh);

			cod.clear();
			BWT.clear();
			RLE_Res.clear();
			strh.clear();
		}
		cout << "Final Compression Rate - " << (final_Rate / size) << "%";
		END << asd;
		END1 << asd;
		final << str_end;
		END_BWT << str_end;

		END.close();
		END_BWT.close();
		break;
	}
	case 3:
	{
		ofstream END_BWT("output_files/END_BWT.bmp", ios::out);
		ofstream END("output_files/END.bmp", ios::out);
		ofstream END1("output_files/END.txt", ios::out);
		ofstream final("output_files/FINAL.txt", ios::out);

		string str;
		string strh;
		string file_name;
		unsigned int choose;
		file_name_enum f_n_e;

		cout << "Choose file\n";
		cout << "1 - enwik7\n";
		cout << "2 - test\n";
		cout << "3 - Russian_text\n";
		cout << "4 - image\n";
		cout << "5 - raw white-black\n";
		cout << "6 - raw grey\n";
		cout << "Your Choose: ";
		cin >> choose;

		file_name = file_name_map[choose];

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

		string list;

		for (size_t i = 0; i < 256; i++) {
			list.push_back((char)i);
		}

		

		for (size_t i = 0; i < 1; i++) {
			string BWT = Coder_Burrows_Wheeler_Transform(str);

			int* output_arr = new int[BWT.length()];

			cout << "Move to Front Transform: ";

			int* mtf_arr = mtfEncode(BWT, list, output_arr);

			END1 << mtf_arr;
		}
	}
	}

	//Entropy
	//double result = entropy(probabilities);
	//cout << "Entropy: " << result << endl;

	return 0;
}