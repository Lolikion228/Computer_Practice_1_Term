
from random import randint as r


def tst_sub():
	with open("sub.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			x0=x*(-1)**r(1,5)
			y=r(1,2**(100000))
			y0=y*(-1)**r(1,5)
			if x0>=0:
				file.write(bin(x0)[2:]+"\n")
			else:
				file.write("-"+bin(x0)[3:]+"\n")
			if y0>=0:
				file.write(bin(y0)[2:]+"\n")
			else:
				file.write("-"+bin(y0)[3:]+"\n")
			if x0-y0>=0:
				file.write(bin(x0-y0)[2:]+"\n")
			else:
				file.write("-"+bin(x0-y0)[3:]+"\n")
				
				
				
tst_sub()


				
