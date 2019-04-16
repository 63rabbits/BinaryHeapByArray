#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "BinaryHeapByArray.h"

//////////////////////////////////////////////////
#define getParent(v) ((v - 1) / 2)
#define getLeftIndex(v) (v * 2 + 1)
#define getRightIndex(v) (v * 2 + 2)
#define max(a, b) (a > b ? a : b)

//////////////////////////////////////////////////
//  private
int findLeftmostEmptyNodeIndexOnBH(BH_t *B);
void autoExpandArrayOnBH(BH_t *B);
int findRightmostLeafIndexOnBH(BH_t *B);
void percolateOnBH(BH_t *B, int rootIndex);
void percolateUpOnBH(BH_t *B, int rootIndex);
void percolateDownOnBH(BH_t *B, int rootIndex);
void swapNodeOnBH(BH_t *B, int indexA, int indexB);
void *getElementOnBH(BH_t *B, int rootIndex);

//////////////////////////////////////////////////
//  public
BH_t *createBH(void) {
    BH_t *B = malloc(sizeof(BH_t));
    if (B == NULL) return NULL;
    B->capacity = BH_INITIAL_CAPACITY;
    B->array = calloc(B->capacity, sizeof(BHN_t**));
    if (B->array == NULL) {
        free(B);
        return NULL;
    }
    
    return B;
}

bool destroyBH(BH_t *B, BH_OPTION_e option) {
    // Block illegal parameters.
    if (B == NULL) return false;
    
    for (int i=0; i<B->capacity; i++) {
        if (B->array[i] != NULL) {
            if (option == BH_OPTION_WITH_ELEMENT) {
                if (B->array[i]->element != NULL) {
                    free(B->array[i]->element);
                }
            }
            free(B->array[i]);
        }
    }
    free(B->array);
    free(B);
    
    return true;
}

bool insertElementOnBH(BH_t *B, int priority, void *element) {
    int emptyIndex = -1;
    while (true) {
        emptyIndex = findLeftmostEmptyNodeIndexOnBH(B);
        if (emptyIndex >= 0) break;
        autoExpandArrayOnBH(B);
    }
    BHN_t *node = malloc(sizeof(BHN_t));
    if (node == NULL) return false;
    node->priority = priority;
    node->element = element;
    B->array[emptyIndex] = node;
    percolateOnBH(B, emptyIndex);
    return true;
}

void *pullMinPriorityElementOnBH(BH_t *B) {
    //    Consider a subtree rooted at the node to be deleted.
    //    Replace the deletion node with the leftmost leaf of the subtree.
    int rootIndex = 0;
    int rightmostIndex = findRightmostLeafIndexOnBH(B);
    if (rightmostIndex < 0) return NULL;
    
    void *element = getElementOnBH(B, rootIndex);
    free(B->array[rootIndex]);
    B->array[rootIndex] = NULL;
    if (rootIndex == rightmostIndex) return element;
    
    B->array[rootIndex] = B->array[rightmostIndex];
    B->array[rightmostIndex] = NULL;
    percolateOnBH(B, rootIndex);
    return element;
}

int getHeightBH(BH_t *B, int rootIndex) {
    int rightmost = -1;
    for (int i=B->capacity - 1; i>=0; i--) {
        if (B->array[i] != NULL) {
            rightmost = i;
            break;
        }
    }
    int height = 0;
    if (rightmost >= 0) {
        height = floor(log2(rightmost + 1));
    }
    
    return height;
}

//////////////////////////////////////////////////
//  private
void autoExpandArrayOnBH(BH_t *B) {
    int newSize = B->capacity << 1;
    B->array = realloc(B->array, sizeof(BHN_t**) * newSize);
    for (int i=B->capacity; i<newSize; i++) {
        B->array[i] = NULL;
    }
    B->capacity = newSize;
}

int findLeftmostEmptyNodeIndexOnBH(BH_t *B) {
    int leftmostEmptyIndex = findRightmostLeafIndexOnBH(B) + 1;
    if (leftmostEmptyIndex < B->capacity) return leftmostEmptyIndex;
    return -1;
}

int findRightmostLeafIndexOnBH(BH_t *B) {
    for (int i=B->capacity-1; i>=0; i--) {
        if (B->array[i] != NULL) return i;
    }
    return -1;
}

void percolateOnBH(BH_t *B, int rootIndex) {
    percolateUpOnBH(B, rootIndex);
    percolateDownOnBH(B, rootIndex);
}

void percolateUpOnBH(BH_t *B, int rootIndex) {
    int parentIndex = getParent(rootIndex);
    if (parentIndex == rootIndex) return;
    
    BHN_t *parent = B->array[parentIndex];
    BHN_t *root = B->array[rootIndex];
    if (parent->priority <= root->priority) return;
    swapNodeOnBH(B, parentIndex, rootIndex);
    return percolateUpOnBH(B, parentIndex);
}

void percolateDownOnBH(BH_t *B, int rootIndex) {
    int leftIndex = getLeftIndex(rootIndex);
    BHN_t *left = NULL;
    int leftKeyValue = INT_MAX;
    if ((leftIndex < B->capacity) &&
        (B->array[leftIndex] != NULL)) {
        left = B->array[leftIndex];
        leftKeyValue = left->priority;
    }
    
    int rightIndex = getRightIndex(rootIndex);
    BHN_t *right = NULL;
    int rightKeyValue = INT_MAX;
    if ((rightIndex < B->capacity) &&
        (B->array[rightIndex] != NULL)) {
        right = B->array[rightIndex];
        rightKeyValue = right->priority;
    }
    
    if ((left == NULL) && (right == NULL)) return;
    
    int minIndex = leftKeyValue <= rightKeyValue ? leftIndex : rightIndex;
    if (B->array[minIndex]->priority > B->array[rootIndex]->priority) return;
    swapNodeOnBH(B, rootIndex, minIndex);
    return percolateDownOnBH(B, minIndex);
}

void swapNodeOnBH(BH_t *B, int indexA, int indexB) {
    BHN_t *temp = B->array[indexA];
    B->array[indexA] = B->array[indexB];
    B->array[indexB] = temp;
}

void *getElementOnBH(BH_t *B, int rootIndex) {
    // Block illegal parameters.
    if (B == NULL) return NULL;
    
    return B->array[rootIndex]->element;
}

//////////////////////////////////////////////////
//  debug
void viewBH(BH_t *B, BH_OPTION_e option) {
    int root = 0;
    int wordWidth = 4;
    if (option == BH_OPTION_VIEW_CHAR) {
        wordWidth = 2;
    }
    int height = getHeightBH(B, root);
    
    // veiw Binary Tree.
    int numOfNodes = (int)pow(2, height);
    int width = wordWidth * numOfNodes;
    char view[height+1][width+1];
    for (int i=0; i<=height; i++) {
        view[i][0] = '\0';
    }
    
    char format10[32] = "";
    char format11[32] = "";
    char format20[32] = "";
    char padding[32] = "";
    for (int i=0; i<wordWidth; i++) {
        strcat(padding, " ");
    }
    //    padding[wordWidth-1] = '_';
    sprintf(format10, "%%s%%%dd", wordWidth);
    sprintf(format11, "%%s%%%dc", wordWidth);
    sprintf(format20, "%%s%s", padding);
    
    int leftmostIndex = pow(2, height) - 1;
    int rightmostIndex = pow(2, height+1) - 2;
    for (int i=height; i>=0; i--) {
        int numOfPadding = (width - (wordWidth * numOfNodes))/numOfNodes;
        for (int j=0; (i!=height) && (j<numOfPadding/2); j++) {
            strcat(view[i], " ");
        }
        for (int j=leftmostIndex; j<=rightmostIndex; j++) {
            if ((j < B->capacity) &&
                (B->array[j] != NULL)) {
                if (option == BH_OPTION_VIEW_INT) {
                    sprintf(view[i], format10, view[i], B->array[j]->priority);
                }
                else {
                    sprintf(view[i], format11, view[i], (char)B->array[j]->priority);
                }
            }
            else {
                sprintf(view[i], format20, view[i]);
            }
            for (int k=0; (i!=height) && (k<numOfPadding); k++) {
                strcat(view[i], " ");
                if (strlen(view[i]) >= width - 1) break;
            }
        }
        leftmostIndex = getParent(leftmostIndex);
        rightmostIndex = getParent(rightmostIndex);
        numOfNodes = numOfNodes >> 1;
    }
    for (int i=0; i<=height; i++) {
        printf("\nLevel #%02d %s\n", i, view[i]);
    }
    printf("\n");
}

