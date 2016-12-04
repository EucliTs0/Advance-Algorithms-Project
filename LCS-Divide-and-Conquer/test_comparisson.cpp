#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <utility>
#include <sstream>
#include "lcsdc.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


int maintt(int argc, char** argv)
{
    std::stringstream plag_string;
    std::stringstream orig_string;

    std::ifstream file_plag("../corpus/corpus1/corpus_preprocessed/g2pC_taskc.txt");

    std::ifstream file_orig("../corpus/corpus1/corpus_preprocessed/orig_taskc.txt");


    if(file_plag.is_open()){
        std::string line;
        while(std::getline(file_plag, line)){
            plag_string << line << ' ';
        }
        file_plag.close();
    }

    if(file_orig.is_open()){
        std::string line;
        while(std::getline(file_orig, line)){
            orig_string << line << ' ';
        }
        file_orig.close();
    }

    //std::cout << plag_string.str() << std::endl;

    std::ofstream resultsfile;
    resultsfile.open ("../corpus/corpus1/lcs/lcs_g2pC_taskc.txt");

    std::string Xs = orig_string.str();
    std::string Ys = plag_string.str();

    std::string* X = new std::string("");
    std::string* Y = new std::string("");
    std::set<long>* LCS_XSet;
    std::set<long>* LCS_YSet;
    X = &Xs;
    Y = &Ys;

    LCS_XSet = new std::set<long>();
    LCS_YSet = new std::set<long>();
    LCS_DIVIDE_CONQUER(X, Y, LCS_XSet, LCS_YSet);
    long lcs_size = LCS_XSet->size();

    long lenght_x = X->length();
    for(long ii = 0; ii < lenght_x; ii++)
    {
        const bool is_in = LCS_XSet->find(ii+1) != LCS_XSet->end();
        if(is_in) {
            resultsfile << X->at(ii);
        }
    }

    std::cout << "Length of LCS: " << lcs_size << std::endl;

    long d = std::min(X->length(), Y->length());
    if(d > 0){
        std::stringstream Dstr;
        double D = (double)lcs_size / (double)d;
        Dstr << D;
        std::cout << std::fixed;
        //std::cout << std::setprecision(4);
        std::cout << "Length of X: " << X->length() << std::endl;
        std::cout << "Length of Y: " << Y->length() << std::endl;
        std::cout << "Distance: " << Dstr.str() << std::endl;
    }






    delete LCS_XSet;
    delete LCS_YSet;
    resultsfile.close();
    return 0;
}
