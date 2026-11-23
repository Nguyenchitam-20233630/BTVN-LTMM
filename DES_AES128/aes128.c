#include<stdio.h>
#include<stdint.h>
int main(void){
    uint8_t p[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11};
    uint8_t k[16] = {0};
    printf("Ban ro p: ");
    for(int i = 0; i < 16; i ++){
        printf("%02X", p[i]);
    }
    printf("\nKhoa k: ");
    for(int i = 0; i < 16; i ++){
        printf("%02X", k[i]);
    }
    printf("\n");

    uint8_t state[16];

for (int i = 0; i < 16; i++) {
    state[i] = p[i];
}

printf("State ban dau:\n");

for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
        printf("%02X ", state[4 * c + r]);
    }
    printf("\n");
}
for (int i = 0; i < 16; i++) {
    state[i] = state[i] ^ k[i];
}
printf("State sau AddRoundKey ban dau:\n");

for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
        printf("%02X ", state[4 * c + r]);
    }
    printf("\n");
}
    return 0;
}
