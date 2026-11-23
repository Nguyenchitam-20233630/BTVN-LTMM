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
    return 0;
}
