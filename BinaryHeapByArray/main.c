#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "BinaryHeapByArray.h"

//////////////////////////////////////////////////
typedef struct Element {
    int priority;
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int priority, int value);
bool destroyElement(Element_t *element);
void displayStatus(BH_t *B);
int levelOrderTraversalOnBHslave(BH_t *B, int rootIndex, void *parameter);
int preOrderTraversalOnBHslave(BH_t *B, int rootIndex, void *parameter);
int inOrderTraversalOnBHslave(BH_t *B, int rootIndex, void *parameter);
int postOrderTraversalOnBHslave(BH_t *B, int rootIndex, void *parameter);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 10;
    int numElement = 30;
    srand((unsigned) time(NULL));
    
    for (int testNo=0; testNo<testCount; testNo++) {
        printf("\n*** [Test #%d] ***\n", testNo+1);
        BH_t *B = createBH();
        
        switch (testNo) {
            case 0:
            {
                printf("\n*** insert ***\n");
                for (int i=0; i<numElement; i++) {
                    Element_t *element = createElement(rand() % 100, i);
                    insertElementOnBH(B, element->priority ,element);
                    printf("insert #%2d : priority = %2d, element = %d\n", i, element->priority, element->value);
                }
                
                printf("\n*** heaping ***\n");
                bool check = heapingOnBH(B);
                if (check) {
                    printf("Heaping was done.\n");
                }
                else {
                    printf("Heaping was not necessary.\n");
                }
                
                printf("\n*** status ***\n");
                displayStatus(B);
                
                printf("\n*** pull min. ***\n");
#ifdef DEBUG
                viewBH(B, BH_OPTION_VIEW_INT);
#endif
                int count = 0;
                while (true) {
                    Element_t *element = pullMinPriorityElementOnBH(B);
                    if (element == NULL) break;
                    printf("pull min. #%2d : priority = %2d, element = %d\n", count++, element->priority, element->value);
                    destroyElement(element);
#ifdef DEBUG
                    viewBH(B, BH_OPTION_VIEW_INT);
#endif
                }
            }
                break;
            case 1:
            {
                printf("\n*** throw in ***\n");
                for (int i=0; i<numElement; i++) {
                    Element_t *element = createElement(rand() % 100, i);
                    throwElementInBH(B, element->priority ,element);
                    printf("throw in #%2d : priority = %2d, element = %d\n", i, element->priority, element->value);
                }
                
                printf("\n*** heaping ***\n");
                bool check = heapingOnBH(B);
                if (check) {
                    printf("Heaping was done.\n");
                }
                else {
                    printf("Heaping was not necessary.\n");
                }
                
                printf("\n*** status ***\n");
                displayStatus(B);
                
                printf("\n*** pull min. ***\n");
#ifdef DEBUG
                viewBH(B, BH_OPTION_VIEW_INT);
#endif
                int count = 0;
                while (true) {
                    Element_t *element = pullMinPriorityElementOnBH(B);
                    if (element == NULL) break;
                    printf("pull min. #%2d : priority = %2d, element = %d\n", count++, element->priority, element->value);
                    destroyElement(element);
#ifdef DEBUG
                    viewBH(B, BH_OPTION_VIEW_INT);
#endif
                }
            }
                break;
            case 2:
            {
                printf("\n*** insert ***\n");
                for (int i=0; i<numElement; i++) {
                    Element_t *element = createElement(rand() % 100, i);
                    insertElementOnBH(B, element->priority ,element);
                    printf("insert #%2d : priority = %2d, element = %d\n", i, element->priority, element->value);
                }
                
                printf("\n*** heaping ***\n");
                bool check = heapingOnBH(B);
                if (check) {
                    printf("Heaping was done.\n");
                }
                else {
                    printf("Heaping was not necessary.\n");
                }
                
                printf("\n*** status ***\n");
                displayStatus(B);
                
                printf("\n*** pull max. ***\n");
#ifdef DEBUG
                viewBH(B, BH_OPTION_VIEW_INT);
#endif
                int count = 0;
                while (true) {
                    Element_t *element = pullMaxPriorityElementOnBH(B);
                    if (element == NULL) break;
                    printf("pull max. #%2d : priority = %2d, element = %d\n", count++, element->priority, element->value);
                    destroyElement(element);
#ifdef DEBUG
                    viewBH(B, BH_OPTION_VIEW_INT);
#endif
                }
            }
                // *************************************
                testNo = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
        destroyBH(B, BH_OPTION_WITH_ELEMENT);
    }
}

Element_t *createElement(int priority, int value) {
    Element_t *e = malloc(sizeof(Element_t));
    if (e == NULL) return NULL;
    e->priority = priority;
    e->value = value;
    return e;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

void displayStatus(BH_t *B) {
    printf("height of tree  = %d\n", getHeightBH(B, 0));
    printf("capacity        = %d\n", B->capacity);
    printf("num of elements = %d\n", B->num);
    printf("use rate        = %-5.2lf%%\n", B->num/(double)B->capacity*100);
    printf("min priority    = %d\n", ((Element_t*)peekMinPriorityElementOnBH(B))->priority);
    printf("max priority    = %d\n", ((Element_t*)peekMaxPriorityElementOnBH(B))->priority);
}
