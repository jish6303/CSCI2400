/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
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
/* Define __STDC_IEC_559__ and other similar macros.  */
/* Copyright (C) 2005 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	int a=~(x&~y);
	int b=~(~x&y);
	int z=~(a&b);
  return z;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8 
 *   Rating: 1
 */
int fitsShort(int x) {
	int a = x>>15;  //shif left 15 bits, then i can keep sign bit and 
					//rest of left 16 bis of x
					//and i have to make the rest of 32 bits either be  1 or 0, 
	int b = !(a);   //  because if it is different, x will extend the interval.
	int c = !(a^(~0));
	return b + c; 
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
	int x = 0x24;   // it is 100100
	x = x+(x<<6);  // 100100+ 100100(000000)=100100100100
	x = x+(x<<12);  // 100100100100+100100100100(000000000000)=100100100100100100100100
	x = x+(x<<24);  // 100100100100100100100100+100100100100(000000000000000000000000)=100100100100100100100100100100100100
  return (x<<1)+1;   //   001001001001001001001001001001001001
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) { 
	return ((!!n & 1) << 31) >> (n + ~0);  // the first part is make this ether 100....31 piece of 0;
												//and when n is 0, so it is all 0. then shif n-1 times left

}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int mask = x >> 31;
	int size = n + ~0;

	int tmp1 = ~x & mask;
	int tmp2 = x & ~mask;

   return !((tmp1 + tmp2) >> size);
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
	
    return (!x)|y;              //when (1,0) is 0 and (0,1) is 1;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
	  //printf("~x+1, %d,\n", ~x+1);
      //printf("(~x+1)&x, %d,\n", (~x+1)&x);
  return (~x+1)&x;      //~x+1 will make the first couple of 0 which is before the 1 to be 1. so when 
						// ~x adds 1, it will keep the 1 in the first positioni, after &x, so it will just
						// keep this 1

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
int isAsciiDigit(int x) {

    int filter = 0x30;	// check whether has two 1 in the 0...00110000,
    int check30 = x ^ filter; // if it is , then it will make those two 1 become 0, rest of the numbers are still the same
    filter = 0x9;   //this is 0...001001     ~ filter become  111....1110110
    int check9 = check30 & ~filter;   // check whether x is euqal to 8 or 9, and rest of the numbers is 0 or not.
    filter = 0x7;     // this is 0....000111,  ~filter is 11111....111000. 
    int check7 = check30 & ~filter;    // this checks whether x is between 0 to 7, if it is , then it is 0, not then 1
    return !check7 | !check9;
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
	int a=(x>>31)&1;  // if the first 2 digits is different ,then <<1 will overflow.
	int b=(x>>30)&1;	// if the first 2 digits is same, it will not matter
	int sign=!(a^b);	//decide whethere the two MSB are the same or not
	int maximun=1<<31;
	int c=((~sign)+1)&(x<<1);   // this is if else
	int d=((~(!sign)+1))&(a+~maximun);
	
   return  c|d;
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  return (x << n) | (x >> (32 - n)) & ~(~0 << n);
  /*
   * 0x87654321=10000111011001010100001100100001, 0x76543218= 01110110010101000011001000011000
   * x<<n will delete the left 4 bits and keep right first 4 bits being 0. and x>>(32-n) will get the left 4 bits, but it will have all 1 in the left probably.
   * so we have to use ~(~0 << n), this will make the right first 4 bits become 1 and rest of bits become 0, so when these
   *two have &, it will keep only left 4 bits, and when they | together, it will just have the result.
   */
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
 
      //printf("x, %d, \n", x);
      //printf("y, %d, \n", y);
       ////printf("y1, %d, \n", y1);
       //printf("sum, %d, \n", sum);
    //printf("sign0, %d, \n", sign0);
    //printf("sign1, %d, \n", sign1);
    //printf("sign2, %d, \n", sign2);
    //printf("sign, %d, \n", sign);
    //printf("overflow, %d, \n", overflow);
    //printf("result, %d, \n", result);
  //return result;
  
int subOK(int x, int y) {
    //int a=1<<31;
    int y1=~y+1;
	int sum = x + y1;   //If operands have different signs, there cannot be an overflow. If the signs are equal and the sum's sign is different, we had an overflow:
                        //overflow = (x ^ s) & (y ^ s);  s = x + y
    int sign0=(sum>>31)&1;
    int sign1=(x>>31)&1;
    int sign2=(y>>31)&1;   // get the sign of each number
    //int sign=sign1^sign2;  
    //int overflow = (sign1 ^ sign0) & (sign2 ^ sign0);
    return !((!sign1&sign2&sign0) | (sign1 & !sign2 & !sign0));


// /*case 1: x positive, y positive: overflow doesn't occur
  //* case 2 : x negative, y negative : overflow doesn't occur
  //* case 3 : x positive y negative : overflow could occur if sign of diff is
  //* negative
  //* case 4 :  x negative, y positive : overflow could occur if sign of diff is
  //* positive
//*/

}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
	int a = x ^ (x << 16);  //
	int b = a ^ (a << 8);
	int c = b ^ (b << 4);
	int d = c ^ (c << 2);
	int e = d ^ (d << 1);
	return !!(e & (1<<31));
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {

    int xhold = x+(~0);
    int onehold = !!x^(x>>31 & 1);
    xhold = xhold & x;
    return ((!xhold)& onehold);

}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
	int v = x;
	int r;	// store our result here
	int shift;
	int full = !(~x); // we must add one if we have 0xffffffff

	// This awesome algorithm's credit goes to Olafur P.G.
	// Without his insight I would never have been able to derive it

	// Check the top 16 bits and add them to our result if they exist
	r     = !(~(v>>16)) << 4;
	v   <<= r;
	// check the remaining 8 bits
	shift = !(~(v >> 24)) << 3;
	v   <<= shift;
	r    |= shift;
	// remaining 4 bits
	shift = !(~(v>>28)) << 2;
	v   <<= shift;
	r    |= shift;
	// remaining 2 bits
	shift = !(~(v >> 30)) << 1;
	v   <<= shift;
	r    |= shift;
	// remaining 1 bits
	r    ^= 1&((v>>31));

	// rememer to add one if we have 32 on bits
	return r + full;
}
/* Extra credit */
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
