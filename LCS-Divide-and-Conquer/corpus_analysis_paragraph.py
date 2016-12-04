import os
import string
import lcsdc_word_based

def remove_punctuation(input_string):
	remove_punctuation_map = dict((ord(char), None) for char in string.punctuation)
	return input_string.translate(remove_punctuation_map)

if __name__ == "__main__":
	source_path = './corpus/corpus1/corpus_preprocessed'
	source_path_originals = './corpus/corpus1/corpus_preprocessed/originals'
	dest_path = './corpus/corpus1'
	
	task_name = 'orig_taskd'
	task = 'taskd'
	original_f = task_name + '.txt'
	

	# Read original, parse paragraphs, words
	# with open(source_path_originals + '/' + original_f, errors='ignore') as ofile:
	with open(source_path_originals + '/' + original_f, encoding="ascii", errors='ignore') as ofile:
		content_X = ofile.read()
	ofile.close()
	paragraphs_X = content_X.split('.\n')
	
	#i = 1
	#for p in paragraphs_X:
	#	print(p)
	#	i = i + 1
	#print(i)
	
	i = 1
	paragraph_words_X = {}
	for para in paragraphs_X:
		p = remove_punctuation(para)
		words = []
		for word in p.split():
			# print(word.lower())
			words.append(word.lower())
		
		paragraph_words_X[i] = words
		i = i + 1
	
	#for k, w in paragraph_words.items():
	#	for i in w:
	#		print(i)
	
	
	## Read all files for Y:
	
	for file in os.listdir(source_path):
        # print(file)
		filename, extension = os.path.splitext(file)
		
		if os.path.isdir(os.path.join(source_path, file)):
			continue
		
		if (filename.find(task) > 0):
			Y = []
			with open(source_path + '/' + file, encoding="utf-8", errors='ignore') as readfile:
				content_Y = readfile.read()
			readfile.close()
			paragraphs_Y = content_Y.split('.\n')
			
			i = 1
			paragraph_words_Y = {}
			for para in paragraphs_Y:
				p = remove_punctuation(para)
				words = []
				for word in p.split():
					words.append(word.lower())
				
				paragraph_words_Y[i] = words
				i = i + 1
			
			LCS_Score = 0
			
			
			for key_Y, item_Y in paragraph_words_Y.items():
				N_words_Y = len(item_Y)
				N_LCS_paragraph = 0
				score = 0
				N_words_LCS = 0
				N_words_X_selected = 0
				p_index_X = 1
				for key_X, item_X in paragraph_words_X.items():
					LCS_XSet = {}
					LCS_YSet = {}
					lcsdc_word_based.LCS_DIVIDE_CONQUER(item_X, item_Y, LCS_XSet, LCS_YSet)
					Size_LCS = len(LCS_XSet)
					N_words_X = len(item_X)
					if(N_words_X > 0):
						s = Size_LCS/N_words_X
					else:
						s = 0
					if(s > score):
						score = s
						N_words_LCS = Size_LCS
						N_words_X_selected = N_words_X
						p_index_X = key_X
					
					# print('Para X: ' + str(key_X) + ', Para Y: ' + str(key_Y) + ', LCS: ' + str(Size_LCS))
				ss = original_f + ', ' + file + ', ' + str(p_index_X) + ', ' + str(key_Y) + ', ' + str(N_words_X_selected) + ', ' + str(N_words_Y) + ', ' + str(N_words_LCS) + ', ' + str(score)
				print(ss)
					
	