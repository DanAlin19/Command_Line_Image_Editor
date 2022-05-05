#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

void insert_QtreeArr(Quadtree** root, QuadtreeNode* arr, int width, int height, int pozitie) {

    if( (*root) == NULL ) {
        // adaug in root
        (*root) = (Quadtree *)malloc(sizeof(Quadtree));
        height -= 1;
        width -= 1;
        (*root)->start_x = 0;
        (*root)->finish_x = height;
        (*root)->start_y = 0;
        (*root)->finish_y = width;
        (*root)->red = arr[0].red;
        (*root)->green = arr[0].green;
        (*root)->blue = arr[0].blue;
        (*root)->nr_node = 0;
        (*root)->leaf = 0;
        (*root)->TL= NULL;
        (*root)->TR = NULL;
        (*root)->BR = NULL;
        (*root)->BL = NULL;
        return;
    }

    else {

        if(arr[pozitie].top_left != -1) {
            // daca nu e frunza adaug in nodul top_left
            (*root)->TL = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* TopL = (*root)->TL;
            TopL->start_x = (*root)->start_x;
            TopL->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
            TopL->start_y = (*root)->start_y;
            TopL->finish_y = ((*root)->finish_y - (*root)->start_y) / 2 + (*root)->start_y;
            TopL->nr_node = arr[pozitie].top_left;
            TopL->leaf = 0;
            TopL->red = arr[TopL->nr_node].red;
            TopL->green = arr[TopL->nr_node].green;
            TopL->blue = arr[TopL->nr_node].blue;
            TopL->TL = NULL;
            TopL->TR = NULL;
            TopL->BR = NULL;
            TopL->BL = NULL;
            insert_QtreeArr( &TopL, arr, width, height, TopL->nr_node );
        }

        if(arr[pozitie].top_right != -1) {
            // daca nu e frunza adaug in nodul top_right
            (*root)->TR = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* TopR = (*root)->TR;
            TopR->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            TopR->finish_x = (*root)->finish_x;
            TopR->start_y = (*root)->start_y;
            TopR->finish_y = ((*root)->finish_y - (*root)->start_y) / 2 + (*root)->start_y;
            TopR->nr_node = arr[pozitie].top_right;
            TopR->leaf = 0;
            TopR->red = arr[TopR->nr_node].red;
            TopR->green = arr[TopR->nr_node].green;
            TopR->blue = arr[TopR->nr_node].blue;
            TopR->TL = NULL;
            TopR->TR = NULL;
            TopR->BR = NULL;
            TopR->BL = NULL;
            insert_QtreeArr( &TopR, arr, width, height, TopR->nr_node);
        }

        if(arr[pozitie].bottom_right != -1) {
            // daca nu e frunza adaug in nodul bottom_right
            (*root)->BR = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* BottomR = (*root)->BR;
            BottomR->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            BottomR->finish_x = (*root)->finish_x;
            BottomR->start_y = ((*root)->finish_y - (*root)->start_y) / 2 + 1 + (*root)->start_y;
            BottomR->finish_y = (*root)->finish_y;
            BottomR->nr_node = arr[pozitie].bottom_right;
            BottomR->leaf = 0;
            BottomR->red = arr[BottomR->nr_node].red;
            BottomR->green = arr[BottomR->nr_node].green;
            BottomR->blue = arr[BottomR->nr_node].blue;
            BottomR->TL = NULL;
            BottomR->TR = NULL;
            BottomR->BR = NULL;
            BottomR->BL = NULL;    
            insert_QtreeArr( &BottomR, arr, width, height, BottomR->nr_node);
        }
    
        if(arr[pozitie].bottom_left != -1) {
            // daca nu e frunza adaug in nodul bottom_left
            (*root)->BL = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* BottomL = (*root)->BL;
            BottomL->start_x = (*root)->start_x;
            BottomL->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
            BottomL->start_y = ((*root)->finish_y - (*root)->start_y) / 2 + 1 + (*root)->start_y;
            BottomL->finish_y = (*root)->finish_y;
            BottomL->nr_node = arr[pozitie].bottom_left;
            BottomL->leaf = 0;
            BottomL->red = arr[BottomL->nr_node].red;
            BottomL->green = arr[BottomL->nr_node].green;
            BottomL->blue = arr[BottomL->nr_node].blue;
            BottomL->TL = NULL;
            BottomL->TR = NULL;
            BottomL->BR = NULL;
            BottomL->BL = NULL;
            insert_QtreeArr( &BottomL, arr, width, height, BottomL->nr_node); 
        }
        else 
            (*root)->leaf = 1;
        
    }    
}

void PrintTree(Quadtree* root, pixel** poza) {

    int lvl = height(root);
    for(int i = 1; i <= lvl; i++) {
        printCLTree(root, poza, i);
    }
}

void printCLTree(Quadtree* root, pixel** poza, int level) {
    if (root == NULL)
        return;
    if (level == 1) {
        insert_matrix(&root, poza);
    }   
    else if (level > 1) {
        printCLTree(root->TL, poza, level - 1);
        printCLTree(root->TR, poza, level - 1);
        printCLTree(root->BR, poza, level - 1);
        printCLTree(root->BL, poza, level - 1);
    }
}

void insert_matrix(Quadtree** root, pixel** poza) {
    // colorez matricea cu culorile medii
    for(int i = (*root)->start_y; i <= (*root)->finish_y ; i++)
        for(int j = (*root)->start_x; j <= (*root)->finish_x; j++) {
            (*(poza + i) + j)->red = (*root)->red;
            (*(poza + i) + j)->green = (*root)->green;
            (*(poza + i) + j)->blue = (*root)->blue;
        }
}
