#include "Arithmetic_coding.h"

map<char, double>Probability(string& str) {
    double prob = 0.0;
    double final_prob = 0.0;
    char alf_str;
    string new_str = str;
    bool flag = true;
    map<char, double> arithmetic_mmap;

    int size = new_str.length();

    unsigned int count = 0;
    while(new_str.length()) {
        alf_str = new_str[0];
        for (size_t j = 0; j < new_str.length(); j++) {
            if (new_str[j] == alf_str) {
                count++;
            }
        }
        char a = new_str[0];
        new_str.erase(remove(new_str.begin(), new_str.end(), a), new_str.end());
        prob = ((double)count / (double)size);
        final_prob += prob;
        
        arithmetic_mmap.emplace(alf_str, prob);

        count = 0;
    }

    return arithmetic_mmap;
}

vector<double> Probability_vector(string str) {
    double prob = 0.0;
    double final_prob = 0.0;
    char alf_str;
    string new_str = str;
    bool flag = true;
    vector<double> arithmetic_mmap;

    int size = new_str.length();

    unsigned int count = 0;
    while (new_str.length()) {
        alf_str = new_str[0];
        for (size_t j = 0; j < new_str.length(); j++) {
            if (new_str[j] == alf_str) {
                count++;
            }
        }
        char a = new_str[0];
        new_str.erase(remove(new_str.begin(), new_str.end(), a), new_str.end());
        prob = ((double)count / (double)size);
        final_prob += prob;

        arithmetic_mmap.push_back(prob);

        count = 0;
    }

    return arithmetic_mmap;
}

void arithm_video(string str) {
    vector<double> p;

    p.push_back(0.2);
    p.push_back(0.4);
    p.push_back(0.4);

    double s = 0.0;

    vector<double> c;
    c.push_back(0.0);
    vector<double> d;
    for (size_t i = 1; i < str.length(); i++) {
        s += p[i-1];
        c.push_back(s);
    }
    for (size_t i = 0; i < str.length(); i++)
    {
        d.push_back(c[i] + p[i]);
    }

    double low = 0.0;
    double high = 1.0;

    for (size_t i = 0; i < str.length(); i++) {
        double range = high - low;
        high = low + range * d[(str[i] - '0')];
        low = low + range * c[(str[i] - '0')];
    }
}

string Arithmetic_Coding::Arithmetic_Encoder(string& str)
{
    //arithm_video(str);

    //map<char, double>Prob = Probability(str);
    
    //vector<double> Prob = Probability_vector(str);

    vector<double> Prob;
    Prob.push_back(0.2);
    Prob.push_back(0.4);
    Prob.push_back(0.4);

    vector<char> x;
    char e = ' ';
    for (size_t i = 0; i < str.length(); i++) {
        if (e == str[i]) continue;
        e = str[i];
        x.push_back(str[i]);
    }

    sort(x.begin(), x.end());

    double s = 0.0;

    
    c.push_back(0.0);
    for (size_t i = 1; i < Prob.size(); i++) {;
        s += Prob[i - 1];
        c.push_back(s);
    }
    for (size_t i = 0; i < Prob.size(); i++) {
        d.push_back(c[i] + Prob[i]);
    }

    double low = 0.0;
    double high = 1.0;

    for (size_t i = 0; i < str.size(); i++) {
        double range = high - low;
        high = low + range * d[(str[i] - '0')];
        low = low + range * c[(str[i] - '0')];
    }


    // ---BINARY---
    int Counter = 0;

    while (high < 0.5 || low > 0.5) {
        if (high < 0.5) {
            byte.push_back('0');
            low = 2 * low;
            high = 2 * high;
        }
        else if(low > 0.5) {
            byte.push_back('1');
            low = 2 * (low - 0.5);
            high = 2 * (high - 0.5);
        }
    }

    while (low > 0.25 && high < 0.75) {
        Counter += 1;
        low = 2 * (low - 0.25);
        high = 2 * (high - 0.25);
    }
    Counter += 1;

    if (low <= 0.25) {
        byte.push_back('0');
        byte.append('1', Counter);
    }
    else {
        byte.push_back('1');
        byte.append('0', Counter);
    }

    return byte;
}

void Arithmetic_Coding::Arithmetic_DeCoding() {
    int z = stoi(byte);

    double low = 0.0;
    double high = 1.0;

    double w;
    while (1) {
        for (size_t i = 0; i < byte.length(); i++) {
            w = high - low;
            high = low + w * d[i];
            low = low + w * c[i];
            if (low <= z || high > z) {
                final_str.push_back(i);
                if (i == 0) {
                    break;
                }
            }
        }
        break;
    }

}