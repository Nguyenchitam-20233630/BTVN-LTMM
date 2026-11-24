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
uint64_t hoan_vi_ip(uint64_t input)
{
    uint64_t output = 0;

    for (int i = 0; i < 64; i++) {
        uint64_t bit = (input >> (64 - IP[i])) & UINT64_C(1);

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
    return 0;
}