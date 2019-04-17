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
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);

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
        
        switch (testNo) {
            case 0:
            {
                BH_t *B = createBH();

                printf("\n*** insert ***\n");
                
                for (int i=0; i<numElement; i++) {
                    int value = rand() % 100;
                    Element_t *element = createElement(value);
                    printf("insert [%d] priority : %d\n", i, element->value);
                    insertElementOnBH(B, value ,element);
                }
                
                printf("\n*** heaping ***\n");
                bool check = heapingOnBH(B);
                if (check) {
                    printf("heaping occured.\n");
                }
                else {
                    printf("heaping did not occur.\n");
                }
                
                printf("\n*** pull ***\n");
                
#ifdef DEBUG
                printf("\n--- Binary Heep ---\n");
                viewBH(B, BH_OPTION_VIEW_INT);
#endif
                
                int count = 0;
                while (true) {
                    Element_t *element = pullMinPriorityElementOnBH(B);
                    if (element != NULL) {
                        printf("pull [%d] priority : %d\n", count++, element->value);
                        destroyElement(element);
                    }
                    else {
                        printf("error [%s] : could not pull the element.\n", __func__);
                        break;
                    }
                    
#ifdef DEBUG
                    printf("\n--- Binary Heep ---\n");
                    viewBH(B, BH_OPTION_VIEW_INT);
#endif
                }
                destroyBH(B, BH_OPTION_WITH_ELEMENT);
            }
                break;
            case 1:
            {
                BH_t *B = createBH();

                printf("\n*** throw in ***\n");
                
                for (int i=0; i<numElement; i++) {
                    int value = rand() % 100;
                    Element_t *element = createElement(value);
                    printf("throw in [%d] priority : %d\n", i, element->value);
                    throwElementInBH(B, value ,element);
                }
                
                printf("\n*** heaping ***\n");
                bool check = heapingOnBH(B);
                if (check) {
                    printf("heaping occured.\n");
                }
                else {
                    printf("heaping did not occur.\n");
                }
                
                printf("\n*** pull ***\n");
                
#ifdef DEBUG
                printf("\n--- Binary Heep ---\n");
                viewBH(B, BH_OPTION_VIEW_INT);
#endif
                
                int count = 0;
                while (true) {
                    Element_t *element = pullMinPriorityElementOnBH(B);
                    if (element != NULL) {
                        printf("pull [%d] priority : %d\n", count++, element->value);
                        destroyElement(element);
                    }
                    else {
                        printf("error [%s] : could not pull the element.\n", __func__);
                        break;
                    }
                    
#ifdef DEBUG
                    printf("\n--- Binary Heep ---\n");
                    viewBH(B, BH_OPTION_VIEW_INT);
#endif
                }
                destroyBH(B, BH_OPTION_WITH_ELEMENT);
            }
                // *************************************
                testNo = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
}

Element_t *createElement(int value) {
    Element_t *e = malloc(sizeof(Element_t));
    if (e == NULL) return NULL;
    e->value = value;
    return e;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}
