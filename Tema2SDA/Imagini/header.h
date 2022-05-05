#ifndef HEADER_H_
#define HEADER_H_

#include <inttypes.h>

typedef struct pixel {

    unsigned char red, green, blue;
} pixel;

typedef struct Quadtree {

    unsigned char red, green, blue;
    int start_x;
    int start_y;
    int finish_x;
    int finish_y;
    int nr_node;
    int leaf;
    struct Quadtree *TL, *TR, *BL, *BR;
} Quadtree;

typedef struct QuadtreeNode {

    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left , top_right;
    int32_t bottom_left , bottom_right;
} __attribute__((packed)) QuadtreeNode;

void insert_Qtree(Quadtree** root, pixel** poza, int width, int height, int *nodes, int *leaf, int threshold);

int height (Quadtree * root);

void PrintLVLOreder(Quadtree* root, pixel** poza, QuadtreeNode *arr, int* count);

void PrintCurrentLVL(Quadtree* root, pixel** poza, int lvl, QuadtreeNode **arr, int* count);

void PrintDescendentOreder(Quadtree* root, pixel** poza, QuadtreeNode *arr);

void PrintDescendentLVL(Quadtree* root, pixel** poza, int lvl, QuadtreeNode **arr);

void dealloc(Quadtree** root);

void insert_QtreeArr(Quadtree** root, QuadtreeNode* arr, int width, int height, int pozitie);

void printCLTree(Quadtree* root, pixel** poza, int level);

void PrintTree(Quadtree* root, pixel** poza);

void insert_matrix(Quadtree** root, pixel** poza);

void insert_QtreeArrH(Quadtree** root, QuadtreeNode* arr, int width, int height, int pozitie);

void insert_QtreeArrV(Quadtree** root, QuadtreeNode* arr, int width, int height, int pozitie);

#endif