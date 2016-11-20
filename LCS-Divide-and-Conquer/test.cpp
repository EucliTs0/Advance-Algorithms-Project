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


int main(int argc, char** argv)
{
    std::ofstream resultsfile;
    resultsfile.open ("results_test.txt");
    resultsfile << "Results of running LCS over X001.txt..X100.txt and Y001..Y100.txt:\n";

    int num_files = 100;
    for(int i = 1; i <= num_files; i++){
        std::string X_file;
        std::string Y_file;
        if(i < 10){
            X_file = "../test/X00" + patch::to_string(i) + ".txt";
            Y_file = "../test/Y00" + patch::to_string(i) + ".txt";
        }
        else {
            if(i < 100){
                X_file = "../test/X0" + patch::to_string(i) + ".txt";
                Y_file = "../test/Y0" + patch::to_string(i) + ".txt";
            }
            else {
                X_file = "../test/X" + patch::to_string(i) + ".txt";
                Y_file = "../test/Y" + patch::to_string(i) + ".txt";
            }
        }
        //std::cout << "X filename: " << X_file << std::endl;
        //std::cout << "Y filename: " << Y_file << std::endl;

        std::string* X = new std::string("");
        std::string* Y = new std::string("");
        std::string lineX;
        std::string lineY;
        std::ifstream file(X_file);

        std::set< std::pair<long, long> >* LCS_Set;
        std::set<long>* LCS_XSet;
        std::set<long>* LCS_YSet;

        if(std::getline(file, lineX)){
            std::ifstream file(Y_file);

            if(std::getline(file, lineY)){
                X = &lineX;
                Y = &lineY;

                std::set< std::pair<long, long> >* LCS_Set = new std::set< std::pair<long, long> >();
                std::set<long>* LCS_XSet = new std::set<long>();
                std::set<long>* LCS_YSet = new std::set<long>();
                LCS_DIVIDE_CONQUER(X, Y, LCS_Set, LCS_XSet, LCS_YSet);
                long lcs_size = LCS_XSet->size();

                std::cout << i << ", " << lcs_size << std::endl;
                resultsfile << i << ", " << lcs_size << "\n";

                delete LCS_Set;
                delete LCS_XSet;
                delete LCS_YSet;
            }
        }
    }
    resultsfile.close();
    return 0;
}
