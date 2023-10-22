
from random import randint as r



def tst_div():
	with open("div.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(5000))
			y=r(1,2**(5000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(x//y)[2:]+"\n")	
			file.write(bin(x%y)[2:]+"\n")	
	
tst_div()




				
