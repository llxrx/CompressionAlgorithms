#include "Arithmetic_coding.h"

map<char, double>Probability(string& str) {
    double prob = 0.0;
    char alf_str;
    string new_str;
    bool flag = true;
    map<char, double> arithmetic_mmap;

    int size = str.length();

    unsigned int count = 0;
    while(str.length()) {
        alf_str = str[0];
        for (size_t j = 0; j < str.length(); j++) {
            if (str[j] == alf_str) {
                count++;
            }
        }
        char a = str[0];
        str.erase(remove(str.begin(), str.end(), a), str.end());
        prob = ((double)count / (double)size);
        
        arithmetic_mmap.emplace(alf_str, prob);

        count = 0;
    }

    return arithmetic_mmap;
}

struct {
    static pair<double, double> getProbability(char c, char c_1, map<char, double> mmap)
    {
        //if (c >= mmap.begin() && c <= mmap.end())
        return make_pair(mmap[c], mmap[c_1]);
        //else
            //throw "character out of range";
    }
    static char getSymbol(double d, string &str)
    {
        if (d >= 0.0 && d < 0.26)
            return 'A' + static_cast<int>(d * str.length());
        else
            throw "message out of range";
    }
} model;



double Arithmetic_Coding(string& str)
{
    string str_ = str;
    map<char, double> Coding_mmap = Probability(str);
    double high = 1.0;
    double low = 0.0;
    for (size_t i = 0; i < str_.length(); i++) {
        char c = str_[i];
        char c_1 = str_[i + 1];
        pair<double, double> p = model.getProbability(c, c_1, Coding_mmap);
        double range = high - low;
        high = low + range * p.second;
        low = low + range * p.first;
     }
    double end = low + (high - low) / 2;
    cout << setprecision(11) << end << "\n";

    return end;
}

void Arithmetic_DeCoding(double message, string& str, map<char, double> mmap) {
    double high = 1.0;
    double low = 0.0;
    for (; ; )
    {
        double range = high - low;
        char c = model.getSymbol((message - low) / range, str);
        char c_1 = model.getSymbol((message - low) / range, str);
        cout << c;
        if (c == 'Z')
            return ;
        pair<double, double> p = model.getProbability(c, c_1, mmap);
        high = low + range * p.second;
        low = low + range * p.first;
    }
}