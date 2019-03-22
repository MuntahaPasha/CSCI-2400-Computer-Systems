/* 
 * CS:APP Data Lab 
 * 
 * Muntaha Pasha (mupa0444@colorado.edu)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
         
int bitOr(int x, int y) 
{
  return ~(~x & ~y);
}

/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */

int evenBits(void) 
{
    /*COMPLETE*/
    
    //So we had hexidecimal 5 which is 0101. So, 0x55 is 01010101.
    int word=0x55;
    
    //So we shift it by 8. Then it becomes 0101010100000000.
    //Then we add another 0x55 to those last bits, and it becomes 010101010101010101. (Something like that)
    word=word <<8;
    word=word+0x55;
    
    //Then again we shift it by 8, so there's 24 total bits available now, 8 of them at the end are 0's.
    word=word <<8;
    word=word+0x55;
    
    //We add another 0x55 onto it, and then 32 bits are occupied, we add the last 0x55 to the end, and we get 01010101010101010101010101. 
    //And all the even bits should have 1 in them. 2^0, 2^2, 2^4, 2^6, etc.
    word=word <<8;
    word=word+0x55;
    
    return word;
}

/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */

int minusOne(void) 
{
    /*COMPLETE*/
    
    /*If -1 is 1111 1111 1111, and 0 is 0000 0000 0000,
    then ~0 is -1.
    -1 is exlcusively just 1111 1111 1111 1111, etc.
    and 1 would be 0000 0000 0001. 
    */
    
    return ~0x00;
}

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12``
 *   Rating: 2
 */

int allEvenBits(int x) 
{
    /*COMPLETE*/
    
    //0x55555555 is equal to 0101 0101 0101 0101 0101 0101 0101 etc.
    //So lets make our mask 0x55, which is 0101 0101 and left shift it by 8. So it's now 0101 0101 0000 0000.
    //We add 0101 0101 to that and we get 16 bits (4 bytes) of 0101 0101 0101 0101.
    int mask= (0x55 << 8) + 0x55;
    
    //Now, we want to make our earlier mask become 32 bits. So we shift those 16 bits over, now we have 16 0's at the end, and we add mask back on.
    //By adding the 16 bit mask of 0101 0101 0101 0101 to our already 32 bit 0101 0101 0101 0101 0000 0000 0000 0000, we will get a 32 bit number.
    mask = (mask << 16) + mask;
    
    //mask now looks like 0101 0101 0101 0101 0101 0101 0101 0101. All the 1's are in the even spots.
    //So x happened to be 32 bit 0101 0101 0101 0101 0101 0101, etc.
    //If you notice, we are mutliplying x to the mask, and guess what? They're the same exact number. So when you multiply..
    //You get 0101 0101 0101! etc.
    //Now use xOR to compare that to mask, which is also 0101 0101, and you get 0000 0000 0000 for xOR (since all the 1's and 0's align)
    //If you bang the 0, that all becomes 1. Which is what we want.
    return !((x & mask)^mask);
}

/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) 
{
    /*COMPLETE*/ 
    
    //lets start off with test case 0x5. 0x5 is 0101.
    //so lets make ourselves a mask of AA. AA is 1010 1010.
    int oMask=(0xAA);
    
    //Shift our oMask by 8 we get... 1010 1010 0000 0000
    //If we hit that with a xOR comparing our oMask of 8 bits, we get 1010 1010 1010 1010
    oMask = (oMask << 8)^oMask;
    
    //Now we shift oMask 16 bits over. 1010 1010 1010 1010 0000 0000 0000 0000.
    //Use an xOR for comparison with our 16 bit oMask so we get 1010 1010 1010 1010 1010 1010 1010 1010.
    oMask = (oMask << 16)^oMask;
    
    //!! means boolean, return either true or false. 1 or 0.
    //So we now multiply x to our 0 mask. In our case, x is 0x5 (for example)
    //0x5 is 0101. 
    //so when we mutliply that together, we have out mask (1010) * x (0101) which we get 0000 0000. 
    //so its false. double bang will return the 0.
    return !!(x&oMask);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) 
{
    /*COMPLETE*/
    
    //first shift.
    //Shift n, which is 1, in binary 0001 over 3 to the left. We get 1000 = 2^3 = 8.
    int fShift= n<<3;
    
    //second shift.
    //Shift m, which is 3, in binary 0011 over 3 to the left. We get 11000 = 2^4+2^3=8+16=24.
	int sShift= m<<3;
    
    //0xFF is 1111 1111, shifted by fShift(8) --> 1111 1111 0000 0000.
    //0xFF now shifted by sShift(24) --> 1111 1111 0000 0000 0000 0000 0000 0000
    //Now add the two together. We get 1111 1111 0000 0000 1111 1111 0000 0000
    //Take the complement, we get ---> 0000 0000 1111 1111 0000 0000 1111 1111.
	int flipAdd = ~((0xFF << fShift) | (0xFF << sShift));
    
    //now we have our x, in this case its 0x12345678 which is 0001 0010 0011 0100 0101 0110 0111 1000.
    //first we will shift it by fShift(which was 8) to the right. We get... 0000 0000 0001 0010 0011 0100 0101 0110.
	int fByte= (x >> fShift) & 0xFF;
    
    //now our x will be shifted 24 to the right. (sShift was 24)
    //0000 0000 0000 0000 0000 0000 0001 0010.
	int sByte= (x >> sShift) & 0xFF;
    
    //multiply x by flipAdd. 0000 0000 1111 1111 0000 0000 1111 1111*
    //                       0001 0010 0011 0100 0101 0110 0111 1000=
    //                       ----------------------------------------
    //                       0000 0000 0011 0100 0000 0000 0111 1000
    //Now, sByte << fShift means our sByte shifted by 8. So it becomes 0000 0000 0000 0000 0001 0010 0000 0000
    //Then, fByte << sShift means out fByte shifted by 24. So it becomes 0101 0110 0000 0000 0000 0000 0000 0000
    //Now we add the first part, with the second part, with the third part. And we get...
    // 0101 0110 0011 0100 0001 0010 0111 1000
    //  5     6    3   4    1     2   7     8
    return (x & flipAdd) | ((sByte << fShift) | (fByte << sShift));
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    
    /*COMPLETE*/
    
    //Xor adds two bits and discards the overflow completely 
    
    //Lets use our first exmple, with x and y both equal to 0x80000000
    //Now 0x8000000 is 1000 0000 0000 0000 ...etc. And the most singificant bit is 1.
    //1 means that this is negative. If it were a 0, it would imply it being positive. So that 1 is our sign bit and we wanna keep track of it.
    //We are shifting it 31 to the RIGHT.
    //So we get 0000 0000 0000 0000 0000 0000 0000 0001.
    int xSigBit = (x >> 31); 
    
    //Same for y, we shift it 31 to see the sign of it.
    //And in our example, its the same as x so we shift it 0000 0000 0000 0000 0000 0000 0000 0001.
	int ySigBit = (y >> 31); 
    
    //We then add both x and y to get a sum, and shift it 31 to again, see the sign of the sum.
    //The sum bit is 0010. (0001+0001). We shift it 31.
	int sumSigBit = ((x + y) >> 31);

    /*IMPORTANT: One bang sign converts it to a 0 or a 1. Only if its a 0 will it ever be 1. Otherwise, no matter what integer you give a bang sign, it will make it into a 0.*/
    //So the first part, xSigBit compared with SigBit. You get all 0's, because they're the same binary number.
    //Then the ySigBit compared to the sumSigBit, you'll get the last bit to be 0001, but since its then being multiplied to the first result which we got as all zero's, the entire thing becomes zero. 
    //Take the compliment and you get 1111 1111 1111...etc.
    //Once we bang that we get a 0. (anything bigger than 0 when its banged gets turned to 0.)
    //And that is the correct result we want. A 0.
    return !(~(xSigBit^ySigBit) & (ySigBit^sumSigBit));
    
	//in our test cases given, either the xSigBit and ySigBit are going to be different, but even if they're same they must be the same as the sumSigBit otherwise you're going to get a overflow.
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
    /*COMPLETE*/
    
    /*m is ~0x00, which would be 1111 1111. 
    We add that to !x. x=2, so !2 equals 0. 
    So 1111 1111 + 0, is just 1111 1111.*/
    
    int m = ~0x00 + !x;
    
    //Now let's do y multiply by m. m is 1111 1111, and y is 4. Which is 0100.
    //so 1111 1111 * 0000 0100, is just 0100.
    //Now the second part of the conditional. z multiply by complement m. 
    //m was 1111 1111, so ~m is 0000 0000. Multiply that by z (z is 5 which is 0101) and that is just gonna give you 0000 0000.
    //So we add the first part (0100) + (0000) and we get 0100. Which is 4.
    //Woo!
    
    return (y&m)|(z&~m);
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{
    /*COMPLETE*/
    
    //Firstly, what this is saying is 48 <= x <= 57
    
    //So we can first have a sign checker, and what this will do is push the 1 31 bits to the right, implying that this would be negative.
    int checkSign = 1 << 31;
    
    //If greater than 57 (or 0x39) is added, then the result will become negative.
    //So we take the complement.
    int upLimit = ~(checkSign | 0x39);
    
    //If less than 48 (or 0x30) is added, then the result will also be negative.
    int lowLimit = ~0x30;
    
    //Now we should check the sign bits by adding x to our upper limits and lower limits, and checking the sign bits for each of them.
    upLimit = checkSign & (upLimit+x) >> 31;
    lowLimit = checkSign & (lowLimit+1+x) >> 31; 
    
    //If we find that the upper or lower limit is negative, then it can't be in the range we are looking for.
    return !(upLimit | lowLimit); 
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)
{
    /*COMPLETE*/
    //So, n=1, so in binary that's 0001. 
    //We shift nby 3, so it becomes 1000.
    int a= n << 3;
    
    //Our mask is FF, which is 1111 1111, shifted a. well, a is 1000, and the 1 is in the 2^3 place, so that means it's 8.
    //So we shift mask over 8 bits. 1111 1111 0000 0000. 
	int mask= 0xFF << a;
    
    //Now we have c. in our case, c is 0xab. that is 1010 1011. Shift that a, so like in the previous one, shift it 8 bits to the left.
    //1010 1011 0000 0000
	int shift = c << a;
    
    //Now we take the ~mask which is 0000 0000 1111 1111, and we multiply it to 0x123456578.
    //0001 0010 0011 0100 0101 0110 0111 1000 *
    //0000 0000 0000 0000 0000 0000 1111 1111 =
    //------------------------------------------
    //0000 0000 0000 0000 0000 0000 0111 1000
    //Now we add shift. So we get...
    //1010 1011 0111 1000. 
    //Now you'll see. This equates to.. a b 7 8. Which if you look above is exactly what we want!
	return (x & ~mask) | shift;
}
/* reverseBits - reverse the bits in a 32-bit integer,
              i.e. b0 swaps with b31, b1 with b30, etc
 *  Examples: reverseBits(0x11111111) = 0x88888888
 *            reverseBits(0xdeadbeef) = 0xf77db57b
 *            reverseBits(0x88888888) = 0x11111111
 *            reverseBits(0)  = 0
 *            reverseBits(-1) = -1
 *            reverseBits(0x9) = 0x90000000
 *  Legal ops: ! ~ & ^ | + << >> and unsigned int type
 *  Max ops: 90
 *  Rating: 4
 */
int reverseBits(int x) 
{
    /*COMPLETE*/
    
    //We make a 32 bit integer representation by using shifts, and we swap different bytes with eachother, as well as swap the order in which they appear, hence our shifting takes place differently for each one.
    
    //By using parentheses to shift each one separately and reverse the order it makes it more efficient.
    x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
    x = ((x >> 2) & 0x33333333u) | ((x & 0x33333333u) << 2);
    x = ((x >> 4) & 0x0f0f0f0fu) | ((x & 0x0f0f0f0fu) << 4);
    x = ((x >> 8) & 0x00ff00ffu) | ((x & 0x00ff00ffu) << 8);
    x = ((x >> 16) & 0xffffu) | ((x & 0xffffu) << 16);
    
    //returning x should weild us a 32 bit strand where the first byte was now in the last, second in the second-to-last with their bits all reversed as well.
    return x;

}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) 
{
    /*COMPLETE*/
    
    //The sign of the sum, like in the overflow function, has to be same sign as inputs, otherwise you will have an overflow.
    int sum = x + y;  
    
    //Performs a xOR with the sum and x, and if they are different you will get 0, but if they are the same you'll get a 1. It then ands that with the sum sxOR with y, if they are different you get a 0, if they're the same you get a 1, and the and operator will only return 1 if they have the same sign, otherwise it'll a return 0. We then right shift by 31.
    int isOverFlow = ((sum ^ x) & (sum ^ y)) >> 31;  
    //when positive overflow, return max value
    //when negative overflow occur, return min value
    
    //We add the two checks together and then shift the sum by them.
    return (sum >> (isOverFlow & 31)) + (isOverFlow << 31);  
}
/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) 
{
    //1<<31 is 1000 0000 0000 0000 etc
    //So the complement of that is 0111 1111 1111 1111 etc. Now our sign is 0, our MSB is positive!
    //Now uf must be unsigned, so its positive. so lets say we were given 1.25, which in binary is 0001.11
    //so we'd have 0111 1111 1111 1111.0000 0000*
    //             0000 0000 0000 0001.11=
    //              -------------------------------
    //                            0001.00
    //It's not only positive, which is what we want, but also absolute floating point. No fraction.
    //return uf & ~(1<<31);
    return 2;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  return 2;
}
