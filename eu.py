
from random import randint as r

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

				
				
def tst_eu():
	with open("eu.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(3000))
			y=r(1,2**(3000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(gcd(x,y))[2:]+"\n")


	
tst_eu()




				
