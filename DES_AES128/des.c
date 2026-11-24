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

    return 0;
}