#define DEBUG 1
#define DEBUG_SPACE_EFF_LCS 1
#define TEST_SPACE_EFF_LCS 0
#define DEBUB_BW_SPACE_EFF_LCS 0
#define TEST_BW_SPACE_EFF_LCS 0
#define DEBUG_LCS_D_C 1

#include <iostream>
#include <string>
#include <math.h>
#include <set>

#define CONDITION1 debug_mode == 1

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


    /** ## Debugging: Print the segments of String_1 and String_2 */
    if(DEBUG_SPACE_EFF_LCS){
        std::cout << "\n############# space_efficient_lcs_length #############" << std::endl;
        std::cout << "\n[" << __LINE__ << "] String_1: from index [" << string_1_begin << "] to index [" << string_1_end << "]:" << std::endl;
        for (long ii = string_1_begin; ii <= string_1_end; ii++) {
            std::cout << String_1->at(ii) << " " << std::endl;
        }
        std::cout << "[" << __LINE__ << "] String_2: from index [" << string_2_begin << "] to index [" << string_2_end << "]:" << std::endl;
        for (long ii = string_2_begin; ii <= string_2_end; ii++) {
            std::cout << String_2->at(ii) << " " << std::endl;
        }
    }

    /** buffer_1 and buffer_2 play the role of the 2 rows matrix */
    long buffer_1[length_2 + 1] = {0};
    long buffer_2[length_2 + 1] = {0};

    /** ## Debugging: Printing the initialization of 0-based buffers 1 and 2 */
    if(DEBUG_SPACE_EFF_LCS){
        std::cout << "Content of buffer_1: " << std::endl;
        for (long ii = 0; ii < length_2 + 1; ii++) {
            std::cout << buffer_1[ii] << " | ";
        }
        std::cout << "\nContent of buffer_2: " << std::endl;
        for (long ii = 0; ii < length_2 + 1; ii++) {
            std::cout << buffer_2[ii] << " | ";
        }
    }

    for(int i = string_1_begin; i <= string_1_end; i++) {
        /** Step i */
        if(DEBUG_SPACE_EFF_LCS){
            std::cout << "\nFor Loop:" << std::endl;
            std::cout << "Processing Letter i = " << i << " of String_1" << std::endl;
            std::cout << "String_1 letter = " << String_1->at(i) << std::endl;
        }
        for(int j = string_2_begin; j <= string_2_end; j++) {
            /** Step j */
            if(DEBUG_SPACE_EFF_LCS){
                std::cout << "Processing Letter j = " << j << " of String_2" << std::endl;
                std::cout << "String_2 letter = " << String_2->at(j) << std::endl;
            }
            if(String_1->at(i) == String_2->at(j)) {
                /** Case 1: X_i = Y_i */
                buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin] + 1;
                if(DEBUG_SPACE_EFF_LCS){
                    std::cout << "[" << __LINE__ << "] Case 1: " << std::endl;
                    std::cout << "buffer_2[" << j - string_2_begin + 1 << "] = buffer_1[" << j - string_2_begin << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
                }
            }
            else {
                if(buffer_2[j - string_2_begin] < buffer_1[j - string_2_begin + 1]) {
                    /** Case 2: Take the Length of the LCS of the upper position */
                    buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin + 1];
                    if(DEBUG_SPACE_EFF_LCS){
                        std::cout << "[" << __LINE__ << "] Case 2: " << std::endl;
                        std::cout << "buffer_2[" << j - string_2_begin + 1 << "] = buffer_1[" << j - string_2_begin + 1 << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
                    }
                }
                else {
                    /** Case 3: Take the Length of the LCS of the Left */
                    buffer_2[j - string_2_begin + 1] = buffer_2[j - string_2_begin];
                    if(DEBUG_SPACE_EFF_LCS){
                        std::cout << "[" << __LINE__ << "] Case 3: " << std::endl;
                        std::cout << "buffer_2[" << j - string_2_begin + 1 << "] = buffer_2[" << j - string_2_begin << "] <--" << buffer_2[j - string_2_begin] << std::endl;
                    }
                }
            }
        }

        if(DEBUG_SPACE_EFF_LCS){
            std::cout << "Content of buffer_2 at the end of the loop: " << std::endl;
            for (long ii = 0; ii < length_2 + 1; ii++) {
                std::cout << "[" << ii << "]: " << buffer_2[ii] << " * ";
            }
        }

        /** Fill the array Q_temp  */
        Q_temp[i] = buffer_2[length_2];
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

    if(DEBUB_BW_SPACE_EFF_LCS) {
        /** Print the segments of String_1 and String_2 */
        std::cout << "\n+++++++++++++++ backward_space_efficient_lcs_length +++++++++++++++" << std::endl;
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
    if(DEBUB_BW_SPACE_EFF_LCS) {
        std::cout << "Content of buffer_1: " << std::endl;
        for (long ii = 0; ii < length_2 + 1; ii++) {
            std::cout << buffer_1[ii] << " | ";
        }
        std::cout << "\nContent of buffer_2: " << std::endl;
        for (long ii = 0; ii < length_2 + 1; ii++) {
            std::cout << buffer_2[ii] << " | ";
        }
    }

    for(long i = string_1_end; i >= string_1_begin; i--) {
        /** Step i */
        if(DEBUB_BW_SPACE_EFF_LCS) {
            std::cout << "\nFor Loop:" << std::endl;
            std::cout << "Processing Letter i = " << i << " of String_1" << std::endl;
            std::cout << "String_1 letter = " << String_1->at(i) << std::endl;
        }
        for(long j = string_2_end; j >= string_2_begin; j--) {
            /** Step j */
            if(DEBUB_BW_SPACE_EFF_LCS) {
                std::cout << "Processing Letter j = " << j << " of String_2" << std::endl;
                std::cout << "String_2 letter = " << String_2->at(j) << std::endl;
            }
            if(String_1->at(i) == String_2->at(j)) {
                /** X_i = Y_j */
                buffer_2[j - string_2_begin] = buffer_1[j - string_2_begin + 1] + 1;
                if(DEBUB_BW_SPACE_EFF_LCS) {
                    std::cout << "[" << __LINE__ << "] Case 1: " << std::endl;
                    std::cout << "buffer_2[" << j - string_2_begin << "] = buffer_1[" << j - string_2_begin + 1 << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
                }
            }
            else {
                if(buffer_2[j - string_2_begin + 1] < buffer_1[j - string_2_begin]) {
                    buffer_2[j - string_2_begin] = buffer_1[j - string_2_begin];
                    if(DEBUB_BW_SPACE_EFF_LCS) {
                        std::cout << "[" << __LINE__ << "] Case 2: " << std::endl;
                        std::cout << "buffer_2[" << j - string_2_begin << "] = buffer_1[" << j - string_2_begin << "] <--" << buffer_2[j - string_2_begin] << std::endl;
                    }
                }
                else {
                    buffer_2[j - string_2_begin] = buffer_2[j - string_2_begin + 1];
                    if(DEBUB_BW_SPACE_EFF_LCS) {
                        std::cout << "[" << __LINE__ << "] Case 3: " << std::endl;
                        std::cout << "buffer_2[" << j - string_2_begin << "] = buffer_2[" << j - string_2_begin + 1 << "] <--" << buffer_2[j - string_2_begin + 1] << std::endl;
                    }
                }
            }
        }
        /** Fill the array Q_temp  */
        if(DEBUB_BW_SPACE_EFF_LCS) {
            std::cout << "Content of buffer_2 at the end of the loop: " << std::endl;
            for (long ii = 0; ii < length_2 + 1; ii++) {
                std::cout << "[" << ii << "]: " << buffer_2[ii] << " * ";
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
*                             std::set<long>* LCS_set  <- A set structure to store the set of indexes (of String 1) for the LCS
*                             )
*/
void lcs_divide_and_conquer(std::string* String_1, std::string* String_2,
                            long string_1_begin, long string_1_end,
                            long string_2_begin, long string_2_end,
                            long* Q,
                            std::set<long>* LCS_set
                            ){
    if(DEBUG_LCS_D_C){
        std::cout << "********************************************************" << std::endl;
    }

    /** Base cases when one of the two string lengths are less than or equal to 2 */
    long length_1 = string_1_end - string_1_begin + 1;
    long length_2 = string_2_end - string_2_begin + 1;

    /** For strings of length 0 do nothing */
    if(length_1 <= 0 || length_2 <= 0){
        if(DEBUG_LCS_D_C){
            std::cout << "[" << __LINE__ << "] Base Case: One string of size = 0" << std::endl;
        }
        return;
    }

    if(length_1 == 1) {
        /** Find if there is an occurrence of the character of String_1 in String_2 */
        if(DEBUG_LCS_D_C){
            std::cout << "[" << __LINE__ << "] Base Case: String_1 size = 1" << std::endl;
        }
        for(long ii = string_2_begin; ii <= string_2_end; ii++){
            if(String_1->at(string_1_begin) == String_2->at(ii)){
                LCS_set->insert(string_1_begin);
                break;
            }
        }
        return;
    }
    if(length_1 == 2) {
        if(DEBUG_LCS_D_C){
            std::cout << "[" << __LINE__ << "] Base Case: String_1 size = 2" << std::endl;
        }

        /** Test the first character in String_1 */
        long jj = string_2_begin;
        for(long ii = string_2_begin; ii <= string_2_end; ii++){
            if(String_1->at(string_1_begin) == String_2->at(ii)) {
                LCS_set->insert(string_1_begin);
                jj = ii + 1;
                break;
            }
        }
        /** Test the second character in String_1 */
        for(long ii = jj; ii <= string_2_end; ii++){
            if(String_1->at(string_1_begin + 1) == String_2->at(ii)) {
                LCS_set->insert(string_1_begin + 1);
                break;
            }
        }
        return;
    }
    if(length_2 == 1){
        if(DEBUG_LCS_D_C){
            std::cout << "[" << __LINE__ << "] Base Case: String_2 size = 1" << std::endl;
        }
        for(long jj = string_1_begin; jj <= string_1_end; jj++){
            if(String_2->at(string_2_begin) == String_1->at(jj)) {
                LCS_set->insert(jj);
                break;
            }
        }
        return;
    }
    if(length_2 == 2){
        if(DEBUG_LCS_D_C){
            std::cout << "[" << __LINE__ << "] Base Case: String_2 size = 2" << std::endl;
        }
        long ii = string_2_begin;
        for(long jj = string_1_begin; jj <= string_1_end; jj++){
            if(String_2->at(string_2_begin) == String_1->at(jj)) {
                LCS_set->insert(jj);
                ii = jj + 1;
                break;
            }
        }
        for(long jj = ii; jj <= string_1_end; jj++) {
            if(String_2->at(string_2_begin + 1) == String_1->at(jj)) {
                LCS_set->insert(jj);
                break;
            }
        }
        return;
    }

    /** Remember that we use 0-based strings */
    /** Calculates the middle point of String_2 */
    long string_2_middle = floor((string_2_begin + string_2_end)/2);
    if(DEBUG_LCS_D_C){
        std::cout << "Middle Point of String_2: " << string_2_middle << std::endl;
    }

    if(DEBUG_LCS_D_C){
        std::cout << "Calling space_efficient_lcs_length(String_1, String_2, " << string_1_begin << ", "
                  << string_1_end << ", " << string_2_begin << ", " << string_2_middle << ", Q):" << std::endl;
    }
    space_efficient_lcs_length(String_1, String_2,
                               string_1_begin, string_1_end,
                               string_2_begin, string_2_middle,
                               Q);
    if(DEBUG_LCS_D_C){
        std::cout << "\n---> Q: " << std::endl;
        for (long ii = string_1_begin; ii <= string_1_end; ii++) {
            std::cout << "[" << ii << "]: " << Q[ii] << " * " << std::endl;
        }
    }

    if(DEBUG_LCS_D_C){
        std::cout << "\n\nCalling backward_space_efficient_lcs_length(String_1, String_2, " << string_1_begin << ", "
                  << string_1_end << ", " << string_2_middle + 1 << ", " << string_2_end << ", Q):" << std::endl;
    }
    backward_space_efficient_lcs_length(String_1, String_2,
                                        string_1_begin, string_1_end,
                                        string_2_middle + 1, string_2_end,
                                        Q);
    if(DEBUG_LCS_D_C){
        std::cout << "\n---> Q: " << std::endl;
        for (long ii = string_1_begin; ii <= string_1_end; ii++) {
            std::cout << "[" << ii << "]: " << Q[ii] << " * " << std::endl;
        }
    }

    /** Find the index that maximizes the sum of c and g*/
    long q_index = string_1_end;
    long Q_min_value = LONG_MIN;

    for (long qi = string_1_end; qi >= string_1_begin; qi--) {
        if(Q[qi] >= Q_min_value){
            Q_min_value = Q[qi];
            q_index = qi;
        }
    }

    if(DEBUG_LCS_D_C){
        std::cout << "[" << __LINE__ << "] q_index that maximizes c+g:" << q_index << std::endl;
    }

    /** Add that index to the structure */
    LCS_set->insert(q_index);

    /** Make the recursive calls */
    if(DEBUG_LCS_D_C){
        std::cout << "\n[" << __LINE__ << "] Calling recursively lcs_divide_and_conquer(String_1, String_2, "
                  << string_1_begin << ", " << q_index << ", " << string_2_begin << ", " << string_2_middle
                  << ", Q, LCS_set)" << std::endl;
    }
    lcs_divide_and_conquer(String_1, String_2,
                           string_1_begin, q_index,
                           string_2_begin, string_2_middle,
                           Q,
                           LCS_set
                           );
    if(DEBUG_LCS_D_C){
        std::cout << "\n[" << __LINE__ << "] Calling recursively lcs_divide_and_conquer(String_1, String_2, "
                  << q_index + 1 << ", " << string_1_end << ", " << string_2_middle + 1 << ", " << string_2_end
                  << ", Q, LCS_set)" << std::endl;
    }
    lcs_divide_and_conquer(String_1, String_2,
                           q_index + 1, string_1_end,
                           string_2_middle + 1, string_2_end,
                           Q,
                           LCS_set
                           );
    return;
}


/** Main function implementing LCS with divide and conquer
* std::string* String_1: String_1
* std::string* String_2: String_2
* Length of the LCS
* Array of chars with the LCS
* Array of Indexes in String_1 with the LCS
*/
void LCS_DIVIDE_CONQUER(std::string* String_1, std::string* String_2, std::set<long>* LCS_Set) {
    long length_1 = String_1->length();
    long length_2 = String_2->length();

    /** Check if one of the Strings is empty */

    /** Array of chars that keeps the sum of arrays c and g */
    long Q_temp[length_1] = {0};

    /** Call Divide and Conquer */
    if(DEBUG_LCS_D_C){
        std::cout << "\n[" << __LINE__ << "] Calling lcs_divide_and_conquer(String_1, String_2, "
                  << 0 << ", " << length_1 - 1 << ", " << 0 << ", " << length_2 - 1
                  << ", Q_temp, LCS_Set)" << std::endl;
    }
    lcs_divide_and_conquer(String_1, String_2, 0, length_1 - 1, 0, length_2 - 1, Q_temp, LCS_Set);
    return;
}
/**
* Unit Testing
* Testing with different strings of different lengths
*
*/
int main(){
    std::set<long>* LCS_Set = new std::set<long>();


    //std::string* X = new std::string("ABCBDAB");
    //std::string* Y = new std::string("BDCABA");

    //std::string* X = new std::string("abaaccd");
    //std::string* Y = new std::string("acbbddda");

    //std::string* X = new std::string("XMJYAUZ");
    //std::string* Y = new std::string("MZJAWXU");

    std::string* X = new std::string("ABCDBAGZCDCA");
    std::string* Y = new std::string("BCADCGZ");
    // <- Failed. Debug

    //std::string* X = new std::string("DB");
    //std::string* Y = new std::string("DC");

    //std::string* X = new std::string("DBAGZCDCA");
    //std::string* Y = new std::string("DCGZ");

    //std::string* X = new std::string("ABCDBAGZCDCA");
    //std::string* Y = new std::string("DD");

    if(TEST_SPACE_EFF_LCS)
    {
        long length_1 = X->length();
        long Q_temp[length_1] = {0};

        std::cout << "\nContent of Q_temp before calling space_efficient_lcs_length: " << std::endl;
        for (long ii = 0; ii < length_1; ii++) {
            std::cout << "[" << ii << "]: " << Q_temp[ii] << " * " << std::endl;
        }

        space_efficient_lcs_length(X,
                                   Y,
                                   0, 6,
                                   0, 2,
                                   Q_temp);

        std::cout << "\nContent of Q_temp after calling space_efficient_lcs_length: " << std::endl;
        for (long ii = 0; ii < length_1; ii++) {
            std::cout << "[" << ii << "]: " << Q_temp[ii] << " * " << std::endl;
        }
    }

    if(TEST_BW_SPACE_EFF_LCS)
    {
        long length_1 = X->length();
        long Q_temp2[length_1] = {0};

        std::cout << "\nContent of Q_temp before calling backward_space_efficient_lcs_length: " << std::endl;
        for (long ii = 0; ii < length_1; ii++) {
            std::cout << "[" << ii << "]: " << Q_temp2[ii] << " * " << std::endl;
        }

        backward_space_efficient_lcs_length(X,
                                            Y,
                                            0, 6,
                                            3, 5,
                                            Q_temp2);

        std::cout << "\nContent of Q_temp after calling backward_space_efficient_lcs_length: " << std::endl;
        for (long ii = 0; ii < length_1; ii++) {
            std::cout << "[" << ii << "]: " << Q_temp2[ii] << " * " << std::endl;
        }
    }

    LCS_DIVIDE_CONQUER(X, Y, LCS_Set);
    long lcs_size = LCS_Set->size();

    if(lcs_size > 0){
        if(DEBUG_LCS_D_C){
            std::cout << "Content of LCS_Set: " << std::endl;
            std::set<long>::iterator it;
            for (it = LCS_Set->begin(); it != LCS_Set->end(); ++it)
            {
                std::cout << *it << std::endl;
            }
        }
        long lenght_x = X->length();
        for(long ii = 0; ii < lenght_x; ii++)
        {
            const bool is_in = LCS_Set->find(ii) != LCS_Set->end();
            if(is_in) {
                std::cout << "At Index " << ii << " of X: " << X->at(ii) << std::endl;
            }
        }
    }
    delete LCS_Set;
    return 0;
}
