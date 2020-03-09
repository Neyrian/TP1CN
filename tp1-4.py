import math as m
import sys

def log2(a):
    return m.log(a)/m.log(2)

# d = [0.39, 0.20, 0.14, 0.11, 0.09, 0.07]
# somme = 0
# for i in d:
#     somme += i * log2(i)
#
# print(-1 * somme)

if (len(sys.argv) != 2):
    print("Erreur d'utilsation use : python tp1.py data.txt")
    exit(1)

try:
    fichier = open(sys.argv[1], "r")
except:
    print("Erreur fichier data")
    exit(1)

somme = 0
print("########### DATA ###########")

for line in fichier:
    try:
        if (float(line) < 0 or float(line) > 1):
            print(line + ' n\'est pas une proba valide')
            exit(1)
        somme += float(line) * log2(float(line))
        print(line)
    except:
        print(line + ' n\'est pas une proba valide')
        exit(1)

print('Resultat : ' + str((-1 * somme)))
