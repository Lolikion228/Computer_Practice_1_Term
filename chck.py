n=int(input(),2)
def check_prime(n):
	for i in range(2,int(n**0.5)+1):
		if n%i==0: return 0
	return 1
print("is prime = ",check_prime(n))
