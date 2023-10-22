
from random import randint as r


					
def tst_copy():
	with open("copy.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			file.write(bin(x)[2:]+"\n")	



tst_copy()
			
