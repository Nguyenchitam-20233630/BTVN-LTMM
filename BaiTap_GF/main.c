
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

    int ket_qua = nhan_gf2_4(a, b);

    printf("Bat dau chuong trinh GF(2^4)\n");
    printf("a = 0x%X\n", a);
    printf("b = 0x%X\n", b);
    printf("Ket qua: 0x%X\n", ket_qua);

    return 0;
}
