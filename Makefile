all: huffman entropie code_arithmetique decode_arithmetique

GCC_OPT= -Wall -Werror #-g #commenter "-g" pour enlever les infos de debug
LDFLAGS = -lm
SRC_UTL = src_utils/
SRC_ENT = src_entropie/
SRC_HUFF = src_huffman/
SRC_ARIT = src_arithmetique/

# Entropie
entropie : $(SRC_ENT)entropie.o
	gcc -o $@ $^ $(LDFLAGS)

entropie.o: $(SRC_ENT)entropie.c
	gcc $(GCC_OPT) -c $^

# Huffman
huffman : $(SRC_HUFF)huffman.o $(SRC_UTL)collection.o $(SRC_UTL)groupe.o
	gcc -o $@ $^

huffman.o: $(SRC_HUFF)huffman.c
	gcc $(GCC_OPT) -c $^

# Codage arithmetique
code_arithmetique : $(SRC_ARIT)code_arithmetique.o $(SRC_UTL)table_parser.o 
	gcc -o $@ $^

code_arithmetique.o: $(SRC_ARIT)code_arithmetique.c
	gcc $(GCC_OPT) -c $^

# Décodage arithmétique
decode_arithmetique : $(SRC_ARIT)decode_arithmetique.o $(SRC_UTL)table_parser.o 
	gcc -o $@ $^ $(LDFLAGS)

decode_arithmetique.o: $(SRC_ARIT)decode_arithmetique.c
	gcc $(GCC_OPT) -c $^

# Utils
collection.o : $(SRC_UTL)collection.o 
	gcc $(GCC_OPT) -c $^

groupe.o: $(SRC_UTL)groupe.c
	gcc $(GCC_OPT) -c $^

table_parser.o: $(SRC_UTL)table_parser.c
	gcc $(GCC_OPT) -c $^


.PHONY : clean
clean:
	rm -f huffman entropie code_arithmetique decode_arithmetique src_*/*.o
