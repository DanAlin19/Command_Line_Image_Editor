#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

void insert_Qtree(Quadtree** root, pixel** poza, int width, int height, int *nodes, int *leaf, int threshold) {
    

    if( (*root) == NULL ) {

        // adaug in radacina coordonatele 
        (*root) = (Quadtree *)malloc(sizeof(Quadtree));
        height -= 1;
        width -= 1;
        (*root)->start_x = 0;
        (*root)->finish_x = height;
        (*root)->start_y = 0;
        (*root)->finish_y = width;
        (*root)->leaf = 0;
        (*root)->nr_node = 0;

        // contorizez numarul de noduri
        *nodes += 1;
        (*root)->TL= NULL;
        (*root)->TR = NULL;
        (*root)->BR = NULL;
        (*root)->BL = NULL;
        return;
    }

    else {
        
        // calculez culoarea medie 
        long long int mean = 0;
        int rosu = 0, verde = 0, albastru = 0;
        for(int i = (*root)->start_y; i <= (*root)->finish_y ; i++)
            for(int j = (*root)->start_x; j <= (*root)->finish_x; j++) {
                rosu += (*(poza + i) + j)->red;
                verde += (*(poza + i) + j)->green;
                albastru += (*(poza + i) + j)->blue;
            }
        
        rosu /= (((*root)->finish_x - (*root)->start_x + 1) * ((*root)->finish_y - (*root)->start_y + 1));
        verde /= (((*root)->finish_x - (*root)->start_x + 1) * ((*root)->finish_y - (*root)->start_y + 1));
        albastru /= (((*root)->finish_x - (*root)->start_x + 1) * ((*root)->finish_y - (*root)->start_y + 1));
        
        // calculez mean 
        for(int i = (*root)->start_y; i <= (*root)->finish_y ; i++)
            for(int j = (*root)->start_x; j <= (*root)->finish_x; j++) {
                
                mean += (rosu - (int)(*(poza + i) + j)->red) * (rosu - (int)(*(poza + i) + j)->red);
                mean += (verde - (int)(*(poza + i) + j)->green) * (verde - (int)(*(poza + i) + j)->green);
                mean += (albastru - (int)(*(poza + i) + j)->blue) * (albastru - (int)(*(poza + i) + j)->blue);
            }

        mean /= (3 * ((*root)->finish_x - (*root)->start_x + 1) * ((*root)->finish_y - (*root)->start_y + 1));
        
        if ( threshold < mean ) {

            // merg in fiul top_left si calculez coordonatele matricii
            (*root)->TL = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* TopL = (*root)->TL;
            *nodes += 1;
            TopL->start_x = (*root)->start_x;
            TopL->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
            TopL->start_y = (*root)->start_y;
            TopL->finish_y = ((*root)->finish_y - (*root)->start_y) / 2 + (*root)->start_y;
            (*root)->nr_node = 0;
            TopL->leaf = 0;
            TopL->TL = NULL;
            TopL->TR = NULL;
            TopL->BR = NULL;
            TopL->BL = NULL;
            insert_Qtree( &TopL, poza, width, height, nodes, leaf, threshold);
           
            // merg in fiul top_right si calculez coordonatele matricii
            (*root)->TR = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* TopR = (*root)->TR;
            *nodes += 1;
            TopR->start_x =  ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            TopR->finish_x = (*root)->finish_x;
            TopR->start_y = (*root)->start_y;
            TopR->finish_y = ((*root)->finish_y - (*root)->start_y) / 2 + (*root)->start_y;
            (*root)->nr_node = 0;
            TopR->leaf = 0;
            TopR->TL = NULL;
            TopR->TR = NULL;
            TopR->BR = NULL;
            TopR->BL = NULL;
            insert_Qtree( &(*root)->TR, poza, width, height, nodes, leaf, threshold);

            // merg in fiul bottom_right si calculez coordonatele matricii
            (*root)->BR = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* BottomR = (*root)->BR;
            *nodes += 1;
            BottomR->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            BottomR->finish_x = (*root)->finish_x;
            BottomR->start_y = ((*root)->finish_y - (*root)->start_y) / 2 + 1 + (*root)->start_y;
            BottomR->finish_y = (*root)->finish_y;
            (*root)->nr_node = 0;
            BottomR->leaf = 0;
            BottomR->TL = NULL;
            BottomR->TR = NULL;
            BottomR->BR = NULL;
            BottomR->BL = NULL;    
            insert_Qtree( &BottomR, poza, width, height, nodes, leaf, threshold);

            // merg in fiul bottom_left si calculez coordonatele matricii     
            (*root)->BL = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* BottomL = (*root)->BL;
            *nodes += 1;
            BottomL->start_x = (*root)->start_x;
            BottomL->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
            BottomL->start_y = ((*root)->finish_y - (*root)->start_y) / 2 + 1 + (*root)->start_y;
            BottomL->finish_y = (*root)->finish_y;
            (*root)->nr_node = 0;
            BottomL->leaf = 0;
            BottomL->TL = NULL;
            BottomL->TR = NULL;
            BottomL->BR = NULL;
            BottomL->BL = NULL;
            insert_Qtree( &BottomL, poza, width, height, nodes, leaf, threshold);
        
        }
       
        else {
            // daca intra pe else => este frunza si ii dau lui (*root)->frunzei valoarea 1
            *leaf += 1;
            (*root)->leaf = 1;
            return;
        }    
    }    
}

int height (Quadtree* root) {

    // calculez adancimea arborelui
    if(root == NULL)
        return 0;

    else {      

        int BRheight = height(root->BR);
        int BLheight = height(root->BL);
        int TLheight = height(root->TL);
        int TRheight = height(root->TR);

        // calculez maximul
        if(BRheight < TRheight)
            BRheight = TRheight;
        if(BRheight < TLheight)
            BRheight = TLheight;
        if(BRheight < BLheight)
            BRheight = BLheight;

        return BRheight + 1;
    }
}

void PrintLVLOreder(Quadtree* root, pixel** poza, QuadtreeNode *arr, int* count) {


    int lvl = height(root);
    for(int i = 1; i <= lvl; i++) 
        PrintCurrentLVL(root, poza, i, &arr, count);      
} 

void PrintCurrentLVL(Quadtree* root, pixel** poza, int lvl, QuadtreeNode **arr, int* count) {

    if(root == NULL)
        return;

    if(lvl == 1) {
        
        //calculez media de culoare de la fiecare nod al arborelui
        int rosu = 0, verde = 0, albastru = 0;
        for(int i = (*root).start_y; i <= (*root).finish_y ; i++)
            for(int j = (*root).start_x; j <= (*root).finish_x; j++) {
                rosu += (*(poza + i) + j)->red;
                verde += (*(poza + i) + j)->green;
                albastru += (*(poza + i) + j)->blue;
            }

        int size = ((*root).finish_x - (*root).start_x + 1) * ((*root).finish_y - (*root).start_y + 1);
        rosu /= ((*root).finish_x - (*root).start_x + 1) * ((*root).finish_y - (*root).start_y + 1);
        verde /= ((*root).finish_x - (*root).start_x + 1) * ((*root).finish_y - (*root).start_y + 1);
        albastru /= ((*root).finish_x - (*root).start_x + 1) * ((*root).finish_y - (*root).start_y + 1);

        (*root).nr_node = *count;
        // adaug in vector
        (*arr + (*root).nr_node)->red = rosu;
        (*arr + (*root).nr_node)->green = verde;
        (*arr + (*root).nr_node)->blue = albastru;
        (*arr + (*root).nr_node)->area = size;

        *count += 1;
    }
    else if(lvl > 1) {

        PrintCurrentLVL(root->TL, poza, lvl - 1, arr, count);
        PrintCurrentLVL(root->TR, poza, lvl - 1, arr, count);
        PrintCurrentLVL(root->BR, poza, lvl - 1, arr, count);
        PrintCurrentLVL(root->BL, poza, lvl - 1, arr, count);
    }
}

void PrintDescendentOreder(Quadtree* root, pixel** poza, QuadtreeNode *arr) {

    int lvl = height(root);
    for(int i = 1; i <= lvl; i++) 
        PrintDescendentLVL(root, poza, i, &arr);        
} 

void PrintDescendentLVL(Quadtree* root, pixel** poza, int lvl, QuadtreeNode **arr) {

    if(root == NULL)
        return;

    if(lvl == 1) {

        if((*root).leaf == 1) {
            // adaug in vectorul de structuri
            (*arr + (*root).nr_node)->top_left = -1;
            (*arr + (*root).nr_node)->top_right = -1;
            (*arr + (*root).nr_node)->bottom_left = -1;
            (*arr + (*root).nr_node)->bottom_right = -1;
        }
        else {
            (*arr + (*root).nr_node)->top_left = (*root).TL->nr_node;
            (*arr + (*root).nr_node)->top_right = (*root).TR->nr_node;
            (*arr + (*root).nr_node)->bottom_left = (*root).BL->nr_node;
            (*arr + (*root).nr_node)->bottom_right = (*root).BR->nr_node;
        }

    }
    else if(lvl > 1) {

        PrintDescendentLVL(root->TL, poza, lvl - 1, arr);
        PrintDescendentLVL(root->TR, poza, lvl - 1, arr);
        PrintDescendentLVL(root->BR, poza, lvl - 1, arr);
        PrintDescendentLVL(root->BL, poza, lvl - 1, arr);
    }
}

void dealloc(Quadtree** root) {

    if((*root) == NULL)
        return;
    dealloc(&(*root)->TL);
    dealloc(&(*root)->TR);
    dealloc(&(*root)->BR);
    dealloc(&(*root)->BL);
    free(*root);
    *root = NULL;
}