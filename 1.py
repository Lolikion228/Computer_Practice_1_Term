
from random import randint as r
from math import ceil
def set_bit(t, n, value):
    number=t
    mask = 1 << n  # Создаем маску, сдвигая 1 на n позиций влево
    if value:
        number |= mask  # Устанавливаем бит, применяя побитовое ИЛИ
    else:
        number &= ~mask  # Сбрасываем бит, применяя побитовое И с инвертированной маской
    return number
    
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def tst_add():
	with open("add.txt", "w") as file:
		for x in range(991,1001):
			for y in range(991,1001):
				x0=x*(-1)**r(1,5)
				y0=y*(-1)**r(1,5)
				if x0>=0:
					file.write(bin(x0)[2:]+"\n")
				else:
					file.write("-"+bin(x0)[3:]+"\n")
				if y0>=0:
					file.write(bin(y0)[2:]+"\n")
				else:
					file.write("-"+bin(y0)[3:]+"\n")
				if x0+y0>=0:
					file.write(bin(x0+y0)[2:]+"\n")
				else:
					file.write("-"+bin(x0+y0)[3:]+"\n")
		print('first')
		for x in range(2**100+991,2**100+1001):
			for y in range(2**100+991,2**100+1001):
				x0=x*(-1)**r(1,5)
				y0=y*(-1)**r(1,5)
				if x0>=0:
					file.write(bin(x0)[2:]+"\n")
				else:
					file.write("-"+bin(x0)[3:]+"\n")
				if y0>=0:
					file.write(bin(y0)[2:]+"\n")
				else:
					file.write("-"+bin(y0)[3:]+"\n")
				if x0+y0>=0:
					file.write(bin(x0+y0)[2:]+"\n")
				else:
					file.write("-"+bin(x0+y0)[3:]+"\n")
		print('second')
		for x in range(2**5000+991,2**5000+1001):
			for y in range(2**5000+991,2**5000+1001):
				x0=x*(-1)**r(1,5)
				y0=y*(-1)**r(1,5)
				if x0>=0:
					file.write(bin(x0)[2:]+"\n")
				else:
					file.write("-"+bin(x0)[3:]+"\n")
				if y0>=0:
					file.write(bin(y0)[2:]+"\n")
				else:
					file.write("-"+bin(y0)[3:]+"\n")
				if x0+y0>=0:
					file.write(bin(x0+y0)[2:]+"\n")
				else:
					file.write("-"+bin(x0+y0)[3:]+"\n")
		print('third')


def tst_sub():
	with open("sub.txt", "w") as file:
		for x in range(991,1001):
			for y in range(991,1001):
				x0=x*(-1)**r(1,5)
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
		print('first')
		for x in range(2**100+991,2**100+1001):
			for y in range(2**100+991,2**100+1001):
				x0=x*(-1)**r(1,5)
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
		print('second')
		for x in range(2**5000+991,2**5000+1001):
			for y in range(2**5000+991,2**5000+1001):
				x0=x*(-1)**r(1,5)
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
		print('third')	

def tst_eu():
	with open("eu.txt", "w") as file:
		for x in range(91,101):#100**2
			for y in range(91,101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(gcd(x,y))[2:]+"\n")		
		for x in range(2**50+91,2**50+101):#2*100**2
			for y in range(91,101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(gcd(x,y))[2:]+"\n")	
		for x in range(2**5000+91,2**5000+101):#3*100**2
			for y in range(2**5000+91,2**5000+101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(gcd(x,y))[2:]+"\n")	
				
def tst_div():
	with open("div.txt", "w") as file:
		for x in range(91,101):
			for y in range(91,101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x//y)[2:]+"\n")	
				file.write(bin(x%y)[2:]+"\n")	
		print('first')
		for x in range(2**50+91,2**50+101):
			for y in range(91,101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x//y)[2:]+"\n")	
				file.write(bin(x%y)[2:]+"\n")
		print('second')
		for x in range(2**3000+91,2**3000+101):#3*100**2
			for y in range(2**3000+91,2**3000+101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x//y)[2:]+"\n")	
				file.write(bin(x%y)[2:]+"\n")
		print('third')
		
		
def tst_swap():
	with open("swap.txt", "w") as file:
		for x in range(91,101):
			for y in range(91,101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				
					
		print('first')
		for x in range(2**50+91,2**50+101):
			for y in range(91,101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				
		print('second')
		for x in range(2**10000+91,2**10000+101):#3*100**2
			for y in range(2**10+91,2**10+101):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
			
		print('third')
		
		
def tst_shft1():
	with open("shft1.txt", "w") as file:
		for x in range(9991,10001):
			file.write(bin(x)[2:]+"\n")
			file.write(bin(x*2)[2:]+"\n")	
			file.write(bin(x//2)[2:]+"\n")	
		print('first')
		for x in range(2**50+9991,2**50+100001):
			file.write(bin(x)[2:]+"\n")
			file.write(bin(x*2)[2:]+"\n")	
			file.write(bin(x//2)[2:]+"\n")	
		print('second')
		for x in range(2**5000+9991,2**5000+100001):#3*100**2
			file.write(bin(x)[2:]+"\n")
			file.write(bin(x*2)[2:]+"\n")	
			file.write(bin(x//2)[2:]+"\n")
		print('third')
		
		
def tst_shft2():
	with open("shft2.txt", "w") as file:
		for x in range(91,101):
			for y in range(245,255):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x*(2**y))[2:]+"\n")	
				file.write(bin(x//(2**y))[2:]+"\n")	
		print('first')
		for x in range(2**50+91,2**50+101):
			for y in range(245,255):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x*(2**y))[2:]+"\n")	
				file.write(bin(x//(2**y))[2:]+"\n")	
		print('second')
		for x in range(2**5000+91,2**5000+101):#3*100**2
			for y in range(245,255):
				file.write(bin(x)[2:]+"\n")
				file.write(bin(y)[2:]+"\n")
				file.write(bin(x*(2**y))[2:]+"\n")	
				file.write(bin(x//(2**y))[2:]+"\n")
		print('third')
					
				
def tst_mod_pow():
	with open("pow.txt", "w") as file:
		for x in range(96,101):#100
			for y in range(996,1001):#100
				for z in range(96,101):#100 all=100*100*100
					file.write(bin(x)[2:]+"\n")
					file.write(bin(y)[2:]+"\n")
					file.write(bin(z)[2:]+"\n")
					file.write(bin((x**y)%z)[2:]+"\n")
		print('first')
		for x in range(2**50+96,2**50+101):#10
			for y in range(2**10+96,2**10+101):#10
				for z in range(96,101):#10 all=10*10*10
					file.write(bin(x)[2:]+"\n")
					file.write(bin(y)[2:]+"\n")
					file.write(bin(z)[2:]+"\n")
					file.write(bin((x**y)%z)[2:]+"\n")
		print('second')
		for x in range(2**5000+5,2**5000+10):#10
			for y in range(2**7+96,2**7+101):#10
				for z in range(96,101):#10 all=10*10*10
					file.write(bin(x)[2:]+"\n")
					file.write(bin(y)[2:]+"\n")
					file.write(bin(z)[2:]+"\n")
					file.write(bin((x**y)%z)[2:]+"\n")
		print('third')

def tst_set_bit():
	with open("set_bit.txt", "w") as file:
		for x in range(2**5000+991,2**5000+1001):#1000
			for y in range(245,255):#255
				for z in range(0,2):#2
					file.write(bin(x)[2:]+"\n")
					file.write(bin(y)[2:]+"\n")
					file.write(bin(z)[2:]+"\n")
					file.write(bin(set_bit(x,y,z))[2:]+"\n")
					
def tst_copy():
	with open("copy.txt", "w") as file:
		for x in range(2**5000+99700,2**5000+100000):#1000
			file.write(bin(x)[2:]+"\n")


def tst_mult():
	with open("mult.txt", "w") as file:
		for x in range(2**100+491,2**100+501):
			for y in range(2**10+491,2**10+501):
				x0=x*(-1)**r(1,5)
				y0=y*(-1)**r(1,5)
				x0=x
				y0=y
				if x0>=0:
					file.write(bin(x0)[2:]+"\n")
				else:
					file.write("-"+bin(x0)[3:]+"\n")
				if y0>=0:
					file.write(bin(y0)[2:]+"\n")
				else:
					file.write("-"+bin(y0)[3:]+"\n")
				if x0*y0>=0:
					file.write(bin(x0*y0)[2:]+"\n")
				else:
					file.write("-"+bin(x0*y0)[3:]+"\n")
		print('first')
		
		for x in range(2**1000+91,2**1000+101):
			for y in range(2**100+91,2**100+101):
				x0=x*(-1)**r(1,5)
				y0=y*(-1)**r(1,5)
				if x0>=0:
					file.write(bin(x0)[2:]+"\n")
				else:
					file.write("-"+bin(x0)[3:]+"\n")
				if y0>=0:
					file.write(bin(y0)[2:]+"\n")
				else:
					file.write("-"+bin(y0)[3:]+"\n")
				if x0*y0>=0:
					file.write(bin(x0*y0)[2:]+"\n")
				else:
					file.write("-"+bin(x0*y0)[3:]+"\n")
		print('second')
		
		for x in range(2**5000+91,2**5000+101):
			for y in range(2**3000+91,2**3000+101):
				x0=x*(-1)**r(1,5)
				y0=y*(-1)**r(1,5)
				if x0>=0:
					file.write(bin(x0)[2:]+"\n")
				else:
					file.write("-"+bin(x0)[3:]+"\n")
				if y0>=0:
					file.write(bin(y0)[2:]+"\n")
				else:
					file.write("-"+bin(y0)[3:]+"\n")
				if x0*y0>=0:
					file.write(bin(x0*y0)[2:]+"\n")
				else:
					file.write("-"+bin(x0*y0)[3:]+"\n")
		print('third')
		


print("add st")	
tst_add()
print("add end")
print("sub st")		
tst_sub()
print("sub end")
print("eu st")		
tst_eu()
print("eu end")	
print("div st")		
tst_div()
print("div end")
print("shft1 st")
tst_shft1()
print("shft1 end")
print("shft2 st")
tst_shft2()
print("shft2 end")
print('swap st')
tst_swap()
print('swap end')
print('set_bit st')
tst_set_bit()
print('set_bit end')
print('copy st')
tst_copy()
print('copy end')
print('mult st')
tst_mult()
print('mult end')
print("pow st")		
tst_mod_pow()
print("pow end")



				
