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

#define MAXINT INT_MAX

using namespace std;


/* M is the width of every line printed

   n is the length of words */

int giveLines(int *, int, vector<string>, int);

void printNeatly(vector<string> words, int M){
    /* Let extras[1...n, 1...n], lc[1...n, 1...n] and c[0...n]
    be new arrays */

    int n = words.size();

    int extras[n + 1][n + 1]; /* white spaces in a line */
    int lc[n + 1][n + 1]; /* Line Cost */
    int c[n + 1]; /* Total Cost */
    int p[n + 1];


    /* Compute extras[i,j] for 1 <= i <= j <= n */
    int i;
    int j;

    for (i = 1; i <= n; i++) {
        extras[i][i] = M - words[i - 1].size();
        for (j = i + 1; j <= n; j++) {
            extras[i][j] = extras[i][j - 1] - words[j - 1].size() - 1;
        }
    }

    /* Compute lc[i, j] for 1 <= i <= j <= n */
    for (i = 1; i <= n; i++){
        for (j = i; j <= n; j++) {
            if (extras[i][j] < 0)
                lc[i][j] = MAXINT;
            else if (j == n && extras[i][j] >= 0)
                lc[i][j] = 0;
            else
                lc[i][j] = pow(extras[i][j], 3);
        }
    }

    /* Compute c[j] and p[j] for 1 <= j <= n */
    c[0] = 0;
    for (j = 1; j <= n; j++){
        c[j] = MAXINT;

        for (i = 1; i <= j; i++){
            if ((c[i - 1] + lc[i][j]) < c[j] && c[i - 1] != MAXINT && lc[i][j] != MAXINT) {
                c[j] = c[i - 1] + lc[i][j];
                p[j] = i;
            }
        }
    }
    giveLines(p, n, words, M);
    	cout << "Total Cost (Penalty): " << c[n] << endl;
}

int giveLines (int p[], int n, vector<string> words, int M) {
    int i, k;

    if (p[n] == 1)
        k = 1;
    else
        k = giveLines(p, p[n] - 1, words, M) + 1;
        int s  = 0; /* size */
        int wordsInLine = 0;
        for (i = p[n]; i <=n; i++) {
            s += words[i - 1].size();
            cout << words[i - 1] << " ";
            wordsInLine++;
        }
        int spaces = M - s;
        if (wordsInLine > 1) {
            spaces = abs(spaces - (wordsInLine - 1));
        }
        cout << string(spaces, ' ') << " | " << spaces << endl;

        return k;

}



