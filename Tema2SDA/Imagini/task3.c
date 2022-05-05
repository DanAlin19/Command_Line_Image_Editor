#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

void insert_QtreeArrH(Quadtree** root, QuadtreeNode* arr, int width, int height, int pozitie) {

    if( (*root) == NULL ) {
        // adaug in radacina
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
            // adauag in nodul de top_left coordonatele de la top_right
            (*root)->TL = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* TopL = (*root)->TL;
            TopL->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            TopL->finish_x = (*root)->finish_x;
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
            insert_QtreeArrH( &TopL, arr, width, height, TopL->nr_node );
        }

        if(arr[pozitie].top_right != -1) {
            // adauag in nodul de top_right coordonatele de la top_left
            (*root)->TR = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* TopR = (*root)->TR;
            TopR->start_x = (*root)->start_x;
            TopR->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
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
            insert_QtreeArrH( &TopR, arr, width, height, TopR->nr_node);
        }

        if(arr[pozitie].bottom_right != -1) {
            // adaug in nodul de bottom_right coordonatele de la bottom_left
            (*root)->BR = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* BottomR = (*root)->BR;
            BottomR->start_x = (*root)->start_x;
            BottomR->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
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
            insert_QtreeArrH( &BottomR, arr, width, height, BottomR->nr_node);
        }
    
        if(arr[pozitie].bottom_left != -1) {
            // adaug in nodul de bottom_left coordonatele de la bottom_right
            (*root)->BL = (Quadtree *)malloc(sizeof(Quadtree));
            Quadtree* BottomL = (*root)->BL;
            BottomL->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            BottomL->finish_x = (*root)->finish_x;
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
            insert_QtreeArrH( &BottomL, arr, width, height, BottomL->nr_node); 
        }
        else 
            (*root)->leaf = 1;
        
    }    
}

void insert_QtreeArrV(Quadtree** root, QuadtreeNode* arr, int width, int height, int pozitie) {

    if( (*root) == NULL ) {
        // adaug in radacina
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
            // adaug in nodul de top_left coordonatele de la bottom_left
            (*root)->TL = (Quadtree *)malloc(sizeof(Quadtree));
            (*root)->TL->start_x = (*root)->start_x;
            (*root)->TL->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
            (*root)->TL->start_y = ((*root)->finish_y - (*root)->start_y) / 2 + 1 + (*root)->start_y;
            (*root)->TL->finish_y = (*root)->finish_y;
            (*root)->TL->nr_node = arr[pozitie].top_left;
            (*root)->TL->leaf = 0;
            (*root)->TL->red = arr[(*root)->TL->nr_node].red;
            (*root)->TL->green = arr[(*root)->TL->nr_node].green;
            (*root)->TL->blue = arr[(*root)->TL->nr_node].blue;
            (*root)->TL->TL = NULL;
            (*root)->TL->TR = NULL;
            (*root)->TL->BR = NULL;
            (*root)->TL->BL = NULL;
            insert_QtreeArrV( &(*root)->TL, arr, width, height, (*root)->TL->nr_node );
        }

        if(arr[pozitie].top_right != -1) {
            // adaug in nodul de top_right coordonatele de la bottom_right
            (*root)->TR = (Quadtree *)malloc(sizeof(Quadtree));
            (*root)->TR->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            (*root)->TR->finish_x = (*root)->finish_x;
            (*root)->TR->start_y = ((*root)->finish_y - (*root)->start_y) / 2 + 1 + (*root)->start_y;
            (*root)->TR->finish_y = (*root)->finish_y;
            (*root)->TR->nr_node = arr[pozitie].top_right;
            (*root)->TR->leaf = 0;
            (*root)->TR->red = arr[(*root)->TR->nr_node].red;
            (*root)->TR->green = arr[(*root)->TR->nr_node].green;
            (*root)->TR->blue = arr[(*root)->TR->nr_node].blue;
            (*root)->TR->TL = NULL;
            (*root)->TR->TR = NULL;
            (*root)->TR->BR = NULL;
            (*root)->TR->BL = NULL;
            insert_QtreeArrV( &(*root)->TR, arr, width, height, (*root)->TR->nr_node);
        }

        if(arr[pozitie].bottom_right != -1) {
            // adaug in nodul de bottom_right coordonatele de la top_right
            (*root)->BR = (Quadtree *)malloc(sizeof(Quadtree));
            (*root)->BR->start_x = ((*root)->finish_x - (*root)->start_x) / 2 + 1 + (*root)->start_x;
            (*root)->BR->finish_x = (*root)->finish_x;
            (*root)->BR->start_y = (*root)->start_y;
            (*root)->BR->finish_y = ((*root)->finish_y - (*root)->start_y) / 2 + (*root)->start_y;
            (*root)->BR->nr_node = arr[pozitie].bottom_right;
            (*root)->BR->leaf = 0;
            (*root)->BR->red = arr[(*root)->BR->nr_node].red;
            (*root)->BR->green = arr[(*root)->BR->nr_node].green;
            (*root)->BR->blue = arr[(*root)->BR->nr_node].blue;
            (*root)->BR->TL = NULL;
            (*root)->BR->TR = NULL;
            (*root)->BR->BR = NULL;
            (*root)->BR->BL = NULL;    
            insert_QtreeArrV( &(*root)->BR, arr, width, height, (*root)->BR->nr_node);
        }
    
        if(arr[pozitie].bottom_left != -1) {
            // adaug in nodul de bottom_left coordonatele de la top_left
            (*root)->BL = (Quadtree *)malloc(sizeof(Quadtree));
            (*root)->BL->start_x = (*root)->start_x;
            (*root)->BL->finish_x = ((*root)->finish_x - (*root)->start_x) / 2 + (*root)->start_x;
            (*root)->BL->start_y = (*root)->start_y;
            (*root)->BL->finish_y = ((*root)->finish_y - (*root)->start_y) / 2 + (*root)->start_y;
            (*root)->BL->nr_node = arr[pozitie].bottom_left;
            (*root)->BL->leaf = 0;
            (*root)->BL->red = arr[(*root)->BL->nr_node].red;
            (*root)->BL->green = arr[(*root)->BL->nr_node].green;
            (*root)->BL->blue = arr[(*root)->BL->nr_node].blue;
            (*root)->BL->TL = NULL;
            (*root)->BL->TR = NULL;
            (*root)->BL->BR = NULL;
            (*root)->BL->BL = NULL;
            insert_QtreeArrV( &(*root)->BL, arr, width, height, (*root)->BL->nr_node); 
        }
        else 
            (*root)->leaf = 1;
        
    }    
}