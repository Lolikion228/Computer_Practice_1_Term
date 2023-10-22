
from random import randint as r

		
		
def tst_shft1():
	with open("shft1.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			y=r(1,2**(100000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(x*2)[2:]+"\n")
			file.write(bin(x//2)[2:]+"\n")
		

tst_shft1()


				
