
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
def multiplicative_inverse(a, m):
  """Find the multiplicative inverse of a modulo m."""
  def extended_euclidean(a, b):
      """Performs the extended Euclidean algorithm."""
      if a == 0:
          return (b, 0, 1)
      else:
          gcd, x, y = extended_euclidean(b % a, a)
          return (gcd, y - (b // a) * x, x)

  gcd, x, _ = extended_euclidean(a, m)
  if gcd == 1:
      return x % m  # Ensure inverse is positive
  else:
      raise ValueError(f"Multiplicative inverse for {a} mod {m} does not exist")
      
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def check_prime(n):
	for i in range(2,int(n**0.5)+1):
		if n%i==0: return 0
	return 1
def tst_add():
	with open("add.txt", "w") as file:
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
			if x0+y0>=0:
				file.write(bin(x0+y0)[2:]+"\n")
			else:
				file.write("-"+bin(x0+y0)[3:]+"\n")
		


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
				
				
				
def tst_eu():
	with open("eu.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(3000))
			y=r(1,2**(3000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(gcd(x,y))[2:]+"\n")
				
def tst_div():
	with open("div.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(5000))
			y=r(1,2**(5000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(x//y)[2:]+"\n")	
			file.write(bin(x%y)[2:]+"\n")	
	
		
		
def tst_swap():
	with open("swap.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			y=r(1,2**(100000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(x)[2:]+"\n")
		
		
def tst_shft1():
	with open("shft1.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			y=r(1,2**(100000))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(x*2)[2:]+"\n")
			file.write(bin(x//2)[2:]+"\n")
		
		
def tst_shft2():
	with open("shft2.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			z=r(0,255)
			file.write(bin(x)[2:]+"\n")
			file.write(bin(z)[2:]+"\n")
			file.write(bin(x*(2**z))[2:]+"\n")
			file.write(bin(x//(2**z))[2:]+"\n")
					
				


def tst_mod_pow():
	with open("pow.txt", "w") as file:
		for j in range(100):
			x=r(1,2**(50))
			y=r(1,2**(15))
			z=r(1,2**(50))
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(z)[2:]+"\n")
			file.write(bin((x**y)%z)[2:]+"\n")
					
def tst_set_bit():
	with open("set_bit.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			y=r(0,255)
			z=r(0,1)
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			file.write(bin(z)[2:]+"\n")
			file.write(bin(set_bit(x,y,z))[2:]+"\n")
					
def tst_copy():
	with open("copy.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(100000))
			file.write(bin(x)[2:]+"\n")	


def tst_mult():
	with open("mult.txt", "w") as file:
		for j in range(1000):
			x=r(1,2**(5000))
			x0=x*(-1)**r(1,5)
			y=r(1,2**(5000))
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
		

def tst_prime():
	with open("prime.txt", "w") as file:
		for x in range(1000):
			y=r(1,10000000000000)
			file.write(bin(y)[2:]+"\n")
			file.write(bin(check_prime(y))[2:]+"\n")
			
			
			
def tst_inv():
	with open("inv.txt", "w") as file:
		for i in range(1000):
			x=r(1,2**500)
			y=r(1,2**500)
			file.write(bin(x)[2:]+"\n")
			file.write(bin(y)[2:]+"\n")
			if gcd(x,y)==1:
				file.write(bin(multiplicative_inverse(x,y))[2:]+"\n")
			else:
				file.write("-1"+"\n")



print('swap st')
tst_swap()
print('swap end')
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
print("prime st")		
tst_prime()
print("prime end")
print("inv st")		
tst_inv()
print("inv end")





				
