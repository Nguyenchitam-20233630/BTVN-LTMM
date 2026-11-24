#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

static const int E[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};
uint64_t hoan_vi_ip(uint64_t input)
{
    uint64_t output = 0;

    for (int i = 0; i < 64; i++) {
        uint64_t bit = (input >> (64 - IP[i])) & UINT64_C(1);

        output = (output << 1) | bit;
    }

    return output;
}
uint64_t mo_rong_e(uint32_t input)
{
    uint64_t output = 0;

    for (int i = 0; i < 48; i++) {
        uint64_t bit =
            (input >> (32 - E[i])) & UINT32_C(1);

        output = (output << 1) | bit;
    }

    return output;
}
static const uint8_t SBOX[8][4][16] = {
    /* S1 */
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    /* S2 */
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    /* S3 */
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    /* S4 */
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    /* S5 */
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    /* S6 */
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    /* S7 */
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    /* S8 */
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};
static const int P[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};

uint32_t hoan_vi_p(uint32_t input)
{
    uint32_t output = 0;

    for (int i = 0; i < 32; i++) {
        uint32_t bit =
            (input >> (32 - P[i])) & UINT32_C(1);

        output = (output << 1) | bit;
    }

    return output;
}
uint32_t ham_f(uint32_t R, uint64_t khoa_con)
{
    uint64_t x = mo_rong_e(R);
    x = x ^ khoa_con;

    uint32_t ket_qua = 0;

    for (int i = 0; i < 8; i++) {
        int nhom = (int)((x >> (42 - 6 * i)) & 63);

        int bit_dau = nhom >> 5;
        int bit_cuoi = nhom & 1;

        int hang = bit_dau * 2 + bit_cuoi;
        int cot = (nhom >> 1) & 15;

        int gia_tri = SBOX[i][hang][cot];

        ket_qua = (ket_qua << 4) | gia_tri;
    }

    ket_qua = hoan_vi_p(ket_qua);

    return ket_qua;
}
static const int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};
uint64_t hoan_vi_pc1(uint64_t khoa)
{
    uint64_t ket_qua = 0;

    for (int i = 0; i < 56; i++) {
        uint64_t bit = (khoa >> (64 - PC1[i])) & 1;

        ket_qua = (ket_qua << 1) | bit;
    }

    return ket_qua;
}
uint32_t dich_vong_trai28(uint32_t x, int so_bit)
{
    for (int i = 0; i < so_bit; i++) {
        uint32_t bit_dau = (x >> 27) & 1;

        x = (x << 1) & 0x0FFFFFFF;

        x = x | bit_dau;
    }

    return x;
}
static const int PC2[48] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

static const int SO_DICH[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
uint64_t hoan_vi_pc2(uint64_t input)
{
    uint64_t ket_qua = 0;

    for (int i = 0; i < 48; i++) {
        uint64_t bit = (input >> (56 - PC2[i])) & 1;

        ket_qua = (ket_qua << 1) | bit;
    }

    return ket_qua;
}
int main(void)
{
    printf("Bang hoan vi IP:\n");

    for (int i = 0; i < 64; i++) {
        printf("%2d ", IP[i]);

        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
uint64_t input_thu = UINT64_C(1) << 6;
uint64_t output_thu = hoan_vi_ip(input_thu);

printf("Dau vao thu: %016" PRIX64 "\n", input_thu);
printf("Sau IP:      %016" PRIX64 "\n", output_thu);

uint32_t L0 = (uint32_t)(output_thu >> 32);
uint32_t R0 = (uint32_t)(output_thu & UINT64_C(0xFFFFFFFF));

printf("L0: %08" PRIX32 "\n", L0);
printf("R0: %08" PRIX32 "\n", R0);

uint64_t ER0 = mo_rong_e(R0);
printf("E(R0): %012" PRIX64 "\n", ER0);

uint32_t r_thu = UINT32_C(0x80000000);
printf("R thu:    %08" PRIX32 "\n", r_thu);
printf("E(R thu): %012" PRIX64 "\n", mo_rong_e(r_thu));

uint64_t khoa_con_thu = UINT64_C(0x000000000001);
uint64_t e_thu = mo_rong_e(r_thu);
uint64_t sau_xor = e_thu ^ khoa_con_thu;

printf("E thu:        %012" PRIX64 "\n", e_thu);
printf("Khoa con thu: %012" PRIX64 "\n", khoa_con_thu);
printf("Sau XOR:      %012" PRIX64 "\n", sau_xor);

uint8_t nhom[8];

for (int i = 0; i < 8; i++) {
    nhom[i] = (uint8_t)((sau_xor >> (42 - 6 * i)) & 0x3F);

    printf("Nhom S%d: ", i + 1);

    for (int j = 5; j >= 0; j--) {
        printf("%u", (unsigned)((nhom[i] >> j) & 1));
    }

    printf("\n");
}
uint32_t sau_sbox = 0;

for (int i = 0; i < 8; i++) {
    uint8_t hang =
        (uint8_t)(((nhom[i] >> 4) & 0x02) |
                  (nhom[i] & 0x01));

    uint8_t cot =
        (uint8_t)((nhom[i] >> 1) & 0x0F);

    uint8_t gia_tri = SBOX[i][hang][cot];

    printf("S%d: hang = %u, cot = %u, dau ra = %X\n",
           i + 1,
           (unsigned)hang,
           (unsigned)cot,
           (unsigned)gia_tri);

    sau_sbox = (sau_sbox << 4) | gia_tri;
}

printf("Sau 8 S-box: %08" PRIX32 "\n", sau_sbox);
uint32_t sau_p = hoan_vi_p(sau_sbox);

printf("Sau hoan vi P: %08" PRIX32 "\n", sau_p);
uint32_t F = ham_f(R0, khoa_con_thu);

uint32_t L1 = R0;
uint32_t R1 = L0 ^ F;

printf("Ket qua ham F: %08" PRIX32 "\n", F);
printf("L1: %08" PRIX32 "\n", L1);
printf("R1: %08" PRIX32 "\n", R1);
uint64_t khoa_thu_pc1 = UINT64_C(1) << 7;
uint64_t khoa56 = hoan_vi_pc1(khoa_thu_pc1);

uint32_t C0 = (uint32_t)(khoa56 >> 28);
uint32_t D0 = (uint32_t)(khoa56 & 0x0FFFFFFF);

printf("Khoa thu PC1: %016" PRIX64 "\n", khoa_thu_pc1);
printf("Sau PC1:      %014" PRIX64 "\n", khoa56);
printf("C0: %07" PRIX32 "\n", C0);
printf("D0: %07" PRIX32 "\n", D0);
uint32_t C1 = dich_vong_trai28(C0, 1);
uint32_t D1 = dich_vong_trai28(D0, 1);

printf("C1: %07" PRIX32 "\n", C1);
printf("D1: %07" PRIX32 "\n", D1);
uint64_t keys_des[16];

sinh_khoa_des(khoa_thu_pc1, keys_des);

printf("\n16 khoa con tu khoa thu:\n");

for (int i = 0; i < 16; i++) {
    printf("K%02d: %012" PRIX64 "\n", i + 1, keys_des[i]);
}
    return 0;
}