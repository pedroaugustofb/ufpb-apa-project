#include <iostream>
#include <string>
#include "log.h"

using namespace std;


void log(string message) {
    cout << "| " << message << endl;

}

void endl() {
    cout << endl;
}