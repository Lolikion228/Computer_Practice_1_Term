
from random import randint as r

def tst_mod_pow():
	with open("pow.txt", "w") as file:
		for j in range(2000000):
			x=r(1,2**(30))
			y=r(1,2**(5))
			z=r(1,2**(30))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(z)[2:]+"\n")
			file.write(bin((x**y)%z)[2:]+"\n")

tst_mod_pow()

