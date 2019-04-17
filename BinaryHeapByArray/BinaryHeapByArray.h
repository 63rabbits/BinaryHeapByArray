#ifndef BinaryHeapByArray_h
#define BinaryHeapByArray_h

//////////////////////////////////////////////////
#define BH_INITIAL_CAPACITY 16;

typedef enum BHOption {
    BH_OPTION_NONE,
    BH_OPTION_WITH_ELEMENT,
    
    BH_OPTION_VIEW_INT = 20,
    BH_OPTION_VIEW_CHAR
} BH_OPTION_e;

typedef struct BinaryHeap_Node {
    int priority;
    void *element;
} BHN_t;

typedef struct BinaryHeap {
    int capacity;
    int num;
    BHN_t **array;
} BH_t;

//////////////////////////////////////////////////
BH_t *createBH(void);
bool destroyBH(BH_t *B, BH_OPTION_e option);
bool insertElementOnBH(BH_t *B, int priority, void *element);
void *pullMinPriorityElementOnBH(BH_t *B);
int getHeightBH(BH_t *B, int rootIndex);
int throwElementInBH(BH_t *B, int priority, void *element);
bool heapingOnBH(BH_t *B);
#ifdef DEBUG
void viewBH(BH_t *B, BH_OPTION_e option);
#endif

#endif
