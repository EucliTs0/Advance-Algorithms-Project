#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

void space_efficient_lcs_length(std::string* String_1,
                                std::string* String_2,
                                long int string_1_begin, long int string_1_end,
                                long int string_2_begin, long int string_2_end,
                                long int* Q_temp
                                ) {
    long int length_2 = string_2_end - string_2_begin + 1;

    /** Print the segments of String_1 and String_2 */
    std::cout << "String_1: from index [" << string_1_begin << "] to index [" << string_1_end << "]:" << std::endl;
    std::cout << String_1->at(0) << " - " << std::endl;
}

int main(){
    std::string* X = new std::string("AAB");
    std::string* Y = new std::string("CABD");
    long length_1 = X->length();
    long Q_temp[length_1 + 1] = {0};

    space_efficient_lcs_length(X,
                               Y,
                               0, 2,
                               0, 3,
                               Q_temp
                              );

    delete X;
    delete Y;
    return 0;
}
