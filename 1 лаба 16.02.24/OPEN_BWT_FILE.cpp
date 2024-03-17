#include "OPEN_BWT_FILE.h"

string Open_file_RLE(int *size, int *choose_file) {
	locale loc;
	ifstream enwik8("enwik8.txt", ios::in);
	ifstream enwik7("enwik7.txt", ios::in);
	ifstream image("image.txt", ios::in);

	ifstream RAW("output_png.bmp", ios::in);
	ifstream RAW_grey("output_jpg.raw", ios::in);

	ifstream test("test.txt", ios::in);

	string str;
	string strh;

	cout << "Choose file\n";
	cout << "1 - enwik7\n";
	cout << "2 - test\n";
	cout << "3 - image\n";
	cout << "4 - raw white-black\n";
	cout << "5 - raw grey\n";
	cout << "Your Choose: ";
	cin >> (*choose_file);

	switch (*choose_file)
	{
	case 1: {
		while (!enwik7.eof()) {
			getline(enwik7, strh);
			str += strh;
			if (!enwik7.eof()) {
				str += '\n';
			}
		}
		(*size) = str.length() / 400;
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 2: {
		while (!test.eof()) {
			getline(test, strh);
			str += strh;
			if (!test.eof()) {
				str += '\n';
			}
		}
		(*size) = str.length() / 400;
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 3: {
		while (!image.eof()) {
			getline(image, strh);
			str += strh;
			if (!image.eof()) {
				str += '\n';
			}
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 4: {
		while (!RAW.eof()) {
			getline(RAW, strh);
			str += strh;
			if (!RAW.eof()) {
				str += '\n';
			}
		}
		(*size) = str.length() / 400;
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 5: {
		while (!RAW_grey.eof()) {
			getline(RAW_grey, strh);
			str += strh;
			if (!RAW_grey.eof()) {
				str += '\n';
			}
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	}
	return str;
}

string Open_file_BWT(int size, int *choose_file) {
	locale loc;
	ifstream enwik8("enwik8.txt", ios::in);
	ifstream enwik7("enwik7.txt", ios::in);
	ifstream image("image.txt", ios::in);

	//ifstream RAW("output_png.raw", ios::in);
	ifstream RAW("output_png.bmp", ios::in);
	ifstream RAW_grey("output_jpg.raw", ios::in);

	ifstream test("test.txt", ios::in);

	string str;
	string strh;
	switch (*choose_file)
	{
	case 1: {
		int count = 400 * size;
		int zxc = count / size;
		char sim;
		bool flag = false;
		for (int i = 0; i < 400; i++) {
			if (count > 400 && flag == false) {
				for (int i = 0; i < (count - 400); i++) {
					enwik7.get(sim);
				}
				flag = true;
			}
			enwik7.get(sim);
			str.push_back(sim);
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 2: {
		int count = 400 * size;
		int zxc = count / size;
		char sim;
		bool flag = false;
		for (int i = 0; i < 400; i++) {
			if (count > 400 && flag == false) {
				for (int i = 0; i < (count-400); i++) {
					test.get(sim);
				}
				flag = true;
			}
			test.get(sim);
			str.push_back(sim);
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 3: {
		while (!image.eof()) {
			getline(image, strh);
			str += strh;
			if (!image.eof()) {
				str += '\n';
			}
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 4: {
		int count = 400 * size;
		int zxc = count / size;
		char sim;
		bool flag = false;
		for (int i = 0; i < 400; i++) {
			if (count > 400 && flag == false) {
				for (int i = 0; i < (count - 400); i++) {
					RAW.get(sim);
				}
				flag = true;
			}
			RAW.get(sim);
			str.push_back(sim);
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	case 5: {
		while (!RAW_grey.eof()) {
			getline(RAW_grey, strh);
			str += strh;
			if (!RAW_grey.eof()) {
				str += '\n';
			}
		}
		cout << "file lenght - " << str.length() << "\n";
	}
		  break;
	}
	return str;
}