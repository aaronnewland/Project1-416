/*
* @author asn89 Aaron Newland
* @author tjr151 Tyler Radziemski
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//TODO: DELETE MACROS
#define DEBUG 0

/* Part 1 - Step 1 and 2: Do your tricks here
 * Your goal must be to change the stack frame of caller (main function)
 * such that you get to the line after "r2 = *( (int *) 0 )"
 */
void signal_handle(int signalno) {
    int* temp;
    temp = &signalno;

    if (DEBUG) {
        printf("address: %p\n", temp);
        printf("val1: %u\n", *temp);
    }
    temp += 15;
    *temp += 2;
    if (DEBUG) {
        printf("address: %p\n", temp);
        printf("val: %X\n", *temp);
    }
    printf("handling segmentation fault!\n");

    /* Step 2: Handle segfault and change the stack*/
}

int main(int argc, char *argv[]) {

    int r2 = 0;

    /* Step 1: Register signal handler first*/
    signal(SIGSEGV, signal_handle);

    r2 = *( (int *) 0 ); // This will generate segmentation fault

    r2 = r2 + 1 * 30;
    printf("result after handling seg fault %d!\n", r2);

    return 0;
}
