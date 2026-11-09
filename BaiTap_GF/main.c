
#include <stdio.h>

// Nhan hai da thuc trong GF(2^4)
int nhan_gf2_4(int a, int b) {
    int ket_qua = 0;

    for (int i = 0; i < 4; i++) {
        if (b & 1) {
            ket_qua ^= a;
        }

        b >>= 1;
        a <<= 1;

        if (a >= 16) {
            a ^= 0x13;
        }
    }

    return ket_qua;
}

int main(void) {
    int a = 0x5;
    int b = 0xB;

    printf("GF(2^4): 0x%X\n", nhan_gf2_4(a, b));

    return 0;
}
