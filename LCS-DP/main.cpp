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
string pNgreedy(string, int);
void printNeatly(vector<string>, int);
char *lcs2(char*, char*);
//string lcs_DnC(string, string);
char *convert(const std::string & s);
int count_lcs(string, string);
bool validUTF8_file(const char*);
void fix_utf8_string(string&);
//void remove_sw(string, string);
void stripChars(string&);

int main() {
    string illegalChars = """""\\/:?,.=''-_+)[]:<>(|";
    int n = 70;
    int L;
    //Checking if files are in utf8 encoding
    validUTF8_file("corpus/g4pD_taskc.txt");
    validUTF8_file("corpus/orig_taskc.txt");
        ifstream mytextfile;

    try {
        mytextfile.open("corpus/g4pD_taskc.txt");
        if (!mytextfile) {
            cout << "Error opening file " << endl;
            return 1;
        }
    }

    catch (ifstream::failure()) {
        cout << "Exception opening file " << endl;

    }
    ifstream originalfile;

    try {
        originalfile.open("corpus/orig_taskc.txt");
        if (!originalfile) {
            cout << "Error opening file " << endl;
            return 1;
        }
    }

    catch (ifstream::failure()) {
        cout << "Exception opening file " << endl;
    }

    ifstream dictionary;
    dictionary.open("stop-word-list.txt");

    vector<string> stopwords;
    string stopwordlist;

    while (dictionary >> stopwordlist) {
        stopwords.push_back(stopwordlist);
    }

    stringstream temp;
    for (int i = 0; i <= stopwords.size() - 1; i++) {
            if (i != 0)
            temp << " ";
            temp << stopwords[i];
    }
    //create a string with the stop words
    string dict = temp.str();



    /* for (int i = 0; i < n; i++)
	{
		cout << i % 10;
	}
	cout << "  |  padding spaces" << endl;
	cout << "<";
	for (int i = 0; i < n - 2; i++)
	{
		cout << "-";
	}
	cout << ">  |" << endl; */

        vector<string> words;
        vector<string> words_original;
        string word;
        string word_original;

    while (mytextfile >> word) {

        words.push_back(word);

    }


    while (originalfile >> word_original) {
        words_original.push_back(word_original);
    }

    //From <vector>string to string

    stringstream ss;
    stringstream ss1;
    for (int i = 0; i <= words.size() - 1; i++) {
            if (i != 0)
            ss << " ";
            ss << words[i];
    }

    for (int i = 0; i <= words_original.size() - 1; i++) {
            if (i != 0)
            ss1 << " ";
            ss1 << words_original[i];
    }

        string text = ss.str();
        string original_text = ss1.str();

        //Remove illegal characters
        string::iterator it;

        for(it = text.begin(); it < text.end(); it++) {
            bool found = illegalChars.find(*it) != string::npos;
            if(found) {
                *it = ' ';
            }
        }

        for(it = original_text.begin(); it < original_text.end(); it++) {
            bool found = illegalChars.find(*it) != string::npos;
            if(found) {
                *it = ' ';
            }
        }

        //transform to lower-case
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        transform(original_text.begin(), original_text.end(), original_text.begin(), ::tolower);

        //Function to remove stopwords. So slow...

       //removeSubStrings(text, dict);
       // removeSubStrings(original_text, dict);


        //Check if strings are in utf8
        fix_utf8_string(text);
        fix_utf8_string(original_text);

        //Remove any non-ASCII characters
        stripChars(text);
        stripChars(original_text);

        //From string to char*
        char* wordsc = new char[text.length() + 1];
        char* words_originalc = new char [original_text.length() + 1];
        strcpy(wordsc, text.c_str());
        strcpy(words_originalc, original_text.c_str());

        cout << pNgreedy(text, n);
        cout << endl;
        cout << endl;
        cout << endl;

        cout << pNgreedy(original_text, n);
        cout << endl;
        cout << endl;
        cout << endl;

        string result;
        result = lcs2(wordsc, words_originalc);


         cout << endl;
         cout << "LCS is: " << result;
         cout << endl;
         L = count_lcs(text, original_text);
         cout << endl;
         cout << "Length of LCS: " << L;

    // printNeatly(result, n);
    cout << endl;
    cout << endl;
    cout << pNgreedy(result, n) << endl;

    delete [] wordsc;
    delete [] words_originalc;

    return 0;



}





