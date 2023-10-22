
from random import randint as r

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


tst_inv()






				
