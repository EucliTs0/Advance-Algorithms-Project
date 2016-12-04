#define DEBUG 0
#define DEBUG_SPACE_EFF_LCS 0
#define TEST_SPACE_EFF_LCS 0
#define DEBUB_BW_SPACE_EFF_LCS 0
#define TEST_BW_SPACE_EFF_LCS 0
#define DEBUG_LCS_D_C 0

#include <windows.h>
#include <iostream>
#include <string>
#include <math.h>
#include <set>
#include <utility>

/**
* Author: Jorge Chong
* Project: Plagiarism Detection with LCS
* 2016
* lcsdc.cpp library
* all debugging information removed
*/

/***
* Helper functions
*/

/**
* Space Efficient LCS length
*/
void space_efficient_lcs_length(std::string* String_1,
                                std::string* String_2,
                                long string_1_begin, long string_1_end,
                                long string_2_begin, long string_2_end,
                                long* Q_temp
                                ) {
    /** Length of the input Strings */
    long length_1 = string_1_end - string_1_begin + 1;
    long length_2 = string_2_end - string_2_begin + 1;

    /** buffer_1 and buffer_2 play the role of the 2 rows matrix */
    long buffer_1[length_2 + 1] = {0};
    long buffer_2[length_2 + 1] = {0};

    // ++
    Q_temp[string_1_begin] = 0;

    for(int i = string_1_begin; i <= string_1_end; i++) {
        /** Step i */
        for(int j = string_2_begin; j <= string_2_end; j++) {
            /** Step j */
            if(String_1->at(i) == String_2->at(j)) {
                /** Case 1: X_i = Y_i */
                buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin] + 1;
            }
            else {
                if(buffer_2[j - string_2_begin] < buffer_1[j - string_2_begin + 1]) {
                    /** Case 2: Take the Length of the LCS of the upper position */
                    buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin + 1];
                }
                else {
                    /** Case 3: Take the Length of the LCS of the Left */
                    buffer_2[j - string_2_begin + 1] = buffer_2[j - string_2_begin];
                }
            }
        }

        /** Fill the array Q_temp  */
        // **
        Q_temp[i + 1] = buffer_2[length_2];
        /** Copy buffer 2 to buffer 1*/
        for (long ii = 0; ii < length_2 + 1; ii++) {
            buffer_1[ii] = buffer_2[ii];
        }
    }
    return;
}

/**
* Space Efficient Backward LCS length: To optimize resources, add the values of Q_temp calculated in
* the previous step to the new values into Q_temp
*/
void backward_space_efficient_lcs_length(std::string* String_1,
                                         std::string* String_2,
                                         long string_1_begin, long string_1_end,
                                         long string_2_begin, long string_2_end,
                                         long* Q_temp
                                        ) {

    long length_1 = string_1_end - string_1_begin + 1;
    long length_2 = string_2_end - string_2_begin + 1;

    long buffer_1[length_2 + 1] = {0};
    long buffer_2[length_2 + 1] = {0};

    // **
    // Q_temp[string_1_end + 1] = 0;
    for(long i = string_1_end; i >= string_1_begin; i--) {
        /** Step i */
        for(long j = string_2_end; j >= string_2_begin; j--) {
            /** Step j */
            if(String_1->at(i) == String_2->at(j)) {
                /** X_i = Y_j */
                buffer_2[j - string_2_begin] = buffer_1[j - string_2_begin + 1] + 1;
            }
            else {
                if(buffer_2[j - string_2_begin + 1] < buffer_1[j - string_2_begin]) {
                    buffer_2[j - string_2_begin] = buffer_1[j - string_2_begin];
                }
                else {
                    buffer_2[j - string_2_begin] = buffer_2[j - string_2_begin + 1];
                }
            }
        }

        Q_temp[i] = Q_temp[i] + buffer_2[0];
        /** Copy buffer 2 to buffer 1*/
        for (long ii = 0; ii < length_2 + 1; ii++) {
            buffer_1[ii] = buffer_2[ii];
        }
    }
    return;
}

/***
* void lcs_divide_and_conquer(std::string* String_1,   <- String 1: X
*                             std::string* String_2,   <- String 2: Y
*                             long string_1_begin,     <- Beginning of String 1
*                             long string_1_end,       <- End of String 1
*                             long string_2_begin,     <- Beginning of String 2
*                             long string_2_end,       <- End of String 2
*                             long* Q,                 <- Array with the indexing q of Size size_of(String 1)
*                             std::set<long>* LCS_xset,  <- Set with index of X in LCS
*                             std::set<long>* LCS_yset   <- Set with index of Y in LCS
*                             )
*/
void lcs_divide_and_conquer(std::string* String_1, std::string* String_2,
                            long string_1_begin, long string_1_end,
                            long string_2_begin, long string_2_end,
                            long* Q,
                            std::set<long>* LCS_xset,
                            std::set<long>* LCS_yset
                            ){
    // auto search = LCS_xset->find(string_1_end + 1);
    // if(search != )
    /** Base cases when one of the two string lengths are less than or equal to 2 */
    long length_1 = string_1_end - string_1_begin + 1;
    long length_2 = string_2_end - string_2_begin + 1;

    /** For strings of length 0 do nothing */
    if(length_1 <= 0 || length_2 <= 0){
        return;
    }

    /** The test is to test if are equals and were added to the LSC_Xset */
    if(length_1 <= 2 || length_2 <= 2){
        if(String_1->at(string_1_end) == String_2->at(string_2_end)) {
            /** Add to the LCS and search over string_1_end - 1, string_2_end - 1 */

            LCS_xset->insert(string_1_end + 1);
            LCS_yset->insert(string_2_end + 1);

            string_1_end = string_1_end - 1;
            string_2_end = string_2_end - 1;
            length_1 = length_1 - 1;
            length_2 = length_2 - 1;


        }

        if(length_1 <= 0 || length_2 <= 0){
            return;
        }
        if(length_1 == 1) {
            /** Find if  there is an occurrence of the character of String_1 in String_2 */
            for(long ii = string_2_begin; ii <= string_2_end; ii++){
                if(String_1->at(string_1_begin) == String_2->at(ii)){
                    //**
                    LCS_xset->insert(string_1_begin + 1);
                    LCS_yset->insert(ii + 1);

                    break;
                }
            }
            return;
        }

        if(length_1 == 2) {
            /** Test the first character in String_1 */
            long jj = string_2_begin;
            long ii = string_2_begin;
            for(ii = string_2_begin; ii <= string_2_end; ii++){
                if(String_1->at(string_1_begin) == String_2->at(ii)) {
                    // ++
                    // LCS_set->insert(string_1_begin);
                    LCS_xset->insert(string_1_begin + 1);
                    LCS_yset->insert(ii + 1);
                    jj = ii + 1;

                    break;
                }
            }
            /** Test the second character in String_1 */
            for(long ii = jj; ii <= string_2_end; ii++){
                if(String_1->at(string_1_begin + 1) == String_2->at(ii)) {
                    // ++
                    // LCS_set->insert(string_1_begin + 1);
                    LCS_xset->insert(string_1_begin + 2);
                    LCS_yset->insert(ii + 1);

                    break;
                }
            }
            return;
        }
        if(length_2 == 1){
            for(long jj = string_1_begin; jj <= string_1_end; jj++){
                if(String_2->at(string_2_begin) == String_1->at(jj)) {
                    // ++
                    // LCS_set->insert(jj);
                    LCS_xset->insert(jj + 1);
                    LCS_yset->insert(string_2_begin + 1);

                    break;
                }
            }
            return;
        }
        if(length_2 == 2){
            long ii = string_1_begin;
            long jj = string_1_begin;
            for(jj = string_1_begin; jj <= string_1_end; jj++){
                if(String_2->at(string_2_begin) == String_1->at(jj)) {
                    // ++
                    // LCS_set->insert(jj);
                    LCS_xset->insert(jj + 1);
                    LCS_yset->insert(string_2_begin + 1);
                    ii = jj + 1;

                    break;
                }
            }
            for(long jj = ii; jj <= string_1_end; jj++) {
                if(String_2->at(string_2_begin + 1) == String_1->at(jj)) {
                    // ++
                    // LCS_set->insert(jj);
                    LCS_xset->insert(jj + 1);
                    LCS_yset->insert(string_2_begin + 2);
                    break;
                }
            }
            return;
        }
    }

    /** Remember that we use 0-based strings */
    /** Calculates the middle point of String_2 */
    long string_2_middle = floor((string_2_begin + string_2_end)/2);
    space_efficient_lcs_length(String_1, String_2,
                               string_1_begin, string_1_end,
                               string_2_begin, string_2_middle,
                               Q);

    backward_space_efficient_lcs_length(String_1, String_2,
                                        string_1_begin, string_1_end,
                                        string_2_middle + 1, string_2_end,
                                        Q);

    /** Find the index that maximizes the sum of c and g*/
    long q_index = string_1_end + 1;
    long Q_max_value = LONG_MIN;

    // **
    for (long qi = string_1_end + 1; qi >= string_1_begin + 1; qi--) {
        if(Q[qi] >= Q_max_value){
            Q_max_value = Q[qi];
            q_index = qi;
        }
    }
    if (Q[string_1_begin] > Q_max_value) {
        Q_max_value = Q[string_1_begin];
        q_index = string_1_begin;
    }

    if(Q_max_value == 0){
        return;
    }

    if(DEBUG_LCS_D_C){
        std::cout << "[" << __LINE__ << "] q_index that maximizes c+g:" << q_index << std::endl;
    }

    // ++
    /** Convert q_index to X 0-based indexes */
    long q_index_x = q_index - 1;
    if(q_index_x < 0)
        q_index_x = 0;

    /** Add that index to the structure */
    if(q_index != 0 && q_index != string_1_begin){
        if(String_1->at(q_index_x) == String_2->at(string_2_middle))
        {
            LCS_xset->insert(q_index);
            LCS_yset->insert(string_2_middle + 1);
        }
    }

    if(q_index == string_1_begin) {
        lcs_divide_and_conquer(String_1, String_2,
                               string_1_begin, string_1_end,
                               string_2_middle + 1, string_2_end,
                               Q,
                               LCS_xset,
                               LCS_yset
                               );

    } else {
        if(q_index == string_1_end + 1) {
            lcs_divide_and_conquer(String_1, String_2,
                                   string_1_begin, string_1_end,
                                   string_2_begin, string_2_middle,
                                   Q,
                                   LCS_xset,
                                   LCS_yset
                                  );
        }
        else {
            /** Make the recursive calls */
            lcs_divide_and_conquer(String_1, String_2,
                                   string_1_begin, q_index_x,
                                   string_2_begin, string_2_middle,
                                   Q,
                                   LCS_xset,
                                   LCS_yset
                                   );
            lcs_divide_and_conquer(String_1, String_2,
                                   q_index_x + 1, string_1_end,
                                   string_2_middle + 1, string_2_end,
                                   Q,
                                   LCS_xset,
                                   LCS_yset
                                   );
        }
    }
    return;
}


/** Main function implementing LCS with divide and conquer
* std::string* String_1: String_1
* std::string* String_2: String_2
* std::set<long>* LCS_XSet
* std::set<long>* LCS_YSet
*/
void LCS_DIVIDE_CONQUER(std::string* String_1,
                        std::string* String_2,
                        std::set<long>* LCS_XSet,
                        std::set<long>* LCS_YSet
                        ) {
    long length_1 = String_1->length();
    long length_2 = String_2->length();

    /** Check if one of the Strings is empty */

    /** Array of chars that keeps the sum of arrays c and g */
    long Q_temp[length_1 + 1] = {0};

    /** Call Divide and Conquer */
    lcs_divide_and_conquer(String_1,
                           String_2,
                           0, length_1 - 1,
                           0, length_2 - 1,
                           Q_temp,
                           LCS_XSet,
                           LCS_YSet
                           );
    return;
}
