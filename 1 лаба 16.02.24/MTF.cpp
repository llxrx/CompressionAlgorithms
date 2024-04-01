#include "MTF.h"

/*
int search(char input_char, string& list) {
    for (int i = 0; i < list.length(); i++) {
        if (list[i] == input_char) {
            return i;
        }
    }
    return -1;
}
 
string moveToFront(int curr_index, string& list) {
    string record;
    record = list;
 
    for (int i = curr_index; i > 0; i--) {
        list[i] = record[i - 1];
    }

    list[0] = record[curr_index];

    return list;
}

string moveToFrontForDecoder(int curr_index, string& list) {
    char temp = list[curr_index];
    // Shift elements from curr_index to the beginning by one position
    for (int i = curr_index; i > 0; i--) {
        list[i] = list[i - 1];
    }
    list[0] = temp;
    return list;
}
 
vector<int> mtfEncode(string& input_text, string& list, vector<int> output_arr) {
    //int* output_arr = new int[input_text.length()];
 
    for (int i = 0; i < input_text.length(); i++) {
 
        output_arr.push_back(search(input_text[i], list));
 
        cout << output_arr[i] << " ";
 
        moveToFront(output_arr[i], list);
    }

    return output_arr;
}

string mtfDecode(string& initial_list, vector<int>& encoded_data) {
    string decoded_text;
    string list = initial_list; // Use a copy to avoid modifying original list

    for (int code : encoded_data) {
        if (code == -1) {
            // Handle invalid code (character not found)
            // You can throw an exception, return an error code, or handle it differently
            decoded_text += '?'; // Or any appropriate placeholder
        }
        else {
            decoded_text += list[code];
            list = moveToFront(code, list);
        }
    }

    return decoded_text;
}

string mtf_dec(string& symbolTable, vector<int>& output) {
    string r;
    for (vector<int>::iterator it = output.begin(); it != output.end(); it++)
    {
        r.append(1, symbolTable[*it]);
        moveToFront(*it, symbolTable);
    }
    return r;
}
*/