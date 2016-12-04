import string
import random

l = 11
size = 2**l
number_of_samples = 30

def string_generator(string_size, alphabet):
    return ''.join(random.choice(alphabet) for _ in range(string_size))


alpha = string.ascii_uppercase + string.digits


destX = open('X_' + str(l) + '.txt','w')
destY = open('Y_' + str(l) + '.txt','w')
stry = string_generator(size, alpha)
for x in range(number_of_samples):
    print(x)
    strx = string_generator(size, alpha)
    destX.write(strx + '\n')
	
destY.write(stry + '\n')
destX.close()
destY.close()

    

