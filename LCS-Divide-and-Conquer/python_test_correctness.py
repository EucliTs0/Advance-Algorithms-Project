import lcsdc

if __name__ == "__main__":
	# Read X001 to X100 and Y001 to Y100
	path = './test/'
	destfilename = 'python_results.txt'
	
	dest = open(path + destfilename, 'w', encoding="utf-8", errors='ignore')
	for i in range(1, 101):
		xfilename =  'X' + str(i).rjust(3, '0') + '.txt'
		yfilename =  'Y' + str(i).rjust(3, '0') + '.txt'
		
		with open(path + xfilename, 'r') as x_file:
			X = x_file.readline().rstrip('\n')
		with open(path + yfilename, 'r') as y_file:
			Y = y_file.readline().rstrip('\n')
		
		LCS_XSet = {}
		LCS_YSet = {}
		lcsdc.LCS_DIVIDE_CONQUER(X, Y, LCS_XSet, LCS_YSet)
		lcs_size = len(LCS_XSet)
		
		print(X)
		print(Y)
		print(LCS_XSet)
		
		s = str(i) + ':' + str(lcs_size) + '\n'
		print(s)
		dest.write(s)
		x_file.close()
		y_file.close()
		
	dest.close()
