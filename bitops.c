/*
* @author asn89 Aaron Newland
* @author tjr151 Tyler Radziemski
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_TOP_BITS 4 //top bits to extract
#define BITMAP_SIZE 4 //size of the bitmap array
#define SET_BIT_INDEX 17 //bit index to set 
#define GET_BIT_INDEX 17 //bit index to read

#define DEBUG 0

static unsigned int myaddress = 4026544704;   // Binary  would be 1111 0000 0000 0000 0011 0010 0100 0000


/* 
 * Function 1: EXTRACTING OUTER (TOP-ORDER) BITS
 */
static unsigned int get_top_bits(unsigned int value,  int num_bits)
{
    //TODO: Add edge case testing.
    if (num_bits == 32) {
        return value;
    }
    //Create bit mask.
    unsigned int bit_mask;
    //Left shift by num_bits to get number of bits needed.
    //Subtract 1 to set all bits to 1.
    bit_mask = (1 << num_bits) - 1;

    return (value >> (32 - num_bits)) & bit_mask;
}


/* 
 * Function 2: SETTING A BIT AT AN INDEX 
 * Function to set a bit at "index" bitmap
 */
static void set_bit_at_index(char *bitmap, int index)
{
    /*
    //Tyler solution
    //Implement your code here	

    //remember zero indexing!!! 1st byte is bitmap[0], first bit is byte[0], 
    //17th bit is the first bit of byte 2 (3rd byte total)
    
    int byte = (BITMAP_SIZE * 8) / index; 
    int remainder = (index % 8) - 1; //17 % 8 = 1 

    bitmap[byte] |= 1 << remainder;
    */
    
    //TODO: More testing.

    //Find block and index needed to set.
    int block;
    block = index / 8;
    index = (index % 8) - 1;

    //Create bit mask.
    unsigned int bit_mask;
    bit_mask = 1 << index;

    //Use bitwise OR to set only if bit is not previously set.
    unsigned int val = bitmap[block] | bit_mask;

    //Return new value back in modified block of bitmap.
    bitmap[block] = val;

    return;
}


/* 
 * Function 3: GETTING A BIT AT AN INDEX 
 * Function to get a bit at "index"
 */
static int get_bit_at_index(char *bitmap, int index)
{
    //TODO: More testing.

    //Get to the location in the character bitmap array
    //Find block and index needed to read.
    int block;
    block = index / 8;
    index = (index % 8) - 1;

    //Use bitwise OR with a 0 to get bit from bitmap.
    unsigned int val = bitmap[block] >> index;

    return val;
    
}


int main () {

    /* 
     * Function 1: Finding value of top order (outer) bits Now let’s say we
     * need to extract just the top (outer) 4 bits (1111), which is decimal 15  
    */
    unsigned int outer_bits_value = get_top_bits (myaddress , NUM_TOP_BITS);
    printf("Function 1: Outer bits value %u \n", outer_bits_value); 
    printf("\n");

    /* 
     * Function 2 and 3: Checking if a bit is set or not
     */
    char *bitmap = (char *)malloc(BITMAP_SIZE);  //We can store 32 bits (4*8-bit per character)
    memset(bitmap,0, BITMAP_SIZE); //clear everything
    
    /* 
     * Let's try to set the bit 
     */
    set_bit_at_index(bitmap, SET_BIT_INDEX);

    //DEBUG: SET 'DEBUG' MACRO TO 1
    if (DEBUG) {
        printf("block 0: %u\n", bitmap[0]);
        printf("block 1: %u\n", bitmap[1]);
        printf("block 2: %u\n", bitmap[2]);
        printf("block 3: %u\n", bitmap[3]);
    }
    
    /* 
     * Let's try to read bit)
     */
    printf("Function 3: The value at %dth location %d\n", 
            GET_BIT_INDEX, get_bit_at_index(bitmap, GET_BIT_INDEX));
            
    return 0;
}
