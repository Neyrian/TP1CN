import sys

if len(sys.argv) != 2:
    print("usage:  python3 code_arith.py message")
    sys.exit(0)

message = sys.argv[1]

dico_lettre = {
    'W' : [0.25, 0, 0.25],
    'I' : [0.50, 0.25, 0.75],
    'K' : [0.25, 0.75, 1]
}

## algo de compression
Binf = 0
Bsup = 1
Vmessage = 1
Vecart = Bsup - Binf
for lettre in message:
    Bsup = Binf + Vecart * dico_lettre[lettre][2]
    Binf = Binf + Vecart * dico_lettre[lettre][1]
    Vmessage = (Bsup + Binf)/2
    Vecart = Bsup - Binf

print("Le code de ", message, " est ", Vmessage)
