#include "BTW.h"

const int STX = 0x02;
const int ETX = 0x03;

void rotate(string& a) {
	char t = a[a.length() - 1];
	for (int i = a.length() - 1; i > 0; i--) {
		a[i] = a[i - 1];
	}
	a[0] = t;
}

string bwt(const string& s) {
	for (char c : s) {
		if (c == STX || c == ETX) {
			throw runtime_error("Input can't contain STX or ETX");
		}
	}

	string ss;
	ss += STX;
	ss += s;
	ss += ETX;

	vector<string> table;
	for (size_t i = 0; i < ss.length(); i++) {
		table.push_back(ss);
		rotate(ss);
	}
	//table.sort();
	sort(table.begin(), table.end());

	string out;
	for (auto& s : table) {
		out += s[s.length() - 1];
	}
	return out;
}

string ibwt(const string& r) {
	int len = r.length();
	vector<string> table(len);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			table[j] = r[j] + table[j];
		}
		sort(table.begin(), table.end());
	}
	for (auto& row : table) {
		if (row[row.length() - 1] == ETX) {
			return row.substr(1, row.length() - 2);
		}
	}
	return {};
}

string makePrintable(const string& s) {
	auto ls = s;
	for (auto& c : ls) {
		if (c == STX) {
			c = '^'; //start
		}
		else if (c == ETX) {
			c = '|'; //end
		}
	}
	return ls;
}

string Coder_Burrows_Wheeler_Transform(string& s) {
	ofstream BWT_OUT("BWT_OUT.raw", ios::out);
	auto tests = { 
		s
	};

	for (auto& test : tests) {
		//cout << makePrintable(test) << "\n";
		//cout << " --> ";

		string t;
		try {
			t = bwt(test);
			//cout << makePrintable(t) << "\n";
			BWT_OUT << t;
			return t;
		}
		catch (runtime_error& e) {
			cout << "Error " << e.what() << "\n";
		}

		string r = ibwt(t);
		//cout << " --> " << r << "\n\n";
	}
}

string DeCoder_Burrows_Wheeler_Transform(string& s, string& t) {
	ofstream BWT_RES("BWT_RES.txt", ios::out);
	auto tests = { 
		s
	};

	for (auto& test : tests) {
		string r = ibwt(t);
		//cout << " --> " << r << "\n\n";
		BWT_RES << r;
		return r;
	}
}

string Start_BWT(string& str) {
	string BWT = Coder_Burrows_Wheeler_Transform(str);
	string BWT_RESULT = DeCoder_Burrows_Wheeler_Transform(str, BWT);
	return BWT;
}
