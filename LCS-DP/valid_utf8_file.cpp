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

bool validUTF8_file(const char *filename){
    ifstream ifs(filename);
    if (!ifs)
        return false;
    istreambuf_iterator<char> it(ifs.rdbuf());
    istreambuf_iterator<char> eos;

    return utf8::is_valid(it, eos);
}
