#include <windows.h>
#include <iostream>
#include <string>
#include <math.h>
#include <set>
#include <utility>



long lcs_recursive_helper(std::string* String_1, std::string* String_2,
                          long string_1_i, long string_1_len,
                          long string_2_j, long string_2_len
                         ) {

    if(string_1_i > string_1_len - 1)
        return 0;
    if(string_2_j > string_2_len - 1)
        return 0;

    if(String_1->at(string_1_i) == String_2->at(string_2_j)) {
        return lcs_recursive_helper(String_1, String_2, string_1_i + 1, string_1_len, string_2_j + 1, string_2_len) + 1;
    } else {
        long l1 = lcs_recursive_helper(String_1, String_2, string_1_i + 1, string_1_len, string_2_j, string_2_len);
        long l2 = lcs_recursive_helper(String_1, String_2, string_1_i, string_1_len, string_2_j + 1, string_2_len);
        if(l1 > l2) {
            return l1;
        }
        else
            return l2;
    }
}

long LCS_RECURSIVE_LENGTH(std::string* String_1, std::string* String_2
                         ){
    long string_1_len = String_1->length();
    long string_2_len = String_2->length();

    return lcs_recursive_helper(String_1, String_2, 0, string_1_len, 0, string_2_len);

}

int maint()
{

    // Case 93 half
    std::string* X = new std::string("ATTACATCGGTATGAAACTTTAA");
    std::string* Y = new std::string("CCTGCGGTTGCAATATATATGGC");

    //std::string* X = new std::string("XMJYAUZ");
    //std::string* Y = new std::string("MZJAWXU");

    long lcs_size = LCS_RECURSIVE_LENGTH(X, Y);
    std::cout << "Length of the LCS: " << lcs_size << std::endl;
    return 0;
}
