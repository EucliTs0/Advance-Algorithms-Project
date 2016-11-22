#include <string>
#include <math.h>
#include <set>
#include <utility>
void space_efficient_lcs_length(std::string* String_1,
                                std::string* String_2,
                                long string_1_begin, long string_1_end,
                                long string_2_begin, long string_2_end,
                                long* Q_temp
                                );
void backward_space_efficient_lcs_length(std::string* String_1,
                                         std::string* String_2,
                                         long string_1_begin, long string_1_end,
                                         long string_2_begin, long string_2_end,
                                         long* Q_temp
                                        );
void lcs_divide_and_conquer(std::string* String_1, std::string* String_2,
                            long string_1_begin, long string_1_end,
                            long string_2_begin, long string_2_end,
                            long* Q,
                            std::set<long>* LCS_xset,
                            std::set<long>* LCS_yset
                            );
void LCS_DIVIDE_CONQUER(std::string* String_1,
                        std::string* String_2,
                        std::set<long>* LCS_XSet,
                        std::set<long>* LCS_YSet
                        );
