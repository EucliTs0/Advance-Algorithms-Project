#include <fstream>
#include <time.h>
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


int main(int argc, char** argv)
{
    std::ofstream resultsfile;
    resultsfile.open("../performance_tests/performance_time_18.txt");

    std::string X_file_name;
    std::string Y_file_name;


    X_file_name = "../performance_tests/X_18.txt";
    Y_file_name = "../performance_tests/Y_18.txt";


    std::ifstream X_file(X_file_name);
    std::ifstream Y_file(Y_file_name);

    std::string lineX;
    std::string lineY;

    std::set<long>* LCS_XSet;
    std::set<long>* LCS_YSet;

    while(std::getline(X_file, lineX) && std::getline(Y_file, lineY))
    {
        std::string* X = new std::string("");
        std::string* Y = new std::string("");
        X = &lineX;
        Y = &lineY;

        LCS_XSet = new std::set<long>();
        LCS_YSet = new std::set<long>();

        clock_t start_time = clock();
        LCS_DIVIDE_CONQUER(X, Y, LCS_XSet, LCS_YSet);

        // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        std::stringstream Dstr;
        double T = (double)(clock() - start_time) / (double) CLOCKS_PER_SEC;
        Dstr << T;
        long lcs_size = LCS_XSet->size();


        std::cout << X->length() << ", " << Y->length() << ", " << lcs_size << ", " << Dstr.str() << std::endl;
        resultsfile << X->length() << ", " << Y->length() << ", " << lcs_size << ", " << Dstr.str() << "\n";
        delete LCS_XSet;

    }

    X_file.close();
    Y_file.close();
    resultsfile.close();
    return 0;
}
