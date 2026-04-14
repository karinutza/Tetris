            Proiect pentru Tehnici de programare 
                Un joc Tetris (roz)
                            De Barbul Karina-Gabriela

                            
Introducere
Tetris este un joc tip puzzle, creat in 1984 de un inginer rus. Numele jocului provine din combinația prefixului “tetra-”, care reprezintă numărul pieselor din segment (patru), și “-tenis”, care era jocul preferat al creatorului.

Obiectivul jocului este să aranjezi piesele geometrice pentru a forma linii orizontale fără spații goale.
Piesele pot fi rotite si mutate in timp ce coboara, iar odata ce o linie este completa, aceasta dispare.


Gameplay
Logica jocului
  •Jocul va trebui sa genereze aleatoriu una dintre cele 7 forme setate de creator (I, J, L, O, S, T, Z) 
  •Va trebui luata in considerare si miscarea si controlul pieselor in timp ce acestea coboara. De exemplu avem comenzile:
    oSageata stanga/dreapta reprezinta mutarea piesei pe orizontala;
    oSageata sus - rotirea piesei la 90 de grade;
    oSageata jos – accelerarea caderii (“soft drop”);
    oTasta space – cadere instantanee (“hard drop”).
  •Trebuie sa tinem cont de limitarile ecanului si a spatiului in care cad piesele.
  •Eliminarea liniilor: odata complete o linie, aceasta trebuie sa dispara si toate piesele de deasupra ei sa se mute cu un rand mai jos.
  •Ecanul de incheiere: cand player-ul nu mai are spatiu de o piesa noua.

Specificatii tehnice
  •	Matricea de joc: un tablou bidimensional (ex.: int field[20][10]) pentru a stoca starea celulelor.
  •	O structură în care să stocăm piesa (tip, rotație, coordonatele pe tablă).
  •	Algoritm de verificare a coliziunii – o functie care verifica daca pozitia va fi libera.
  •	Game loop – o bucla care gestioneaza imput-ul si actualizeaza logica.

Interfata
  •	Zona de joc: un dreptunghi de 10x20 spatii/patratele.
  •	Panoul lateral cu scorul curent, nivelul si “Piesa urmatoare”.
  •	Mesajele de “Game over” si optiunea de restart.



  -	Scor/ high scor
  -	Fisier txt – high score 
  -	Veificare Scor nou dupa fiecare sesiune cu high scor
  -	Nu static! Viteza elementelor trebuie sa cresca pe parcurs
  -	EXTRA: animatie (evolueaza -> se schimba culorile) 
