import math as m
import sys

def log2(a):
    return m.log(a)/m.log(2)

d = [0.39, 0.20, 0.14, 0.11, 0.09, 0.07]
somme = 0
for i in d:
    somme += i * log2(i)

print(-1 * somme)
