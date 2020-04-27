#include <stdio.h>
#define HALF_BITS_LENGTH 4
#define FULLMASK 255 //11111111
#define LMASK (FULLMASK << HALF_BITS_LENGTH) // 11110000
#define RMASK (FULLMASK >> HALF_BITS_LENGTH) // 00001111
#define RSET(b, n) (b = ((LMASK & b) ^ n))
#define LSET(b, n) (b = ((RMASK & b) ^ (n << HALF_BITS_LENGTH)))
#define RGET(b) (RMASK & b)
#define LGET(b) ((LMASK & b) >> HALF_BITS_LENGTH)
#define GRIDW 3

int main() 
{
    /*二进制 一个int分成两个16位
    unsigned char b;
    for(LSET(b,1); LGET(b) <= GRIDW * GRIDW; LSET(b, (LGET(b) + 1)))
        for(RSET(b,1); RGET(b) <= GRIDW * GRIDW; RSET(b, (RGET(b) + 1)))
            if(LGET(b) % GRIDW != RGET(b) % GRIDW)
                printf("A = %d, B = %d\n", LGET(b), RGET(b));
    return 0;
    */
    //三进制 只要81个位置
    int i = 81;
    while(i--){
        if(i < 0) break;
        if(i/9%3 == i%9%3)
            continue;
        printf("A = %d, B = %d\n", i/9+1, i%9+1);
    }
}