#define DEBUG 0
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

void space_efficient_lcs_length(std::string* String_1,
                                std::string* String_2,
                                long string_1_begin, long string_1_end,
                                long string_2_begin, long string_2_end,
                                long* Q_temp
                                ) {
    long length_1 = string_1_end - string_1_begin + 1;
    long length_2 = string_2_end - string_2_begin + 1;

    /** ## Debugging: Print the segments of String_1 and String_2 */
    if(DEBUG){
        std::cout << "String_1: from index [" << string_1_begin << "] to index [" << string_1_end << "]:" << std::endl;
        for (long ii = string_1_begin; ii <= string_1_end; ii++) {
            std::cout << String_1->at(ii) << " " << std::endl;
        }
        std::cout << "String_2: from index [" << string_2_begin << "] to index [" << string_2_end << "]:" << std::endl;
        for (long ii = string_2_begin; ii <= string_2_end; ii++) {
            std::cout << String_2->at(ii) << " " << std::endl;
        }
    }
    long buffer_1[length_2 + 1] = {0};
    long buffer_2[length_2 + 1] = {0};

    /** Printing the initialization of 0-based buffers 1 and 2 */
    std::cout << "Content of buffer_1: " << std::endl;
    for (long ii = 0; ii < length_2 + 1; ii++) {
        std::cout << buffer_1[ii] << " * ";
    }
    std::cout << "Content of buffer_2: " << std::endl;
    for (long ii = 0; ii < length_2 + 1; ii++) {
        std::cout << buffer_2[ii] << " * ";
    }

    for(int i = string_1_begin; i <= string_1_end; i++) {

        /** Step i */
        std::cout << "\n##############################################" << std::endl;
        std::cout << "Processing Letter i = " << i << " of String_1" << std::endl;
        std::cout << "String_1 letter = " << String_1->at(i) << std::endl;
        for(int j = string_2_begin; j <= string_2_end; j++) {
            /** Step j */
            std::cout << "Processing Letter j = " << j << " of String_2" << std::endl;
            std::cout << "String_2 letter = " << String_2->at(j) << std::endl;
            if(String_1->at(i) == String_2->at(j)) {
                buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin] + 1;
                std::cout << "Case 1: " << std::endl;
                std::cout << "buffer_2[" << j - string_2_begin + 1 << "] = buffer_1[" << j - string_2_begin << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
            }
            else {
                if(buffer_2[j - string_2_begin] < buffer_1[j - string_2_begin + 1]) {
                    buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin + 1];
                    std::cout << "Case 2: " << std::endl;
                    std::cout << "buffer_2[" << j - string_2_begin + 1 << "] = buffer_1[" << j - string_2_begin + 1 << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
                }
                else {
                    buffer_2[j - string_2_begin + 1] = buffer_2[j - string_2_begin];
                    std::cout << "Case 3: " << std::endl;
                    std::cout << "buffer_2[" << j - string_2_begin + 1 << "] = buffer_2[" << j - string_2_begin << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
                }
            }
        }
        /** Fill the array Q_temp  */
        std::cout << "Content of buffer_2 at the end of the loop: " << std::endl;
        for (long ii = 0; ii < length_2 + 1; ii++) {
            std::cout << buffer_2[ii] << " * " << std::endl;
        }

        Q_temp[i] = buffer_2[string_2_end];
        /** Copy buffer 2 to buffer 1*/
        for (long ii = 0; ii < length_2 + 1; ii++) {
            buffer_1[ii] = buffer_2[ii];
        }
    }
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
