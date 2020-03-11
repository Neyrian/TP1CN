 +===============================================================+
 | GROUPE : MALOD Victor -- LANQUETIN Alexis -- BLANQUET Antoine |
 +===============================================================+

Dans ce document, les commentaires commencent par "#", et les 
prompts par "   $>".

I / Résumé des commandes :
==========================

    1. Entropie :
    -------------

#Compiler le programme C :
    $> make entropie
#Executer le programme avec un ensemble spécifique :
#(ici contenu dans le fichier X)
    $> ./entropie X

    2. Code de Huffman :
    --------------------

#Compiler le programme C :
    $> make huffman
#Executer le programme avec un ensemble spécifique
#(ici contenu dans le fichier X), et une multiplicité :
    $> ./huffman X 2

    3. Code arithmétique :
    ----------------------

#Compiler le programme C :
    $> make code_arithmetique
#Executer le programme avec une table spécifique
#(ici contenu dans le fichier tableWIKI), et un message :
    $> ./code_arithmetique tableWIKI WIKI

    4. Décode arithmétique :
    ------------------------

#Compiler le programme C :
    $> make decode_arithmetique
#Executer le programme avec une table spécifique
#(ici contenu dans le fichier tableWIKI), et un code optimisé :
    $> ./decode_arithmetique 4.171875

    5. Généralités :
    ----------------

#Tout compiler :
    $> make [all]
#Tout nettoyer :
    $> make clean

II / Remarques :
================

    Des gestions des erreurs ont été incorporées dans chaque 
    programmes pour éviter à l'utilisateur de lancer de faux
    calculs.
    Aussi, nous invitons l'utilisateur à feuilleter le code
    pour qu'il comprenne de lui même d'où vient les compléxités
    énnoncées dans le compte-rendu.
    Nous avons effectué des tests de fuite de mémoire avec 
    valgrind sur chacun de nos programmes, et aucunes fuites
    n'ont été constatées.
