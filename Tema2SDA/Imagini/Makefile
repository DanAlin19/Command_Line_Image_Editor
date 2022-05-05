# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c11
 
# Regula de compilare
all: build

build: quadtree.c
	$(CC) task1.c task2.c task3.c quadtree.c -o quadtree $(CFLAGS) 

# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f quadtree
	rm -f *.out