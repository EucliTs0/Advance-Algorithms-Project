import os
import lcsdc_word_based

if __name__ == "__main__":
	source_path = './corpus/corpus1/corpus_wo_stop_words_ow'
	source_path_originals = './corpus/corpus1/corpus_wo_stop_words_ow/originals'
	dest_path = './corpus/corpus1/lcs_cb_wo_stop_words_ow'
	
	task_name = 'orig_taske'
	task = 'taske'
	original_f = task_name + '.txt'
	
	X = []
	# Read original
	# with open(source_path_originals + '/' + original_f, errors='ignore') as ofile:
	with open(source_path_originals + '/' + original_f, encoding="utf-8", errors='ignore') as ofile:
		for l in ofile:
			X.append(l.rstrip('\n'))
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
			Y = []
			with open(source_path + '/' + file, encoding="utf-8", errors='ignore') as readfile:
			# with open(source_path + '/' + file, errors='ignore') as readfile:
				for line in readfile:
					Y.append(line.rstrip('\n'))
			readfile.close()	
			# print(Y)
			
			LCS = []
			LCS_XSet = {}
			LCS_YSet = {}
			
			# Sizes in char of X and Y
			# Words of X and Y
			
			lcsdc_word_based.LCS_DIVIDE_CONQUER(X, Y, LCS_XSet, LCS_YSet)
			# print(X)
			# Count words of X and Y
			N_words_X = len(X)
			N_words_Y = len(Y)
			
			pos = 0
			if(len(LCS_XSet) > 0):
				for word in X:
					if ((pos+1) in LCS_XSet):
						LCS.append(LCS_XSet[(pos+1)])
					pos = pos + 1
					
			N_words_in_LCS = len(LCS)
			
			# print(Xsplit)

			# print(LCS)
			s = original_f + ', ' + file + ', ' + str(N_words_X) + ', ' + str(N_words_Y) + ', ' + str(N_words_in_LCS)
			print(s)
			dest = open(dest_path + '/' + file, 'w', encoding="utf-8", errors='ignore')
			for word in LCS:
				dest.write(word + '\n')
			dest.close()
			
			
