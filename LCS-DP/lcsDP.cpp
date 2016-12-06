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
#include <bits/stdc++.h>

using namespace std;
void printNeatly(string, int);
string pNgreedy(string text, int);
void lcs(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();
    int result = 0;
    int tmp1, tmp2;
    int l = 70;

    int **c = new int*[n + 1];
    for (int i = 0; i < n + 1; i++) {
        c[i] = new int[m + 1];
    }

    for (int i = 0; i <= n; i++){
        c[i][0] = 0;
    }

    for (int j = 0; j <= m; j++) {
        c[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else {
                c[i][j] = c[i - 1][j - 1];
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (c[i][j] > result) {
                result = c[i][j];
                tmp1 = i;
                tmp2 = j;
            }
        }
    }

    cout <<"Length of LCS is: " << result << "\n";
    cout << endl;

    cout << "LCS Score: " << double(result / double(m))*100 << "%" << "\n";
    cout << endl;

    //Print the LCS
    vector<char> printlcs;
    while (c[tmp1][tmp2] != 0) {
        printlcs.push_back(str1[tmp1 - 1]);
        tmp1--;
        tmp2--;
    }
    reverse(printlcs.begin(), printlcs.end());

    vector<char>::iterator it;
    it = printlcs.begin();

    //From vector to string //
    stringstream ss;
    for (int i = 0; i <= printlcs.size(); i++) {
            //if (i != 0)
            //ss << " ";
            ss << printlcs[i];
    }
    string s = ss.str();


    //Print neatly the LCS
    //cout << pNgreedy(s, l) << "\n";
    cout << "Using Printing Neatly Dynamic Programming on LCS ";
    cout << "\n";
    cout << endl;
    printNeatly(s, l);
    cout << "\n";
    cout << endl;

    /*while (it != printlcs.end()) {
        cout << *it;
        it++;
    }*/

    for (int k = 0; k <= n; k++)
        delete c[k];

        delete [] c;


}

