#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include <math.h>
#include <cmath>
#include <sstream>
#include <algorithm>

#define NEITHER 0
#define UP 1
#define LEFT 2
#define UP_AND_LEFT 3

using namespace std;

char* lcs2(char *x, char *y) {
    int n = strlen(x);
    int m = strlen(y);
    int i, j, pos;
    char* lcs_p;

    int **c = new int*[(n + 1)*sizeof(int)];
    int **b = new int*[(n + 1)*sizeof(int)];

    for (i = 0; i <= n; i++) {
        c[i] = new int[(m + 1)*sizeof(int)];
        b[i] = new int[(m + 1)*sizeof(int)];
    }

    /* Initialization */

    for (i = 0; i <= n; i++){
        c[i][0] = 0;
        b[i][0] = UP;
    }

    for (j = 0; j <= m; j++){
        c[0][j] = 0;
        b[0][j] = LEFT;
    }

    /* DP */

    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++){
            if (x[i - 1] == y[j - 1]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = UP_AND_LEFT;
            }
            else {
                c[i][j] = c[i - 1][j - 1];
                b[i][j] = NEITHER;
            }
            if (c[i - 1][j] >= c[i][j]){
                c[i][j] = c[i - 1][j];
                b[i][j] = UP;
            }
            if (c[i][j - 1] >= c[i][j]){
                c[i][j] = c[i][j - 1];
                b[i][j] = LEFT;
            }
        }
    }

    /* Length of LCS is c[n][m] */

    i = n;
    j = m;
    pos = c[i][j];

    lcs_p = new char[(pos + 1)*sizeof(char)];

    lcs_p[pos--] = 0;

    while ( i > 0 || j > 0){
        if (b[i][j] == UP_AND_LEFT){
            i--;
            j--;
            lcs_p[pos--] = x[i];
        }
        else if (b[i][j] == UP){
            i--;
        }
        else if (b[i][j] == LEFT){
            j--;
        }
    }
    cout << "Length of LCS is: " << c[n][m];
    double D = double(c[n][m]) / double(min(m, n));
    cout << endl;

    /*for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            cout << b[x][y] << " ";
        }
    }*/

    for (i = 0; i <= n; i++){
        delete c[i];
        delete b[i];
    }
    delete [] c;
    delete [] b;
    cout << endl;
    cout << "LCS score: " << D;

    return lcs_p;
}


