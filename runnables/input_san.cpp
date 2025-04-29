#include"../headers/input_san.h"
#include<iostream>

using namespace std;

int input_san() {
    string sanString = "";
    cin.clear();
    cin >> sanString;
    int string_len = sanString.length();
    int final = -1;
    for (int i = 0; i < string_len; i++) {
        if (sanString[i] >= '0' && sanString[i] <= '9') {
            if (i == 0) {
                final = sanString[i]-'0';
            } else {
                final = final*10+(sanString[i]-'0');
            }
        }
    }
    return final;
}