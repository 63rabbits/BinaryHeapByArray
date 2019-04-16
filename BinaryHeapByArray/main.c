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
    int numElement = 30;
    srand((unsigned) time(NULL));

    BH_t *B = createBH();

    for (int i=0; i<numElement; i++) {
        int value = rand() % 100;
        Element_t *element = createElement(value);
        insertElementOnBH(B, value ,element);
    }
    
    printf("*** pull ***\n");
    printf("--- Binary Tree ---\n");
    viewBH(B, BH_OPTION_VIEW_INT);
    
    while (true) {
        Element_t *element = pullMinPriorityElementOnBH(B);
        if (element != NULL) {
            printf("pull value : %d : success.\n", element->value);
            destroyElement(element);
        }
        else {
            printf("error [%s] : could not pull the element.\n", __func__);
            break;
        }

        printf("--- Binary Tree ---\n");
        viewBH(B, BH_OPTION_VIEW_INT);
    }
    
    destroyBH(B, BH_OPTION_WITH_ELEMENT);
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
