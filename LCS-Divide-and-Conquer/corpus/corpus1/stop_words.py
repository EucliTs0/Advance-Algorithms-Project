import os
from nltk.corpus import stopwords

cachedStopWords = stopwords.words("english")

if __name__ == "__main__":
    source_directory = 'corpus_preprocessed'
    directory = 'corpus_wo_stop_words'

    for file in os.listdir(source_directory):
        # print(file)
        dest = open(directory + '/' + file, 'w', encoding="utf-8", errors='ignore')
        with open(source_directory + '/' + file, encoding="utf-8", errors='ignore') as readfile:
            for line in readfile:
                print(line)
                write_line = ' '.join([word for word in line.split() if word not in cachedStopWords])
                dest.write(write_line + '\n')
                
        readfile.close()
        dest.close()

    
    #dest = open('./corpus_wo_stop_words/test.txt','w')
    #with open('./' + 'corpus_wo_stop_words/' + filename, encoding="utf8") as readfile:
    #    for line in readfile:
    #        write_line = ' '.join([word for word in line.split() if word not in cachedStopWords])
    #        dest.write(write_line + '\n')
        
    #readfile.close()
    #dest.close()
    


## g0pA_taska.txt
## f.write('hi there\n')
## f.write('hi there' + os.linesep) # same result as previous line ?????????
## f.close()
