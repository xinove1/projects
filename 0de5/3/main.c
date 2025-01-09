#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int str_copy_into(char *dst, char *src, int dst_pos, int dst_len)
{
    int src_len = strlen(src);
    if (dst_len - dst_pos <= src_len) {
        printf("INFO: str_copy_into: not enough space on dst to fully copy.");
    }
    for (int i = 0; i < src_len && dst_pos < dst_len;) {
        dst[dst_pos] = src[i];
        i++;
        dst_pos++;
    }
    return dst_pos;
}

char *itoa(int number)
{
    char index[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    static char buf[50] = {0};
    memset(&buf[0], 0, 50);
    int places = 0;
    for (int n = number; n; n = n / 10) {places++;}
    places--;
    while (places < 50 && number) {
        buf[places] = index[number % 10];
        number = number / 10;
        places--;
    }
    return &buf[0];
}

char *fizzbuzz(int qty)
{
    char *buf = calloc(qty * 10, sizeof(char));
    int buf_i = 0;
    for (int i = 1; i < qty; i++) {
        if ( i % 3 == 0 && i % 5 == 0 ) {
            buf_i = str_copy_into(buf, "FizzBuzz", buf_i, qty * 10);
        }
        else if ( i % 3 == 0 ) {
            buf_i = str_copy_into(buf, "Fizz", buf_i, qty * 10);
        }
        else if ( i % 5 == 0 ) {
            buf_i = str_copy_into(buf, "Buzz", buf_i, qty * 10);
        }
        else {
            buf_i = str_copy_into(buf, itoa(i), buf_i, qty * 10);
        }
        
        buf_i = str_copy_into(buf, ", ", buf_i, qty * 10);
    }
    return buf;
}

char *prime_number(int qty)
{
    int *arr = calloc(qty, sizeof(qty));
    for (int i = 0; i < qty; i++) arr[i] = i+1;
    
    for (int i = 1; i < qty; i++) {
        if (arr[i] == 0) continue;
        for (int k = i + 1; k < qty; k++) {
            if (arr[k] == 0) continue;
            if (arr[k] % arr[i] == 0) {
                arr[k] = 0;
            }
        }
    }
    int buf_size = 0;
    for (int i = 0; i < qty; i++){
        if (arr[i] != 0) {
            buf_size += 10;
        }
    }
    char *buf = calloc(buf_size, sizeof(char));
    int k = 0;
    for (int i = 0; i < qty; i++){
        if (arr[i] != 0) {
            k = str_copy_into(buf, itoa(arr[i]), k, buf_size);
            k = str_copy_into(buf, ", ", k, buf_size);
        }
    }
    free(arr); 
    return buf;
}

int get_decimal_place(int number, int place)
{
    return (number % (int)pow(10, place)) / (int)pow(10, place - 1);
}

char *number_written(int number)
{
    char *number_index[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *places_index[] = {"hundred", "thousand", "milion", "bilion"};
    // 123.098.998
    // 876 543 210

    int places = 0;
    for (int n = number; n; n = n / 10) { places++; }
    printf("%d\n", get_decimal_place(number, places));
    int remainder = places % 3;
    places -= remainder;
    while (places) {
        int trio[3] = {0};
        printf("place: %d\n", places);
        printf("%s\n", places_index[places/3 - 1]);
        trio[0] = get_decimal_place(number, places);
        trio[1] = get_decimal_place(number, places-1);
        trio[2] = get_decimal_place(number, places-2);

        printf("%s ", number_index[trio[0]]);
        printf("%s ", number_index[trio[1]]);
        printf("%s ", number_index[trio[2]]);

        //number = number / 10;
        places -= 3;
    }

    return "a";
}

int main() 
{
    printf("%s \n", number_written(1230989));
}
