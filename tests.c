#include <stdio.h>
#include "reconocedor.h"
#include <assert.h>
int main(void){
    assert(conseguirIndice(46) == -1);
    assert(conseguirIndice(44) == -1);
    assert(conseguirIndice(58) == -1);
    assert(conseguirIndice(10) == -1);
    assert(T(0,51) == 1);
    assert(T(0,41) == 3);
    assert(T(1,53) == 1);
    assert(T(1,47) == 2);
    return 0;
}