/*
* @author asn89 Aaron Newland
* @author tjr151 Tyler Radziemski
* CS 416
* Tested on candle, frost
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_TOP_BITS 4 //top bits to extract
#define BITMAP_SIZE 4 //size of the bitmap array
#define SET_BIT_INDEX 17 //bit index to set 
#define GET_BIT_INDEX 17 //bit index to read

static unsigned int myaddress = 4026544704;   // Binary  would be 1111 0000 0000 0000 0011 0010 0100 0000


/* 
 * Function 1: EXTRACTING OUTER (TOP-ORDER) BITS
 */
static unsigned int get_top_bits(unsigned int value,  int num_bits)
{
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

    //Get to the location in the character bitmap array
    //Find block and index needed to read.
    int block;
    block = index / 8;
    index = (index % 8) - 1;

    //Right bit shift by index to get desired bit.
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
    
    /* 
     * Let's try to read bit)
     */
    printf("Function 3: The value at %dth location %d\n", 
            GET_BIT_INDEX, get_bit_at_index(bitmap, GET_BIT_INDEX));
            
    return 0;
}
