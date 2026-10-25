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

// Nhan hai da thuc trong GF(2^8)
int nhan_gf2_8(int a, int b) {
    int ket_qua = 0;

    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            ket_qua ^= a;
        }

        b >>= 1;
        a <<= 1;

        if (a >= 256) {
            a ^= 0x11B;
        }
    }

    return ket_qua;
}

int main(void) {
    int a4 = 0x5, b4 = 0xB;
    int a8 = 0x26, b8 = 0x9E;

    printf("GF(2^4): 0x%X\n", nhan_gf2_4(a4, b4));
    printf("GF(2^8): 0x%X\n", nhan_gf2_8(a8, b8));

    return 0;
}
