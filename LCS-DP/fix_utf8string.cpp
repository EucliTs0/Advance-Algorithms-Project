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
#include <locale.h>
#include <locale>
#include <cassert>
#include <utf8.h>

using namespace std;
using namespace utf8;

void fix_utf8_string(string& str) {
    string temp;
    replace_invalid(str.begin(), str.end(), back_inserter(temp));
    str = temp;

}
