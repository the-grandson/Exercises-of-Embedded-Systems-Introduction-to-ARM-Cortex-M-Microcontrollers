// Exercises.c
// Runs on TM4C123
// Solutions to Chapter 6 exercises of the book: "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
// Luis Neto
// 22 August, 2019


/* These exercises are solutions to Chapter 6 of the book>
  "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
  ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015
  Volume 1 Program 4.5
	
	The subroutines are variations of the proposed exercisess because they are implemented in "C".
	The book proposes implementation on assembly.

 Copyright 2019 by Luis Neto, lcsmneto@gmail.com
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */
 
#include <stdint.h>

//8-bit unsigned sum overflow detection and ceiling
uint8_t ceiling_sum(uint8_t a, uint8_t b){
	uint32_t result = a+b; //Promote result
	if(result>255){
		result = 255;
	}
	return result;
}

//Exercise 6.1: Convert a null terminated string to upper case
void Exercise_61(char *string_pt){
	while(*string_pt){ //Assume the string is null temrinated with /0
		if(*string_pt >= 97 && *string_pt < 123){ //All lower case alphabet characters are between 97 and 122
			*string_pt-=0x20; //Subtracting 0x20 gives each character correspondence in capital
		}
		string_pt++; //Move the pointer to the next character
	}
}

//Exercise 6.2: Convert a null terminated string to lower case
void Exercise_62(char *string_pt){
	while(*string_pt){ //Assume the string is null temrinated with /0
		if(*string_pt >= 65 && *string_pt < 91){ //All upper case alphabet characters are between 65 and 91
			*string_pt+=0x20; //Subtracting 0x20 gives each character correspondence in capital
		}
		string_pt++; //Move the pointer to the next character
	}
}

//Exercise 6.3: Compare two null-terminated strings, return 0 if the strings do not match
int32_t Exercise_63(char *string1, char* string2){
	while(*string1 & *string2){ //Check if non 0
		if(*string1 != *string2){ //Compare strings
			return 0; //Do not match
		}
		string1++; //Move the pointer to the next character
		string2++;
	}
	return 1;
}

//Exercise 6.4: Add two equally sized arrays. Pointers to the arrays and the size are passed as arguments.
//The type is 8 bit unsigned with ceilling on overflow.
//The sum is placed back in the second array
void Exercise_64(uint8_t *array1, uint8_t *array2, uint32_t size){
	for(;size>=1;size--){
		*array2 = ceiling_sum(*array1,*array2);
		array1++;
		array2++;
	}
}

//Exercise 6.5: Dot-product of two equally sized arrays. Pointers to the arrays and the size are passed as arguments.
//The result is placed in a new variable
uint32_t Exercise_65(uint8_t *array1, uint8_t *array2, uint32_t size){
	uint32_t result = 0;
	for(;size>=1;size--){
		result += (*array1)*(*array2);
		array1++;
		array2++;
	}
	return result;
}

//Exercise 6.6: Count the number of characters in a string
uint32_t Exercise_66(char *string_pt){
	uint32_t result = 0;
	while(*string_pt){ //Assume the string is null temrinated with /0
		if(*string_pt >= 65 && *string_pt < 91){
			result++; 
		}else if(*string_pt >= 97 && *string_pt < 123){
			result++;
		}
		string_pt++; //Move the pointer to the next character
	}
	return result;
}

//Exercise 6.7: Find the maximum number in a list of 8-bit signed numbers
int8_t Exercise_67(int8_t *array1, uint32_t size){
	int8_t result = -128; //Initiallize result to the smallest 8-bit signed number
	for(;size>=1;size--){
		if(*array1>result){ //Any number great than result actual value, replaces it
			result = *array1;
		}
		array1++;
	}
	return result;
}

//Exercise 6.8: Find the largest absolute number in a list of 8-bit signed numbers
int8_t Exercise_68(int8_t *array1, uint32_t size){
	uint8_t result = 0; //Initiallize result to the smallest 8-bit signed number
	for(;size>=1;size--){
		int8_t absolute = *array1; //Get read of the signal to get the absolute number
		if(absolute < 0){
			absolute *= -1;
		}
		if(absolute > result){ //Any number great than result actual value, replaces it
			result = absolute;
		}
		array1++;
	}
	return result;
}

//Exercise 6.9: Count the frequency of occurrence of letters in a text buffer.
//The result is returned in a 26 element array.
//For example, the frequency of 'A' and 'a' will be inserted in the first position.
//This resolution is not completly correct, it should allocate the result array in heap.
//The way it is, the result will be erased on return because it resides in stack.
uint32_t *Exercise_69(char *string_pt){
	uint32_t result[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	while(*string_pt){ //Assume the string is null temrinated with /0
		if(*string_pt >= 65 && *string_pt < 91){ //Check capital letters
			result[*string_pt-65] += 1; //Subtract 65 to map the letters in the array
		}else if(*string_pt >= 97 && *string_pt < 123){
						result[*string_pt-97] += 1; //Subtract 97 to map the capital letters in the array
		}
		string_pt++; //Move the pointer to the next character
	}
	return &(result[0]);
}

//Exercise 6.10: Retrieve the information stored in a 16-bit matrix, given index as parameters.
//Slightly different from the book, the matrix is row-major.
//The information in the matrix is stored in a row-major format (C does not support column major indexing).
//The row is indexed by 'i' and the column by 'j', 'm' is the number of bytes in each row.
//If the pointer points to the 'Base' address, and is 'n' the number of halfwords in each row, the information at i,j is retrieved by: Base+m*(n*i+j)
uint16_t Exercise_6_10(uint16_t *matrix, uint16_t i, uint16_t j){
	return matrix[8*i+j];
}

//Exercise 6.11: Retrieve the information stored in a 32-bit matrix, given index as parameters.
//Slightly different from the book, the matrix is row-major.
//The information in the matrix is stored in a row-major format (C does not support column major indexing).
//The row is indexed by 'i' and the column by 'j', 'm' is the number of bytes in each row.
//If the pointer points to the 'Base' address, and is 'n' the number of halfwords in each row, the information at i,j is retrieved by: Base+m*(n*i+j)
uint32_t Exercise_6_11(uint32_t *matrix, uint32_t i, uint32_t j){
	return matrix[10*i+j];
}

int main(void){
	
	
	//Declaration of all variables and pointers
	char P[] = "Pechisbeque\n\r";
	char PE[] = "Pchisbeque\n\r";
	
	char *ptr = 0;
	char *ptr_2 = 0;
	
	uint8_t A[] = {5,10,15,150};
	uint8_t B[] = {5,10,15,150};
	int8_t A_signed[] = {-1,1,15,-120};
	
	//Matrix of halfwords with 6 rows by 8 columns
	uint16_t matrix_16[6][8] = {
                     {1,2,3,4,5,6,7,8},
	                   {9,10,11,12,13,14,15,16},
	                   {17,18,19,20,21,22,23,24},
	                   {25,26,27,28,29,30,31,32},
	                   {33,34,35,36,37,38,39,40},
	                   {41,42,43,44,45,46,47,48}
	};
	
	//Matrix of words with 5 rows by 10 columns
	uint32_t matrix_32[5][10] = {
                     {1,2,3,4,5,6,7,8,9,10},
	                   {9,10,11,12,13,14,15,16,17,18},
	                   {17,18,19,20,21,22,23,24,25,26},
	                   {25,26,27,28,29,30,31,32,33,34},
	                   {33,34,35,36,37,38,39,40,41,42}
	};
	
	
	uint16_t mResult = 0;
	
	uint32_t size = 4;
	
	uint32_t result = 0;
	
	ptr = P;
	
	ptr_2 = PE;
	
	
	//Calls to the subroutines implementing the exercises
	Exercise_61(ptr);
	
	Exercise_62(ptr);
	
	Exercise_63(ptr,ptr_2);

	Exercise_64(A,B,size);
	
	result = Exercise_65(A,B,size);
	
	result = Exercise_67(A_signed,size);
	
	result = Exercise_68(A_signed,size);
	
	Exercise_69(ptr);
	
	mResult = Exercise_6_10(&(matrix_16[0][0]), 2, 7);
	
	mResult = Exercise_6_11(&(matrix_32[0][0]), 2, 7);
}
