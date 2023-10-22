
from random import randint as r

def set_bit(t, n, value):
    number=t
    mask = 1 << n  # Создаем маску, сдвигая 1 на n позиций влево
    if value:
        number |= mask  # Устанавливаем бит, применяя побитовое ИЛИ
    else:
        number &= ~mask  # Сбрасываем бит, применяя побитовое И с инвертированной маской
    return number

					
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

tst_set_bit()


				
