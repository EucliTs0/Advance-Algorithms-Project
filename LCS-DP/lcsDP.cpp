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
#include <set>

using namespace std;

string lcs(string& str1, string& str2) {
    if (str1.empty() || str2.empty()) {
        return 0;
    }

    int *curr = new int[str2.size()];
    int *prev = new int[str2.size()];
    int *s = nullptr;
    int maxSubstr = 0;
    string longest;

    for (unsigned int i = 0; i < str1.size(); i++) {
        for (unsigned int j = 0; j < str2.size(); j++) {
            if (str1[i] != str2[j]) {
                curr[j] = 0;
            }
            else {
                if (i == 0 || j == 0) {
                    curr[j] = 1;
                }
                else {
                    curr[j] = 1 + prev[j - 1];
                }
                if (maxSubstr < curr[j]) {
                    maxSubstr = max(maxSubstr, curr[j]);
                    longest.clear();


                    //cout << longest.append(str1.substr(i - maxSubstr + 1, i + 1));
                }
                if (maxSubstr == curr[j]) {
                    longest.append(str1.substr(i - maxSubstr + 1, i + 1));

                    }
                }
            }
            s = curr;
            curr = prev;
            prev = s;
        }




    delete [] curr;
    delete [] prev;
    cout << "Length of LCS is: " << longest.size();
    cout << endl;
    return longest;
}

