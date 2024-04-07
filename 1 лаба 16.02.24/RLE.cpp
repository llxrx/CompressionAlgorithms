#include "RLE.h"
const int M_I_N = 0x04;
const int M_A_X = 0x05;

/*
		int i = str.size();
		string letters;

		for (int j = 0; j < i; ++j) {
			int count = 1;
			while (str[j] == str[j + 1]) {
				count++;
				j++;
			}
			letters += std::to_string(count);
			letters.push_back(str[j]);
		}
		enwik7_pre << letters;
		return letters;
		*/

bool isDigit(char c) {
	locale loc;
	return std::isdigit(c, loc);
}

bool Equal_Text(string& str, const string& decoded_str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != decoded_str[i]) {
			cout << "str" << " " << i << " - " << str[i] << "\n";
			cout << "decoded_str" << " " << i << " - " << decoded_str[i] << "\n";
			return false;
		}
		else {
			return true;
		}
	}
}

string Coder_Run_Len_Encoding(string& str, float * compression_Rate_in_percent) {
	string str_2;
	for (size_t i = 0; i < str.length(); i++) {
		int counter = 1;
		/*
		if (isDigit(str[i]) == true) {
			str_2.push_back(str[i]);
			int digit_count = 1;
			while (isDigit(str[i + digit_count]) == true || str[i + digit_count] == '.' || str[i + digit_count] == ',') {
				str_2.push_back(str[i + digit_count]);
				digit_count++;
			}
			//i = digit_count + 1;
			str_2.push_back(SCHAR_MIN);
			i += digit_count - 1;
			continue;
		}
		*/
		while (str[i] == str[i + counter]) {
			counter++;
			if ((i + counter > str.length())) {
				break;
			}
			//i++;
		}
		//cout << "";
		string string_counter = to_string(counter);
		if (counter > 3) {
			str_2.push_back((char)M_I_N);
			str_2.append(string_counter);
			str_2.push_back((char)M_A_X);
			str_2.push_back(str[i]);
			i += counter - 1;
		}
		else {
			str_2.push_back(str[i]);
		}
		
	}
	//cout << str_2 << "\n";
	//cout << "Length before RLE: " << str.length() << "\n";
	//cout << "Length after RLE: " << str_2.length() << "\n";
	float Compression_Rate = (float)str_2.length() / (float)str.length();
	*compression_Rate_in_percent = (1 - Compression_Rate) * 100;
	//cout << "Compression Rate = " << (*compression_Rate_in_percent) << "%" << "\n";
	return str_2;
}

string Coder_Run_Len_Encoding(string& str) {
	string str_2;
	for (size_t i = 0; i < str.length(); i++) {
		int counter = 1;
		/*
		if (isDigit(str[i]) == true) {
			str_2.push_back(str[i]);
			int digit_count = 1;
			while (isDigit(str[i + digit_count]) == true || str[i + digit_count] == '.' || str[i + digit_count] == ',') {
				str_2.push_back(str[i + digit_count]);
				digit_count++;
			}
			//i = digit_count + 1;
			str_2.push_back(SCHAR_MIN);
			i += digit_count - 1;
			continue;
		}
		*/
		while (str[i] == str[i + counter]) {
			counter++;
			if ((i + counter > str.length())) {
				break;
			}
			//i++;
		}
		//cout << "";
		string string_counter = to_string(counter);
		if (counter > 3) {
			str_2.push_back((char)M_I_N);
			str_2.append(string_counter);
			str_2.push_back((char)M_A_X);
			str_2.push_back(str[i]);
			i += counter - 1;
		}
		else {
			str_2.push_back(str[i]);
		}

	}
	//cout << str_2 << "\n";
	//cout << "Length before RLE: " << str.length() << "\n";
	//cout << "Length after RLE: " << str_2.length() << "\n";
	float Compression_Rate = (float)str_2.length() / (float)str.length();
	//*compression_Rate_in_percent = (1 - Compression_Rate) * 100;
	//cout << "Compression Rate = " << Compression_Rate << "%" << "\n";
	return str_2;
}

string Decoder_Run_Len_Encoding(const string& encoded_str) {
	try {
		string number;

		string decoded_text;
		for (size_t i = 0; i < encoded_str.length(); i++) {
			number.clear();
			int count = 1;
			if (encoded_str[i] == (char)M_I_N) {
				int qq = 1;
				int j = 0;
				while (isDigit(encoded_str[i + qq]) == true) {
					number.push_back(encoded_str[i + qq]);
					qq++;
					j++;
				}
				if (j > 1) {
					count = stoi(number);
				}
				else {
					count = encoded_str[i + 1] - '0';
				}
				char c = encoded_str[i + qq + 1];
				decoded_text.append(count, c);
				i += qq + 1;
			}
			else {
				decoded_text.push_back(encoded_str[i]);
			}
		}

		return decoded_text;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}


/*
string Coder_Run_Len_Encoding(string& str) {

	string str_2;
	for (size_t i = 0; i < str.length(); i++) {
		
		int counter = 1;
		//if (str[i] == ' ') continue;
		//cout << isdigit(str[i]);
			if (isDigit(str[i]) == true) {
			str_2.push_back(str[i]);
			int digit_count = 1;
			while (isDigit(str[i + digit_count]) == true || str[i + digit_count] == '.' || str[i + digit_count] == ',') {
				str_2.push_back(str[i + digit_count]);
				digit_count++;
			}
			//i = digit_count + 1;
			str_2.push_back(SCHAR_MIN);
			i += digit_count - 1;
			continue;
 		}
		while (str[i] == str[i + 1]) {
			counter++;
			i++;
		}
		cout << "";
		string string_counter = to_string(counter);
		if (counter > 1) {
			str_2.append(string_counter);
		}
		str_2.push_back(str[i]);
	}
	rle << str_2;
	//cout << str_2 << "\n";
	cout << "Length before RLE: " << str.length() << "\n";
	cout << "Length after RLE: " << str_2.length() << "\n";
	float Compression_Rate = (float)str_2.length()/(float)str.length();
	cout << "Compression Rate = " << ((1 - Compression_Rate)*100) << "%" << "\n";
	return str_2;
}
*/
/*
string Decoder_Run_Len_Encoding(const string& encoded_str) {
	cout << "\n\nDECODER\n\n\n";

	string decoded_text;
	for (size_t i = 0; i < encoded_str.length(); i++) {
		int count = 0;
		while (isDigit(encoded_str[i])) {
			int digit_count = 1;
			int count_for = 0;
			bool flag = false;
			while (isDigit(encoded_str[i + digit_count]) || encoded_str[i + digit_count] == '.' || encoded_str[i + digit_count] == ',') {
				if (encoded_str[i + digit_count] == '.') {
					if (flag == false) {
						decoded_text.push_back(encoded_str[i]);
						flag = true;
					}
					decoded_text.push_back(encoded_str[i + digit_count]);
				}
				else if (isDigit(encoded_str[i + digit_count])) {
					if (flag == true) {
						decoded_text.push_back(encoded_str[i + digit_count]);
					}
					else {
						decoded_text.push_back(encoded_str[i + count_for]);
						count_for++;
					}
				}
				else {
					decoded_text.push_back(encoded_str[i + digit_count]);
				}
				digit_count++;
			}
			if (encoded_str[i + digit_count] == SCHAR_MIN) {
				if (flag == false) {
					decoded_text.push_back(encoded_str[i + digit_count - 1]);
				}
				i += digit_count + 1;
				continue;
			}
			else {
				count = encoded_str[i] - '0';
				i += digit_count;
			}
		}
		if (count == 0) {
			decoded_text.push_back(encoded_str[i]);
		}
		else {
			char c = encoded_str[i];
			decoded_text.append(count, c);
		}
	}
	enwik7_decoder << decoded_text;
	return decoded_text;
}
*/

string Start_RLE(string& str, string *cod, float *comp_Rate) {
	string coder = Coder_Run_Len_Encoding(str, comp_Rate);

	cod->append(coder);

	string decoder = Decoder_Run_Len_Encoding(coder);

	//Equal_Text(str, decoder);
	return decoder;
}