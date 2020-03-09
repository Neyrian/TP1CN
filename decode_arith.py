import sys

if len(sys.argv) != 3:
    print("usage:  python3 decode_arith.py code_message n")
    sys.exit(0)

Vmessage = float(sys.argv[1])

dico_lettre = {
    ##lettre : [probabilité, borne inf, borne supp]
    "W" : [0.25, 0, 0.25],
    "I" : [0.50, 0.25, 0.75],
    "K" : [0.25, 0.75, 1]
}

def lettre(val):
    for lettre in dico_lettre:
        if (val >= dico_lettre[lettre][1] and val <= dico_lettre[lettre][2]):
            return lettre
    sys.exit(1)

## algo de decompression
sym = lettre(Vmessage)
message = sym
for i in range(1, int(sys.argv[2])):
    Vmessage = (Vmessage - dico_lettre[sym][1])/dico_lettre[sym][0]
    sym = lettre(Vmessage)
    message += sym

print("Le message decodé est ", message)
