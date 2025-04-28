#include"../headers/spinner.h"

#include<cstdlib>
#include<ctime>
#include<iostream>

using namespace std;

int spinner () {
    bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    int result = rand()%6;
    cout << "You rolled a " << result+1 << endl;
    return result+1;
}