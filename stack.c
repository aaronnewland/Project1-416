/*
* @author asn89 Aaron Newland
* //TODO: Add Tyler NetID
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Part 1 - Step 1 and 2: Do your tricks here
 * Your goal must be to change the stack frame of caller (main function)
 * such that you get to the line after "r2 = *( (int *) 0 )"
 */
void signal_handle(int signalno) {

    printf("handling segmentation fault!\n");
    //address of param is close to address to return
    //we need to go up the stack to the point where the return address will 
    //instead send us to the line after the segfault
    int *address = &signalno;
    
    int *address2 = address + 4; //access address containing return address to main()
    *address2 += 2; //increment two instructions (after segfault)

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
