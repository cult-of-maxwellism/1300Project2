#include"../headers/spinner.h"

#include<cstdlib>
#include<ctime>

using namespace std;

int spinner () {
    bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    int result = rand()%6;
    return result+1;
}