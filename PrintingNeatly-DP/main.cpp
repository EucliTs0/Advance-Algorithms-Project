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

void lcs(string, string);
string pNgreedy(string, int);
void printNeatly(string, int);
char *lcs2(char*, char*);
char *convert(const std::string & s);
bool validUTF8_file(const char*);
void fix_utf8_string(string&);
//void remove_sw(string, string);
void stripChars(string&);
string lcs_DnC(string , string);


int main() {
    string illegalChars = """""\?,.=''-_+)[]{}:</>(|";
    int n = 70;
    int L;
    //Checking if files are in utf8 encoding
    validUTF8_file("corpus/g2pC_taskd.txt");
    validUTF8_file("corpus/orig_taskd.txt");
        ifstream mytextfile;

    try {
        mytextfile.open("corpus/g2pC_taskd.txt");
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
        originalfile.open("corpus/orig_taskd.txt");
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

    //From vector<string> to string

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
        /*char* wordsc = new char[text.length() + 1];
        char* words_originalc = new char [original_text.length() + 1];
        strcpy(wordsc, text.c_str());
        strcpy(words_originalc, original_text.c_str());*/

        printNeatly(text, n);
        cout << "\n";
        cout << endl;


        //cout << pNgreedy(original_text, n) << "\n";
        printNeatly(original_text, n);
        cout << "\n";
        cout << endl;

        //Print the LCS
        //string r = lcs_DnC(text, original_text);
        //cout << r;
         lcs(text, original_text);



    //delete [] wordsc;
    //delete [] words_originalc;

    return 0;



}






