import math
#
# Author: Jorge Chong
# Project: Plagiarism Detection with LCS
# 2016
# port to python from lcsdc.cpp library
# all debugging information removed
#

#
# Helper functions
#

#
# Space Efficient LCS length
#
def space_efficient_lcs_length(String_1, String_2, string_1_begin, string_1_end,
                               string_2_begin, string_2_end, Q_temp):
	## Length of the input Strings 
	length_1 = string_1_end - string_1_begin + 1
	length_2 = string_2_end - string_2_begin + 1

    ## buffer_1 and buffer_2 play the role of the 2 rows matrix */
	buffer_1 = [0]*(length_2 + 1)
	buffer_2 = [0]*(length_2 + 1)
    
    # ++
	Q_temp[string_1_begin] = 0
	for i in range(string_1_begin, string_1_end + 1):
		# Step i
		for j in range(string_2_begin, string_2_end + 1):
			# Step j
			if String_1[i] == String_2[j]:
				# Case 1 X_i = Y_j
				buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin] + 1
			else:
				if buffer_2[j - string_2_begin] < buffer_1[j - string_2_begin + 1]:
					# Case 2: Take the length of the LCS of the upper position
					buffer_2[j - string_2_begin + 1] = buffer_1[j - string_2_begin + 1]
				else:
					# Case 3: Take the length of the LCS of the Left
					buffer_2[j - string_2_begin + 1] = buffer_2[j - string_2_begin]
		
        # Fill the array Q_temp 
        # **
		Q_temp[i + 1] = buffer_2[length_2]
		# Copy buffer 2 to buffer 1
		for ii in range(length_2 + 1):
			buffer_1[ii] = buffer_2[ii]
	return
	
	
#
# Space Efficient Backward LCS length: To optimize resources, add the values of Q_temp calculated in
# the previous step to the new values into Q_temp
#	
def backward_space_efficient_lcs_length(String_1,
                                        String_2,
                                        string_1_begin, string_1_end,
                                        string_2_begin, string_2_end,
                                        Q_temp
                                        ):
	length_1 = string_1_end - string_1_begin + 1;
	length_2 = string_2_end - string_2_begin + 1;
	
	buffer_1 = [0]*(length_2 + 1)
	buffer_2 = [0]*(length_2 + 1)
	
    ## **
    ## Q_temp[string_1_end + 1] = 0;
	#print(string_1_end)
	#print(string_1_begin - 1)
	for i in range(string_1_end, string_1_begin - 1, -1):
		# Step i
		for j in range(string_2_end, string_2_begin - 1, -1):
			# Step j
			if String_1[i] == String_2[j]:
				# X_i = Y_j
				buffer_2[j - string_2_begin] = buffer_1[j - string_2_begin + 1] + 1
			else:
				if buffer_2[j - string_2_begin + 1] < buffer_1[j - string_2_begin]:
					buffer_2[j - string_2_begin] = buffer_1[j - string_2_begin]
				else:
					buffer_2[j - string_2_begin] = buffer_2[j - string_2_begin + 1]
		
		
		Q_temp[i] = Q_temp[i] + buffer_2[0]
        ## Copy buffer 2 to buffer 1
		for ii in range(length_2 + 1):
			buffer_1[ii] = buffer_2[ii]

	
	

def lcs_divide_and_conquer(String_1, String_2,
                           string_1_begin, string_1_end,
                           string_2_begin, string_2_end,
                           Q,
                           LCS_xset,
                           LCS_yset
                           ):
	# auto search = LCS_xset->find(string_1_end + 1);
    # if(search != )
    # Base cases when one of the two string lengths are less than or equal to 2 */
	length_1 = string_1_end - string_1_begin + 1
	length_2 = string_2_end - string_2_begin + 1

    # For strings of length 0 do nothing */
	if length_1 <= 0 or length_2 <= 0:
		return

	# The test is to test if are equals and were added to the LSC_Xset */
	if (length_1 <= 2 or length_2 <= 2):
		if (String_1[string_1_end] == String_2[string_2_end]):
			# Add to the LCS and search over string_1_end - 1, string_2_end - 1 */
			LCS_xset[string_1_end + 1] = String_1[string_1_end]
			LCS_yset[string_2_end + 1] = String_2[string_2_end]
			
			## LCS_xset.append(string_1_end + 1)
			## LCS_yset.append(string_2_end + 1)
			string_1_end = string_1_end - 1
			string_2_end = string_2_end - 1
			length_1 = length_1 - 1
			length_2 = length_2 - 1
			
		if (length_1 <= 0 or length_2 <= 0):
			return
			
		if (length_1 == 1):
			# Find if  there is an occurrence of the character of String_1 in String_2 */
			for ii in range(string_2_begin, string_2_end + 1):
				if(String_1[string_1_begin] == String_2[ii]):
					#
					LCS_xset[string_1_begin + 1] = String_1[string_1_begin]
					LCS_yset[ii + 1] = String_2[ii]
					
					## LCS_xset.append(string_1_begin + 1)
					## LCS_yset.append(ii + 1)
					break
			return

		if (length_1 == 2):
			# Test the first character in String_1 */
			jj = string_2_begin
			ii = string_2_begin
			
			for ii in range(string_2_begin, string_2_end + 1):
				if (String_1[string_1_begin] == String_2[ii]):
					# ++
					# LCS_set->insert(string_1_begin);
					LCS_xset[string_1_begin + 1] = String_1[string_1_begin]
					LCS_yset[ii + 1] = String_2[ii]
					
					## LCS_xset.append(string_1_begin + 1)
					## LCS_yset.append(ii + 1)
					jj = ii + 1
					break
			
            # Test the second character in String_1 */
			for kk in range(jj, string_2_end + 1):
				if (String_1[string_1_begin + 1] == String_2[kk]):
					# ++
					# LCS_set->insert(string_1_begin + 1);
					
					LCS_xset[string_1_begin + 2] = String_1[string_1_begin + 1]
					LCS_yset[kk + 1] = String_2[kk]
					## LCS_xset.append(string_1_begin + 2)
					## LCS_yset.append(kk + 1)
					break			
			return
        
		if (length_2 == 1):
			for jj in range(string_1_begin, string_1_end + 1):
				if (String_2[string_2_begin] == String_1[jj]):
					# ++
					# LCS_set->insert(jj);
					LCS_xset[jj + 1] = String_1[jj]
					LCS_yset[string_2_begin + 1] = String_2[string_2_begin]
					## LCS_xset.append(jj + 1)
					## LCS_yset.append(string_2_begin + 1)
					break
			return
			
		if (length_2 == 2):
			ii = string_1_begin
			jj = string_1_begin
			
			for jj in range(string_1_begin, string_1_end + 1):
				if (String_2[string_2_begin] == String_1[jj]):
					# ++
					# LCS_set->insert(jj);
					LCS_xset[jj + 1] = String_1[jj]
					LCS_yset[string_2_begin + 1] = String_2[string_2_begin]
					## LCS_xset.append(jj + 1)
					## LCS_yset.append(string_2_begin + 1)
					ii = jj + 1
					break
			
			for kk in range(ii, string_1_end + 1):
				if (String_2[string_2_begin + 1] == String_1[kk]):
					# ++
                    # LCS_set->insert(jj);
					LCS_xset[kk + 1] = String_1[kk]
					LCS_yset[string_2_begin + 2] = String_2[string_2_begin + 1]
					
					## LCS_xset.append(kk + 1)
					## LCS_yset.append(string_2_begin + 2)
					break
			return
			

    # Remember that we use 0-based strings */
    # Calculates the middle point of String_2 */
	string_2_middle = math.floor((string_2_begin + string_2_end)/2)
	
	space_efficient_lcs_length(String_1, String_2, string_1_begin, string_1_end, string_2_begin, string_2_middle, Q)
	
	backward_space_efficient_lcs_length(String_1, String_2, string_1_begin, string_1_end, string_2_middle + 1, string_2_end, Q)
	# print(Q)

    # Find the index that maximizes the sum of c and g*/
	q_index = string_1_end + 1
	Q_max_value = -100	
		
	##
	for qi in range(string_1_end + 1, string_1_begin, -1):
		if (Q[qi] >= Q_max_value):
			Q_max_value = Q[qi]
			q_index = qi
			
	if (Q[string_1_begin] > Q_max_value):
		Q_max_value = Q[string_1_begin]
		q_index = string_1_begin
    
	if (Q_max_value == 0):
		return

    #if(DEBUG_LCS_D_C){
    #    std::cout << "[" << __LINE__ << "] q_index that maximizes c+g:" << q_index << std::endl;
    #}
	# ++
    # Convert q_index to X 0-based indexes */
	q_index_x = q_index - 1
	if (q_index_x < 0):
		q_index_x = 0

    # Add that index to the structure */
	if (q_index != 0 and q_index != string_1_begin):
		if(String_1[q_index_x] == String_2[string_2_middle]):
			LCS_xset[q_index] = String_1[q_index_x]
			LCS_yset[string_2_middle + 1] = String_2[string_2_middle]
			## LCS_xset.append[q_index]
			## LCS_yset.append[string_2_middle + 1]

	if (q_index == string_1_begin):
		lcs_divide_and_conquer(String_1, String_2, string_1_begin, string_1_end, string_2_middle + 1, string_2_end, Q, LCS_xset, LCS_yset)
	else:
		if(q_index == string_1_end + 1):
			lcs_divide_and_conquer(String_1, String_2, string_1_begin, string_1_end, string_2_begin, string_2_middle, Q, LCS_xset, LCS_yset)
		else:
			# Make the recursive calls */
			lcs_divide_and_conquer(String_1, String_2, string_1_begin, q_index_x, string_2_begin, string_2_middle, Q, LCS_xset, LCS_yset)
			lcs_divide_and_conquer(String_1, String_2, q_index_x + 1, string_1_end, string_2_middle + 1, string_2_end, Q, LCS_xset, LCS_yset)
	return
	
def LCS_DIVIDE_CONQUER(String_1, String_2, LCS_XSet, LCS_YSet):
	length_1 = len(String_1)
	length_2 = len(String_2)

    # Check if one of the Strings is empty */
	
    # Array of chars that keeps the sum of arrays c and g */
	Q_temp = [0]*(length_1 + 1)
	# print(Q_temp)

    # Call Divide and Conquer */
	lcs_divide_and_conquer(String_1, String_2, 0, length_1 - 1, 0, length_2 - 1, Q_temp, LCS_XSet, LCS_YSet)
	return
	
# Utils: Reconstruct LCS


def memory():
    import os
    from wmi import WMI
    w = WMI('.')
    result = w.query("SELECT WorkingSet FROM Win32_PerfRawData_PerfProc_Process WHERE IDProcess=%d" % os.getpid())
    return int(result[0].WorkingSet)

if __name__ == "__main__":
	X = "AA"
	##X = "ATCGAGCGGGCAATATGTACATATTTACCTCTACAATGGATGCGCAAAAACATTCCCTCATCACAATTGAACTAAAGGGCGCGAGACGTATTCCCCGGTTGCTGCTTGGGACCATAAAACCTCATTCACCGCGGAACCCGACTATGCGACTGGACGGCCTATTTACCGAGAGCTGTTCGAAGGCTGGTTGAATACATGGCAGAAGATTGAGGTGTCCTAAACTTACGCGGCCATAACACCTTAGCCGTCTCGGGGGAATAAGTGACCTATGCACCAGACGCCGCTTGCGATTTCGACCAACAGCGGGAACGGCTGTGCAGTCACACCGCTGTGTAGCGGACAGTCTGAGCTACCCTCTCAAGCACGAGATCTACAGGGCGGGGTAGAAGCCGTCGCTTCGGGTCCATGCGGGGGGTAAAACCCTGTTTAAGAGGTCCGGGCAGCATACGCGCGGCACCCATCTCTCTTCATTCGCTTATTGTGAACGTTCGAAAGCACAATGTGGTTTATGT"
	Y = "A"
	##Y = "GCTACTGTGGAGAGGGTTTGTGAATCTAGGAGCACAAAAAAGCGGCGCACTTCAGGCATAAAAGGATGGATTTTTGACAATCCCCGATGTCCAAGCTATGGTCCCTTAACAGCAATGCTAGGGAGCAATAAACATAACCATCCACAGTGAATTGATCCGAAGGGGGTCGGCATCGGAAGCTTGAAATTGAGAAGCGGGGAGTTACCGGTCAATACGAGCATACAGACAATCGTCGTCGATACTCTCCAGCCGACTGAAAACGGGAGAAAAAACCACTGGAAATGGCAGTACCAGCTCGACATTCGCGTGCCCCCGGCCAACCGTTCATTGGAGCAATAAGTGGATGGATGAGCGCCACATGTATTGCCTAATGGGCCTCTTTGGTCATGCTAGGCAACAGCTGGATCTACAGAAGCGCGATTGTCGGGCACATTAGATTATAGTGTTGAAAAAGTCCTTGTTCGACGGCGTGGGGAGTCTCTCCAACGTGATTTACGGACGCGAATTTAAAC"
	LCS_XSet = {}
	LCS_YSet = {}
	LCS_DIVIDE_CONQUER(X, Y, LCS_XSet, LCS_YSet)
	lcs_size = len(LCS_XSet)
	pos = 0
	print("lcs_size = " + str(lcs_size) + " LCS = " + str(LCS_XSet))
	for i in X:
		if (pos + 1) in LCS_XSet:
			print("X[" + str(pos + 1) + "] = " + X[pos])
		pos = pos + 1

	print(memory())