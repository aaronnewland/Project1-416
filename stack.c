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
 /*
*  Where is the program counter, and how did you use GDB to locate the PC? 3. 
*  What were the changes to get the desired result?
*  
*  From main() a signal handler is called, by getting information about the stack
*  frame from gdb (using info frame) the stack frame of main() has saved the contents
*  of its program counter at a memory address. By examining this address the adress
*  of the program counter from main() is retrieved. Once the address of main()'s eip
*  was found, by stepping through the program in gdb inside the signal handler the integer
*  value of singalno could be found through an lea operation to the eax register.
*  Through examining the contents of eax the adress of signalno was obtained.
*  Then, through finding the difference between the two numbers the offset was obtained as well.
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
