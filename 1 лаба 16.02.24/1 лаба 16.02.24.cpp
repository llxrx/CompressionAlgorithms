#include <iostream>
#include <locale>
#include "RLE.h"
#include "BTW.h"
#include "OPEN_BWT_FILE.h"
#include "MTF.h"
#include "Arithmetic_coding.h"
#include "Entropia.h"

struct file_name_enum {
	string enwik7 = "enwik7.txt";
	string test = "test.txt";
	string image = "image.txt";
	string raw_white_black = "output_png.bmp";
	string raw_grey = "output_jpg.raw";
};

int main() {
	float comp_Rate;
	unsigned int choose_file;
	cout << "Choose file\n";
	cout << "1 - RLE\n";
	cout << "2 - BWT\n";
	cout << "Your Choose: ";
	cin >> choose_file;

	switch (choose_file) {
	case 1: {
		// RLE
		int size;
		int choice;
		string cod;
		string str = Open_file_RLE(&size, &choice);
		Start_RLE(str, &cod, &comp_Rate);
		break;
	}
	case 2: {
		ofstream END_BWT("END_BWT.bmp", ios::out);
		ofstream END("END.bmp", ios::out);
		ofstream END1("END.txt", ios::out);

		string str;
		string strh;
		string file_name;
		unsigned int choose;
		file_name_enum f_n_e;

		cout << "Choose file\n";
		cout << "1 - enwik7\n";
		cout << "2 - test\n";
		cout << "3 - image\n";
		cout << "4 - raw white-black\n";
		cout << "5 - raw grey\n";
		cout << "Your Choose: ";
		cin >> choose;

		if (choose == 1) {
			file_name = f_n_e.enwik7;
		}
		else if (choose == 2) {
			file_name = f_n_e.test;
		}
		else if (choose == 3) {
			file_name = f_n_e.image;
		}
		else if (choose == 4) {
			file_name = f_n_e.raw_white_black;
		}
		else if (choose == 5) {
			file_name = f_n_e.raw_grey;
		}

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

		unsigned int block_size_1 = 400;
		unsigned int block_size_2 = 400;
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
		END_BWT << str_end;

		END.close();
		END_BWT.close();
		break;
	}
	}

	//Entropy
	//double result = entropy(probabilities);
	//cout << "Entropy: " << result << endl;

	double c = Arithmetic_Coding();
	Arithmetic_DeCoding(c);
	cout << "\n\n\n\n";
	
	MTF mtf;
	string a, b, start_str = "to be or not to be";
	string str = Coder_Burrows_Wheeler_Transform(start_str);

	a = str;
	cout << a << " -> encoded = ";
	a = mtf.encode(a);
	b = mtf.decode(a);
	cout << a << "; \ndecoded = " << mtf.decode(a) << "\n\n";

	string end_str = DeCoder_Burrows_Wheeler_Transform(str, b);
	cout << end_str << "\n";

	return 0;
}