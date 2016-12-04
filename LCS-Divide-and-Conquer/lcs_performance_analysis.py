import os
import string
import lcsdc
import time

if __name__ == "__main__":
	source_directory = 'performance_tests'
	dest_directory = 'performance_tests/python_char'
	dest_file = 'test_time_python_char.txt'
	f = open(dest_directory + '/' + dest_file, 'w')
	
	for i in range(2,12):
		X_filename = 'X_' + str(i) + '.txt'
		Y_filename = 'Y_' + str(i) + '.txt'
		
		with open(source_directory + '/' + Y_filename, encoding="ascii", errors='ignore') as readY:
			for lineY in readY:
				with open(source_directory + '/' + X_filename, encoding="ascii", errors='ignore') as readX:
					for lineX in readX:
						LCS_XSet = {}
						LCS_YSet = {}
						
						size_of_X = len(lineX)
						size_of_Y = len(lineY)
						start_time = time.process_time()
						lcsdc.LCS_DIVIDE_CONQUER(lineX, lineY, LCS_XSet, LCS_YSet)
						elapse_time = time.process_time() - start_time
						
						lcs_size = len(LCS_XSet)
						
						s = str(size_of_X) + ', ' + str(size_of_Y) + ', ' + str(lcs_size) + ', ' + str(elapse_time)
						print(s + '\n')
						f.write(s + '\n')
					
		