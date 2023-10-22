
from random import randint as r


def check_prime(n):
	for i in range(2,int(n**0.5)+1):
		if n%i==0: return 0
	return 1


def tst_prime():
	with open("prime.txt", "w") as file:
		for x in range(1000):
			y=r(1,10000000000000)
			file.write(bin(y)[2:]+"\n")
			file.write(bin(check_prime(y))[2:]+"\n")
			

tst_prime()




				
