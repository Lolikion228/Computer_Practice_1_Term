
from random import randint as r

		
		
def tst_swap():
	with open("swap.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			y=r(1,2**(100000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(x)[2:]+"\n")
		
		


tst_swap()





				
