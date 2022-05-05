    In functia main daca in linia de comanda gasesc -c => ca trebuie sa  fac 
compresie citesc primele trei linii din fisier, prima linie contine formatul
pozei de tip ppm a doua linie contine lungimea si latimea pozei si ultima
linie din cele 3 contine rgb_component. Aloc dinamic o matrice de pixeli in
care o sa stochez poza. Inserez in arbore cu functia "insert_Qtree". Adaug
in vectorul arr "PrintLVLOreder" si "PrintDescendentOrder". Scriu in fisierul
binar numarul de frunze si numarul de noduri din arbore apoi adaug vectorul si
la final eliberez memoria.
    Daca in linia de comanda gasesc -d => ca trebuie sa pun datele in vectorul
arr, cu ajutorul functiti "insert_QtreeArr" adaug in arbore cuaternar vectorul.
Adaug in matrice nodurile frunza ale arborelui cuaternar si adaug in fisierul 
de iesire tipul pozei ppm, lungimea si latimea pozei si rgb_component. Eliberez
memoria alocata.
    Daca in linia de comanda gasesc -m => ca trebuie sa rotesc imaginea. 
Acesta este o combinare intre cele doua task-uri precedente singura 
modificare este ca la -h (top_left este top_right si bottom_left este 
bottom_right si vice-versa) si la -v (top_left este bottom_left si top_right 
este bottom_right si vice-versa).
    
    insert_Qtree adaug in radacina coordonatele si leaf este = 0 daca nodul nu 
este frunza si nr_node o sa reprezinte numarul nodului cu o parcurgere BFS si 
incrementez nodes. Dupa ce am pus in radacina calculez media culorilor (rosu, 
verde, albastru) pe matricea de la coordonatele nodului si calculez mean cu 
formula din pdf. Daca pragul este mai mic decat mean adaug in fii sai: TopL, 
TopR, BottomR, BottomL. Altfel nodul respectiv este frunza incrementez 
variabila leaf care imi retine numarul de frunze si (*root)->leaf = 1 => nodul
este frunza.

    height daca root = NULL => arborele nu exista si inaltimea este 0, altfel 
ma duc recursiv din fiu in fiu si calculez maximul dintre ei si la final 
adaug 1 reprezentand radacina.

    PrintLVLOreder parcurge arborele pe nivele si executa PrintCurrentLVL(BFS)

    PrintCurrentLVL daca nivelul este 1 calculez media culorilor si o bag in 
elementele vectorului si size-ul este dimeniunea matricei.

    Mai fac o parcurgere pentru a adauga si numarul fiilor.

    insert_QtreeArr este la fel ca insert_Qtree doar ca aicea dimensiunile le 
iau din vectorul arr si la fel si culoarea medie.

    insert_matrix imi coloreaza matricea cu culoarea medie.

    Fac din nou o parcurgere BFS si adaug in matrice.in functia printCLTree

    insert_QtreeArrH aduag in arborele cuaternar la fel ca in functia
insert_Qtree singura diferenta este ca nodului TopL ii introduc coordonatele 
nodului TopR cu acelasi tata si nodului BottomR ii introduc coordonatele 
nodului BottomL cu acelasi tata si vice-versa.

    insert_QtreeArrV aduag in arborele cuaternar la fel ca in functia
insert_Qtree singura diferenta este ca nodului TopL ii introduc coordonatele 
nodului BottomL cu acelasi tata si nodului TopR ii introduc coordonatele 
nodului BottomR cu acelasi tata si vice-versa.
