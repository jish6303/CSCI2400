
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

#endif

int bitXor(int x, int y) {//truth table x y a ~a b ~b z
	int a = x & y;//                    1 1 1  0 0  1 0
	int b = ~x & ~y;//                  0 0 0  1 1  0 1 
    int z = ~a & ~b;//                  1 0 0  1 0  1 1
	return z;//a keeps both 1, b keeps both 0
}

int fitsShort(int x) { //Ideal number should be all 0s or all 1s in highest 17 digits.
  int n=(x>>15);//shift right 15 bits, ideal result should return 0, or 17 of 1s.
  return !n + !(~n);// 17 of 1s produces 0 in the left and 1 of right. 17 of 0s produces 1 in the right and 0 of left. All other cases produce 0 at both sides.
}

int thirdBits(void) {
	int a = 0x24;// binary 100100, 6 bits
	a=a+(a<<6);// 100100100100, 13 bits
	a=a+(a<<12);//100100100100100100100100, 24 bits
	a=a+(a<<24);//00100100100100100100100100100100, 32 bits
	return (a<<1)+1;//01001001001001001001001001001001,32 bits
}

int upperBits(int n) {
	return ((!!n) << 31) >> (n + ~0);//((!!n) << 31) sets the highest bit to 1, and (n + ~0)==n-1, right shift (n-1) bit and set them to 1.
}

int fitsBits(int x, int n) {
  int ma = x >> 31;//right shift 31 bits, leaving the highest digit. If(x<0), ma is 32 of 1s, else ma is 32 of 0s
  int si = n + ~0;//size n-1
  int tp1 = ~x & ma;// if (x<0), tp1 is ~x. if(x>=0), tp1 is all 0s, as ma is all 0s. 
  int tp2 = x & ~ma;// if (x<0), tp2 is all 0s, as ~ma is all 0s. If(x>=0) tp2 is x.
   return !((tp1 + tp2) >> si); // if (x<0) tp1+tp2=~x, else tp1+tp2=x. If move (n-1) bits both cases should be all 0 if we want to return 1.
}

int implication(int x, int y) {
    return y|(!x);//write a truth table. x=1,y=1,r=1; x=0,y=1,r=1; x=1,y=0,r=0; x=0,y=0,r=0
}

int leastBitPos(int x) {
  return x&(~x+1);//~x reverses all digits of x. ~x+1 is able to change the lowest 0 in ~x (lowest 1 in x) into 1, with digits below it all 0s.
}

int isAsciiDigit(int x) {
    return !((x^0x30)& ~0x9)|!((x^0x30)& ~0x7);//x^0x30 is (x^0x30). Any valid number (x^0x30) we want is between 0x0 (0000) and 0x9 (1001)
                                               // ~0x9=-10 (1....10110), ~0x7=-8 (....1000). Any number(x^0x30) exceeds 9 (1001) will cause both ((x^0x30)& ~0x7) and ((x^0x30)& ~0x9) be 1.
}                                              // Any negative number will have highest digits 1.

int satMul2(int x) {
  int h=(x>>31)&1;  //If the highest bit is 1(x<0), then a is 1. Else a is 0.
  int sh=(x>>30)&1;	// Highest two bits could be four situations: 00, 11, 01, 10. 01 and 10 include overload situations. This manipulation displays the second most highest bit. 
  int sign=!(h^sh);	// If and only if a==b sign=1, no overflow. 
  int max=1<<31;
  int a=((~sign)+1)&(x<<1);   //a is not 0 if sign==1. x<<1. 
  int b=((~(!sign)+1))&(h+~max);// b is not 0 if sign==0. if x starts with 01, return Max 2147483647. else return -2147483648.
  return  a|b;//Either a or b but not both: if there is no need to overflow, sign=1, (~sign)+1=0xffffffff, ~(!sign)+1=0. If there is need to overflow, the reverse 
}

int rotateLeft(int x, int n) {
  return (x << n) | ((x >> (32+~n+1)) & ~(~0 << n));
  //x<<n will probabaly delete the left n bits and keep right first n bits being 0. and x>>(32-n) will get the left n bits. but it will have all 1 in the left probably.
  //so we have to use ~(~0 << n), this will make the right first n bits become 1 and rest of bits become 0, so when these
  //two have &, it will keep only left n bits, and when they | together, it will just have the result.
}

int subOK(int x, int y) {
	int y1=~y+1;//y1=-y
	int dif = x + y1;// x-y
    int sign0=(dif>>31)&1;//get the highest digit of dif, 1 or 0.
    int sign1=(x>>31)&1;//get the hightest digit of x, 1 or 0.
    int sign2=(y>>31)&1;//get the hightest digit of y, 1 or 0.
    return !((!sign1&sign2&sign0) | (sign1 & !sign2 & !sign0));//Two cases that causes overflow: x positive(0) y negative(1) dif negative(1), x negative(1) y and dif positive(0)
}

int bitParity(int x) { //XORing two numbers returns a number with same bit parity.
	x = ( x >> 16 ) ^ x;//
	x = ( x >> 8 ) ^ x;
	x = ( x >> 4 ) ^ x;
	x = ( x >> 2 ) ^ x;
	x = ( x >> 1) ^ x;
	return (x & 1);
}

int isPower2(int x) {
    int min,sign,minus;//What we want: Only one 1, and the highest cannot be 1.
    min=~0;// 0xffffffff
    sign=x>>31;//get the sign, 0x0 (x>=0) or 0xffffffff (x<0)
    minus=(min^sign);// if x<0 minus=0x0, else minus=0xffffffff
    return !((x&(x+minus))+!x);//if x>0 and x is the power of 2, x&(x+minus)=x&(x-1)=0 return 1. 
                               //if x>0 but x is not the power of 2, return 0.
                               //if x=0 return 0.
                               //if x<0 and ((x&(x+minus))+!x) is not zero anyway, return 0.
}

int leftBitCount(int x) {
	int v = x;
	int r;	// store our result here
	int shift;
	int full = !(~x); // we must add one if we have 0xffffffff
	r     = !(~(v>>16)) << 4;//if there is no 16 consecutive 1s in the highest digits, v>>16 is a number of 1s amd 0s, so is ~(v>>16). If there is 16 consecutive 1s in the highest digits, r=16(binary 10000).
	v   <<= r;//if r=16, we need to check the other 16 bits, so make the shift of 16 bits. If r=0, there is no need to shift and we check the highest 8 bits.
	shift = !(~(v >> 24)) << 3;//check the highest 8 digits of current v
	v   <<= shift;//
	r    |= shift;//add
	shift = !(~(v>>28)) << 2;
	v   <<= shift;
	r    |= shift;
	shift = !(~(v >> 30)) << 1;
	v   <<= shift;
	r    |= shift;
	r    |= 1&((v>>31));//highest current 1 digit, also is original lowest 1 digit, return 1 or 0
	return r + full;//if x==-1, add 1 to create the "overflow".
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
