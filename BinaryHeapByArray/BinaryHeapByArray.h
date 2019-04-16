#ifndef BinaryHeapByArray_h
#define BinaryHeapByArray_h

//////////////////////////////////////////////////
#define BH_INITIAL_CAPACITY 16;

typedef enum BHOption {
    BH_OPTION_NONE,
    BH_OPTION_WITH_ELEMENT,
    
    BH_OPTION_BREADTH_FIRST_SEARCH = 10,
    BH_OPTION_DEPTH_FIRST_SEARCH,
    
    BH_OPTION_VIEW_INT = 20,
    BH_OPTION_VIEW_CHAR
} BH_OPTION_e;

typedef struct BinaryTree_Node {
    int priority;
    void *element;
} BHN_t;

typedef struct BinaryTree {
    int capacity;
    BHN_t **array;
} BH_t;

//////////////////////////////////////////////////
BH_t *createBH(void);
bool destroyBH(BH_t *B, BH_OPTION_e option);
bool insertElementOnBH(BH_t *B, int priority, void *element);
void *pullMinPriorityElementOnBH(BH_t *B);
int getHeightBH(BH_t *B, int rootIndex);
// for debug
void viewBH(BH_t *B, BH_OPTION_e option);

#endif
