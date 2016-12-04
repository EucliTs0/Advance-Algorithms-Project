import os
import string
from nltk.corpus import stopwords

cachedStopWords = stopwords.words("english")

def remove_punctuation(input_string):
	remove_punctuation_map = dict((ord(char), None) for char in string.punctuation)
	return input_string.translate(remove_punctuation_map)
	
if __name__ == "__main__":
	source_directory = 'corpus_preprocessed'
	directory = 'corpus_wo_stop_words'

	for file in os.listdir(source_directory):
		print(file)
		dest = open(directory + '/' + file, 'w', encoding="utf-8", errors='ignore')
		with open(source_directory + '/' + file, encoding="ascii", errors='ignore') as readfile:
			for line in readfile:
				write_line = ' '.join([word.lower() for word in line.split() if word not in cachedStopWords])
				write_line = remove_punctuation(write_line)
				print(write_line)
				dest.write(write_line + '\n')
                
				
		readfile.close()
		dest.close()
		