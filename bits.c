/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(~x&~y))&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x){
        return !y;
    }else{
        if(!y){
            return 0;
        }else{
            return !((x>>31)^(y>>31));
        }
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int t1=((v>>16)>0)<<4;
    v=v>>t1;
    int t2=((v>>8)>0)<<3;
    v=v>>t2;
    int t3=((v>>4)>0)<<2;
    v=v>>t3;
    int t4=((v>>2)>0)<<1;
    v=v>>t4;
    int t5=(v>>1)>0;
    return t1|t2|t3|t4|t5;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int sn=n<<3;
    int sm=m<<3;
    int bn=(x>>sn)&0xFF;
    int bm=(x>>sm)&0xFF;
    int xor=bn^bm;
    return x^(xor<<sn)^(xor<<sm);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result=0;
    int i=32;
    while(i){
        result=(result<<1)|(v&1);
        v=v>>1;
        i=i-1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask=~(((1<<31)>>n)<<1);
    return (x>>n)&mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y=~x;
    int count=0;
    int s;
    s=(!(y&0xFFFF0000))<<4;
    count=count+s;
    y=y<<s;
    s=(!(y&0xFF000000))<<3;
    count=count+s;
    y=y<<s;
    s=(!(y&0xF0000000))<<2;
    count=count+s;
    y=y<<s;
    s=(!(y&0xC0000000))<<1;
    count=count+s;
    y=y<<s;
    s=(!(y&0x80000000));
    count=count+s;
    y=y<<s;
    return count+!y;  //如果x是-1，count=31，加上这个1就能得到32；其他时候！y都是0
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(x==0)return 0;
    if(x==0x80000000)return 0xCF000000;
    unsigned sign=0;
    int exp=158;
    if(x<0){
        sign=0x80000000;
        x=-x;
    }
    while(!(x&0x80000000)){
        x=x<<1;
        exp=exp-1;
    }
    unsigned int f=(x>>8)&0x007FFFFF; 
    unsigned int r=x&0xFF;
    if(r>128){
        f++;
    }else{
        if(r==128){
            if(f&1){
                f++;
            }
        }
    }
    if(f&0x800000){
        exp=exp+1;
        f=f&0x7FFFFF;
    }
    return sign|(exp<<23)|f;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp=(uf>>23)&0xFF;
    if(exp==0xFF)return uf;
    if(exp==0)return (uf&0x80000000)|(uf<<1);
    return uf+(1<<23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign=uf2>>31;
    int exp=((uf2>>20)&0x7FF)-1023;
    unsigned int high=(uf2&0xFFFFF)|0x100000;
    unsigned int low=uf1;
    if(exp<0)return 0;
    if(exp>=31)return 0x80000000;
    int result=0;
    if(exp>=20){
        result=(high<<(exp-20))|(low>>(32-(exp-20))); //高位左移留出空位，低位右移得到低位的高位补上去
    }else{
        result=high>>(20-exp);
    }
    if(sign){
        result=-result;
    }
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127)return 0x7F800000;
    if(x<-149)return 0;
    if(x>=-126){
        int exp=x+127;
        return exp<<23;
    }else{
        int s=x+149;
        return 1<<s;
    }
}
