#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
    uint64_t p = UINT64_C(0x0123456789ABCDEF);
    uint64_t k = UINT64_C(0x133457799BBCDFF1);

    printf("Ban ro P: %016" PRIX64 "\n", p);
    printf("Khoa K:   %016" PRIX64 "\n", k);

    return 0;
}