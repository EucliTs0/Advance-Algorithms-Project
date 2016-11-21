#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <math.h>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <locale.h>
#include <utf8.h>
#include <locale>

using namespace std;
bool invalidChar( char c) {
    return !(c >= 0 && c < 128);
}

void stripChars( string &s) {
    s.erase(remove_if(s.begin(), s.end(), invalidChar), s.end());
}
