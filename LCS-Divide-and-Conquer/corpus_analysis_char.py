import os
import lcsdc

if __name__ == "__main__":
	source_path = './corpus/corpus1/corpus_wo_stop_words'
	source_path_originals = './corpus/corpus1/corpus_wo_stop_words/originals'
	dest_path = './corpus/corpus1/lcs_cb_wo_stop_words'
	
	task_name = 'orig_taske'
	task = 'taske'
	original_f = task_name + '.txt'
	
	X = ""
	# Read original
	# with open(source_path_originals + '/' + original_f, errors='ignore') as ofile:
	with open(source_path_originals + '/' + original_f, encoding="utf-8", errors='ignore') as ofile:
		for l in ofile:
			X = X + l
	ofile.close()
	
	#print(X)
	
	for file in os.listdir(source_path):
        # print(file)
		filename, extension = os.path.splitext(file)
		
		if os.path.isdir(os.path.join(source_path, file)):
			continue
		
		if (filename.find(task) > 0):
			# Read File
			# print(file)
			Y = ""
			with open(source_path + '/' + file, encoding="utf-8", errors='ignore') as readfile:
			# with open(source_path + '/' + file, errors='ignore') as readfile:
				for line in readfile:
					Y = Y + line
			readfile.close()	
			# print(Y)
			
			LCS = ""
			LCS_XSet = {}
			LCS_YSet = {}
			
			# Sizes in char of X and Y
			# Words of X and Y
			
			lcsdc.LCS_DIVIDE_CONQUER(X, Y, LCS_XSet, LCS_YSet)
			# print(X)
			# Count words of X and Y
			chars_in_X = len(X)
			chars_in_Y = len(Y)
			Xsplit = X.split()
			N_words_X = len(Xsplit)
			Ysplit = Y.split()
			N_words_Y = len(Ysplit)
			
			pos = 0
			if(len(LCS_XSet) > 0):
				for c in X:
					if ((pos+1) in LCS_XSet):
						LCS = LCS + LCS_XSet[(pos+1)]
					pos = pos + 1
					
			chars_in_LCS = len(LCS)
			LCS_split = LCS.split()
			N_words_LCS = len(LCS_split)
			
			N_words_LCS_in_X = 0
			# print(Xsplit)
			for w in LCS_split:
				# print(w)
				if w in Xsplit:
					N_words_LCS_in_X = N_words_LCS_in_X + 1


			# print(LCS)
			s = original_f + ', ' + file + ', ' + str(chars_in_X) + ', ' + str(chars_in_Y) + ', ' + str(N_words_X) + ', ' + str(N_words_Y) + ', ' + str(chars_in_LCS) + ', ' + str(N_words_LCS) + ', ' + str(N_words_LCS_in_X)
			print(s)
			dest = open(dest_path + '/' + file, 'w', encoding="utf-8", errors='ignore')
			dest.write(LCS)
			dest.close()
			
			
