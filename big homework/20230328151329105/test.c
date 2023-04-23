#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int N, M;
    printf("%s %s", argv[1], argv[2]);
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    printf("%d %d", N, M);
}
