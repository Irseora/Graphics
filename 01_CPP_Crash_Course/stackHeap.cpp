#include "stackHeap.h"
#include <iostream>

void functionOnStack()
{
    int imOnTheStackToo = 0;
    std::cout << &imOnTheStackToo << std::endl;
}

void stackHeap()
{
    // If you want to declare an object in C on the stack
    // it's the same in CPP
    int imOnTheStack = 1;

    // Allocate on the heap in C 
    int* onHeapCstyle = (int*)std::malloc(1 * sizeof(int)); // 1,  because we want space for one int
    *onHeapCstyle = -5;
    std::cout << "Value on heap C style: " << *onHeapCstyle << std::endl;
    // The CPP way
    int* onHeapCPPstyle = new int(5);
    std::cout << "Value on heap CPP style: " << *onHeapCPPstyle << std::endl;
    // Where are the variables onHeapCstyle and onHeapCPPstyle located? (stack/heap)

    // We need to manually free memory allocated on the heap!
    // In C with the free function; in CPP with the delete operator
    // DO NOT mix them!
    std::free(onHeapCstyle);
    delete onHeapCPPstyle;

    // If we want to allocate an array on the stack
    int arrayOnStack[3];
    // You can decide how do you index it
    arrayOnStack[0] = 1;
    *(arrayOnStack + 1) = 3;
    (arrayOnStack + 4)[-2] = 5;

    // Initialization with a specific value can only be done together with declaration
    // int arrayOnStack[] = {2,4,6};
    std::cout << "Array on stack: ";
    for (int i = 0; i < sizeof(arrayOnStack) / sizeof(arrayOnStack[0]); ++i)
        std::cout << arrayOnStack[i] << " ";
    std::cout << std::endl;

    // If we want to allocate on the heap
    int* arrayOnHeap = new int[5] {0, 1, 2, 3, 4};
    std::cout << "Array on heap: ";
    for (int i = 0; i < 5; ++i)
        std::cout << arrayOnHeap[i] << " ";
    std::cout << std::endl;

    // DO NOT mix delete[] with delete
    delete[] arrayOnHeap;

    // The called functions and inner blocks are also on the stack,
    // which we can infer from the proximity of the memory addresses
    std::cout << "Stack memory addresses: " << std::endl;
    {
        int valueOnTheStack = 0;
        functionOnStack();
        std::cout << &valueOnTheStack << std::endl;
    }
}