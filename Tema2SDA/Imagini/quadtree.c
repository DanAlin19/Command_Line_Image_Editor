#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int main(int argc, char *argv[]) {

    // daca in linia de comanda gasesc "-c" atunci trebuie sa fac compress
    if (strcmp(argv[argc - 4], "-c") == 0) {
        
        char *buff;
        buff = (char *)malloc(16 * sizeof(char));

        // factor este indicele unde opresc partitionarea pozei
        int factor = atoi(argv[argc - 3]);
        FILE *fin;
        fin = fopen(argv[argc - 2], "rb");

        if (!fin) {
            exit(1);
        }

        if( !fgets(buff, sizeof(buff), fin) ) {
            exit(1);
        }
        // buff retine tipul imaginii ppm
        if (buff[0] != 'P' || buff[1] != '6') {
            exit(1);
        }
        // x retine height si y retine width
        int x, y, rgb_component;
        if (fscanf(fin, "%d %d", &x, &y) != 2) {
            exit(1);
        }
        
        if (fscanf(fin, "%d", &rgb_component) != 1) {
            exit(1);
        }

        while (fgetc(fin) != '\n') ;

        // aloc o matrice in care voi retine pixelii imaginii
        pixel **data = (pixel**)malloc(x * sizeof(pixel*));
        for(int i = 0; i < x; i++)
            data[i] = (pixel*)malloc(y * sizeof(pixel));

        // adaug in matrice
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++) 
                fread( *(data + i) + j, sizeof(pixel), 1, fin);

        // poza este arborele cuaternar
        Quadtree* poza = NULL;

        int node = 0;
        int leafs = 0;
        int count = 0;
        
        // inserez in arbore
        insert_Qtree(&poza, data, x, y, &node, &leafs, factor);
        insert_Qtree(&poza, data, x, y, &node, &leafs, factor);

        QuadtreeNode *arr = (QuadtreeNode*)malloc(node * sizeof(QuadtreeNode));
        FILE * fout;
        fout = fopen(argv[argc - 1], "wb");

        // fac BFS si adaug in vector
        PrintLVLOreder(poza, data, arr, &count);
        PrintDescendentOreder(poza, data, arr);

        // adaug in fisier numarul de frunze si noduri si vectorul format
        fwrite(&leafs, sizeof(node), 1, fout);
        fwrite(&node, sizeof(node), 1, fout);

        for(int i = 0; i < node; i++) {
            fwrite(&arr[i], sizeof(QuadtreeNode), 1, fout);
        } 
        
        // eliberarez memoria si inchid fisierele
        for(int i = 0; i < x; i++)
            free(data[i]);

        dealloc(&poza);
        free(poza);
        free(data);
        free(arr);
        free(buff);
        fclose(fin);
        fclose(fout);
    }

    // daca in linia de comanda gasesc "-d" atunci trebuie sa fac decompress
    if (strcmp(argv[argc - 3], "-d") == 0) {
        FILE* fin;
        fin = fopen(argv[argc - 2], "rb");
        
        if (!fin) {
            exit(1);
        }

        Quadtree* poza = NULL;

        
        int leaf, node;
        fread(&leaf, sizeof(int), 1, fin);
        fread(&node, sizeof(int), 1, fin);
        QuadtreeNode *arr = (QuadtreeNode*)malloc(node * sizeof(QuadtreeNode));
        // introduc datele in vector arr
        for(int i = 0; i < node; i++) 
            fread(&arr[i], sizeof(QuadtreeNode), 1, fin);

        int x = sqrt(arr[0].area);
        int y = sqrt(arr[0].area);
        
        // adaug in arbore
        insert_QtreeArr(&poza, arr, x, y, 0); 
        insert_QtreeArr(&poza, arr, x, y, 0);


        pixel **data = (pixel**)malloc(x * sizeof(pixel*));
        for(int i = 0; i < x; i++)
            data[i] = (pixel*)malloc(y * sizeof(pixel));

        FILE* fout;
        fout = fopen(argv[argc - 1], "wb");
        fprintf(fout,"P6\n");
        fprintf(fout,"%d %d\n", x, y);
        fprintf(fout,"255\n");
        // adaug in matricea data datele din arborele poza
        PrintTree(poza, data);

        // pun datele in fisier pentru a recrea poza
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++) 
                fwrite( *(data + i) + j, sizeof(pixel), 1, fout);

        for(int i = 0; i < x; i++)
            free(data[i]);
        dealloc(&poza);
        free(poza);
        free(data);
        free(arr);
        fclose(fin);
        fclose(fout);
    }
    // daca in linia de comanda gasesc "-m" atunci trebuie sa rotesc poza
    // in functie de urmatorul argument
    if (strcmp(argv[ 1 ], "-m") == 0) {
        
        char *buff;
        buff = (char *)malloc(16 * sizeof(char));

        // factorl unde se va opri impartirea pozei
        int factor = atoi(argv[ 3 ]);

        // tipul de rotire vertical sau orizontal
        char rotire = *argv [ 2 ];
        FILE *fin;
        fin = fopen(argv[ 4 ], "rb");

        if (!fin) {
            exit(1);
        }

        if( !fgets(buff, sizeof(buff), fin) ) {
            exit(1);
        }

        if (buff[0] != 'P' || buff[1] != '6') {

            exit(1);
        }

        int x, y, rgb_component;
        if (fscanf(fin, "%d %d", &x, &y) != 2) {
            exit(1);
        }

        if (fscanf(fin, "%d", &rgb_component) != 1) {
            exit(1);
        }

        while (fgetc(fin) != '\n') ;
 
        pixel **data = (pixel**)malloc(x * sizeof(pixel*));
        for(int i = 0; i < x; i++)
            data[i] = (pixel*)malloc(y * sizeof(pixel));

        // adaug pixelii de la poza intr-o matrice
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++) 
                fread( *(data + i) + j, sizeof(pixel), 1, fin);

        Quadtree* poza = NULL;

        int node = 0;
        int leafs = 0;
        int count = 0;

        // adaug in arborele cuaternar
        insert_Qtree(&poza, data, x, y, &node, &leafs, factor);
        insert_Qtree(&poza, data, x, y, &node, &leafs, factor);

        QuadtreeNode *arr = (QuadtreeNode*)malloc(node * sizeof(QuadtreeNode));
        FILE * fout;
        fout = fopen(argv[ 5 ], "wb");

        // fac BFS si adaug in vector
        PrintLVLOreder(poza, data, arr, &count);
        PrintDescendentOreder(poza, data, arr);
        
        //eliberez o parte din memorie
        for(int i = 0; i < x; i++)
            free(data[i]);

        dealloc(&poza);
        free(poza);
        free(data);

        Quadtree* poza_actual = NULL;

        // daca rotire e orizontala  
        if(rotire == 'h') {
            // adaug in arbore
            insert_QtreeArrH(&poza_actual, arr, x, y, 0); 
            insert_QtreeArrH(&poza_actual, arr, x, y, 0);
        }
        // daca rotire e verticala
        if(rotire == 'v') {
            // adaug in arbore
            insert_QtreeArrV(&poza_actual, arr, x, y, 0); 
            insert_QtreeArrV(&poza_actual, arr, x, y, 0);
        }

        pixel **new = (pixel**)malloc(x * sizeof(pixel*));
        for(int i = 0; i < x; i++)
            new[i] = (pixel*)malloc(y * sizeof(pixel));


        fprintf(fout,"P6\n");
        fprintf(fout,"%d %d\n", x, y);
        fprintf(fout,"255\n");
        // adaug in matricea new datele din arborele poza_actual
        PrintTree(poza_actual, new);

        // adaug in fisier 
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++) 
                fwrite( *(new + i) + j, sizeof(pixel), 1, fout);

        for(int i = 0; i < x; i++)
            free(new[i]);
        dealloc(&poza_actual);
        free(poza_actual);
        free(new);
        free(arr);
        free(buff);
        fclose(fin);
        fclose(fout);
    }
    return 0;
}