#include "stdio.h"

char *to_byte(char c)
{
    static char buf[9] = {0};
    for (int i = 0; i < 8; i++) {
        int bit = (c >> i) & 0b00000001;
        if (bit) buf[7-i] = '1';
        else buf[7-i] = '0';
    }
    return &buf[0];
}

char *to_hex(char c)
{
    char index[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    static char buf[3] = {0};
    int low = c & 0b00001111;
    int high = c & 0b11110000;
    buf[0] = index[high/ 16];
    buf[1] = index[low % 16];
    return &buf[0];
}

int main()
{
    char buf[40] = {0};
    buf[0] = 0b01001101;
    buf[1] = 0x79;
    buf[2] = 0b00100000;
    buf[3] = 0b01101110;
    buf[4] = 0x61;
    buf[5] = 0x6D;
    buf[6] = 0b01100101;
    buf[7] = 0x20;
    buf[8] = 0x69;
    buf[9] = 0x73;
    buf[10] = 0b00101110;
    buf[11] = '.';
    buf[12] = 0b00101110;
    buf[13] = 0b00100000;
    buf[14] = 'T';
    buf[15] = 'h';
    buf[16] = 'o';
    buf[17] = 'm';
    buf[18] = 'i';

    printf("%s \n", to_hex(0b00000111));

    for (int i = 0; buf[i]; i++) {
        printf("%c  %d   %s  %s\n", buf[i], buf[i], to_hex(buf[i]), to_byte(buf[i]));
    }
}



