#include "MTF.h"

int search(char input_char, string& list) {
    for (int i = 0; i < list.length(); i++) {
        if (list[i] == input_char) {
            return i;
        }
    }
    return -1;
}
 
void moveToFront(int curr_index, string& list) {
    string record;
    record = list;
 
    for (int i = curr_index; i > 0; i--) {
        list[i] = record[i - 1];
    }

    list[0] = record[curr_index];
}
 
int* mtfEncode(string& input_text, string& list, int* output_arr) {
    //int* output_arr = new int[input_text.length()];
 
    for (int i = 0; i < input_text.length(); i++) {
 
        output_arr[i] = search(input_text[i], list);
 
        cout << output_arr[i] << " ";
 
        moveToFront(output_arr[i], list);
    }

    return output_arr;
}