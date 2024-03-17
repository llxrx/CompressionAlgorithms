#include "Arithmetic_coding.h"

struct {
    static std::pair<double, double> getProbability(char c)
    {
        if (c >= 'A' && c <= 'Z')
            return std::make_pair((c - 'A') * .01, (c - 'A') * .01 + .01);
        else
            throw "character out of range";
    }
    static char getSymbol(double d)
    {
        if (d >= 0.0 && d < 0.26)
            return 'A' + static_cast<int>(d * 100);
        else
            throw "message out of range";
    }
} model;



double Arithmetic_Coding()
{
    double high = 1.0;
    double low = 0.0;
    string c = "WXYZ";
    for (char s : c) {
        std::pair<double, double> p = model.getProbability(s);
        double range = high - low;
        high = low + range * p.second;
        low = low + range * p.first;
    }
    double end = low + (high - low) / 2;
    cout << setprecision(11) << end;

    return end;
}

void Arithmetic_DeCoding(double message) {
    double high = 1.0;
    double low = 0.0;
    for (; ; )
    {
        double range = high - low;
        char c = model.getSymbol((message - low) / range);
        std::cout << c;
        if (c == 'Z')
            return ;
        std::pair<double, double> p = model.getProbability(c);
        high = low + range * p.second;
        low = low + range * p.first;
    }
}