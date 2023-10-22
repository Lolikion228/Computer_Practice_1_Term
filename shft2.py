
from random import randint as r


def tst_shft2():
	with open("shft2.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			z=r(0,255)
			file.write(bin(x)[2:]+"\n")
			file.write(bin(z)[2:]+"\n")
			file.write(bin(x*(2**z))[2:]+"\n")
			file.write(bin(x//(2**z))[2:]+"\n")
					
				

tst_shft2()




				
