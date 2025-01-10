#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int32_t b32; // bool
typedef enum {false = 0, true = 1} __bool;

typedef struct {
    int x;
    int y;
} V2;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} Color;

typedef struct {
    int width;
    int height;
    Color *pixels;
} Bitmap;

typedef struct {
    // File Header
    u8 type[2];
    u32 file_size;
    u16 reserved_1;
    u16 reserved_2;
    u32 pixel_data_offset;
    // Info header
    u32 info_header_size;
    i32 image_width;
    i32 image_height;
    u16 planes;
    u16 bit_count;
    u32 compression;
    u32 pixel_data_size;
    u64 resolution;
    u32 color_index;
    u32 important_colors;
    char *data;
} BitmapRawData;

typedef struct { u8 offset; u8 size; } SizeOffset;

static SizeOffset Type            = {0,  2};
static SizeOffset FileSize        = {2,  4};
static SizeOffset Reserved1       = {6,  2};
static SizeOffset Reserved2       = {8,  2};
static SizeOffset PixelDataOffset = {10, 4};
static SizeOffset InfoHeaderSize  = {14, 4};
static SizeOffset ImageWidth      = {18, 4};
static SizeOffset ImageHeight     = {22, 4};
static SizeOffset Planes          = {26, 2};
static SizeOffset BitCount        = {28, 2};
static SizeOffset Compression     = {30, 4};
static SizeOffset PixelDataSize   = {34, 4};
static SizeOffset Resolution      = {38, 8};
static SizeOffset ColorIndex      = {46, 4};
static SizeOffset ImportantColors = {50, 4};

static char *PrintColorCharacterSet = "  ";

void print_color(u8 red, u8 green, u8 blue)
{
    printf("\033[48;2;%d;%d;%dm%s\033[0m", red, green, blue, PrintColorCharacterSet);
}

void print_bitmap(BitmapRawData bitmap)
{
    char *offset  = bitmap.data + bitmap.file_size; // go to end of data
    u8 padding    = bitmap.image_width % 4;
    u8 pixel_byte = bitmap.bit_count / 8;
    offset -= pixel_byte + padding; // go to first pixel data backwards
    for (int y = bitmap.image_height; y > 0; y--) {
        for (int x = bitmap.image_width; x > 0; x--) {
            print_color(offset[2], offset[1], offset[0]); 
            offset -= pixel_byte;
        }
        printf("\n");
        offset -= padding;
    }
}

BitmapRawData read_bitmap_data(char *data)
{
    BitmapRawData map = {0};
    if (data[0] != 'B' || data[1] != 'M') {
        printf("read_bitmap_file: file header bftype \"%c%c\" does not match expected header \"BM\", aborting.\n", data[0], data[1]);
        return (map);
    }
    memcpy(&map.type,              &data[Type.offset],            Type.size);
    memcpy(&map.file_size,         &data[FileSize.offset],        FileSize.size);
    memcpy(&map.reserved_1,        &data[Reserved1.offset],       Reserved1.size);
    memcpy(&map.reserved_2,        &data[Reserved2.offset],       Reserved2.size);
    memcpy(&map.pixel_data_offset, &data[PixelDataOffset.offset], PixelDataOffset.size);
    memcpy(&map.info_header_size,  &data[InfoHeaderSize.offset],  InfoHeaderSize.size);
    memcpy(&map.image_width,       &data[ImageWidth.offset],      ImageWidth.size);
    memcpy(&map.image_height,      &data[ImageHeight.offset],     ImageHeight.size);
    memcpy(&map.planes,            &data[Planes.offset],          Planes.size);
    memcpy(&map.bit_count,         &data[BitCount.offset],        BitCount.size);
    memcpy(&map.compression,       &data[Compression.offset],     Compression.size);
    memcpy(&map.pixel_data_size,   &data[PixelDataSize.offset],   PixelDataSize.size);
    memcpy(&map.resolution,        &data[Resolution.offset],      Resolution.size);
    memcpy(&map.color_index,       &data[ColorIndex.offset],      ColorIndex.size);
    memcpy(&map.important_colors,  &data[ImportantColors.offset], ImportantColors.size);
    map.data = data;
    
    printf("type: %c%c \n", map.type[0], map.type[1]);
    printf("file_size: %d \n", map.file_size);
    printf("reserved_1: %d \n", map.reserved_1);
    printf("reserved_2: %d \n", map.reserved_2);
    printf("pixel_data_offset: %d \n", map.pixel_data_offset);
    printf("image size: %d, %d \n", map.image_width, map.image_height);
    return (map);
}

void write_bitmap_file(BitmapRawData bmp, char *path)
{
    FILE *file = fopen(path, "w+");
    if (!file) {
        printf("write_bitmap_file(\"%s\"): %s\n", path, strerror(errno));
        return ;
    }
    fwrite(&bmp.type,                        Type.size,            1, file);
    fwrite(&bmp.file_size,                   FileSize.size,        1, file);
    fwrite(&bmp.reserved_1,                  Reserved1.size,       1, file);
    fwrite(&bmp.reserved_2,                  Reserved2.size,       1, file);
    fwrite(&bmp.pixel_data_offset,           PixelDataOffset.size, 1, file);
    fwrite(&bmp.info_header_size,            InfoHeaderSize.size,  1, file);
    fwrite(&bmp.image_width,                 ImageWidth.size,      1, file);
    fwrite(&bmp.image_height,                ImageHeight.size,     1, file);
    fwrite(&bmp.planes,                      Planes.size,          1, file);
    fwrite(&bmp.bit_count,                   BitCount.size,        1, file);
    fwrite(&bmp.compression,                 Compression.size,     1, file);
    fwrite(&bmp.pixel_data_size,             PixelDataSize.size,   1, file);
    fwrite(&bmp.resolution,                  Resolution.size,      1, file);
    fwrite(&bmp.color_index,                 ColorIndex.size,      1, file);
    fwrite(&bmp.important_colors,            ImportantColors.size, 1, file);
    fwrite(&bmp.data[bmp.pixel_data_offset], bmp.pixel_data_size,  1, file);
    fclose(file);
}

BitmapRawData read_bitmap_file(char *path) 
{
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("read_bitmap_file(\"%s\"): %s\n", path, strerror(errno));
        return ((BitmapRawData) {0});
    }
    char *contents = 0;
    int contents_size = 0;
    fseek(file, 0, SEEK_END);
    contents_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    contents = calloc(contents_size + 1, sizeof(char));
    fread(contents, contents_size, 1, file);
    fclose(file);
    return (read_bitmap_data(contents));
}

BitmapRawData generate_raw_bitmap(Bitmap bitmap)
{
    BitmapRawData raw = {0};

    return (raw);
}

Bitmap create_bitmap(int width, int height)
{
    Bitmap bitmap = {0};
    bitmap.width = width;
    bitmap.height = height;
    bitmap.pixels = calloc(width * height, sizeof(Color));
    return (bitmap);
}

void clear_background(Bitmap *bitmap, Color color)
{
    for (int i = bitmap->width * bitmap->height - 1; i >= 0; i++) {
        bitmap->pixels[i] = color;
    }
}

void draw_rectangle(Bitmap *bitmap, V2 pos, V2 size, Color color)
{
}

#define flag_compare(flag, ...) strcmp_many(flag, ((const char*[]){__VA_ARGS__}), (sizeof((const char*[]){__VA_ARGS__})/sizeof(const char*)))
b32 strcmp_many(const char *str, const char **str_many, i32 str_many_count)
{
	for (i32 i = 0; i < str_many_count; i++) {
		if (!strcmp(str, str_many[i])) return (true);
	}
	return (false);
}

char *shift_args(int *argc, char ***argv)
{
    if (*argc < 0) return (NULL);
    char *result = **argv;
    (*argv) += 1;
    (*argc) -= 1;
    return result;
}

int main(int argc, char **argv)
{
    if (argc <= 1 || flag_compare(argv[1], "-h", "-help", "--help")) {
        printf("Please provide an bpm image path to display \n");
        printf(" Program [options] bmp_files \n");
        printf("-c <characters> to change printing. \n");
        printf("-g [save_path] generate exercise images. \n");
        return (0);
    }
    shift_args(&argc, &argv);
    
    char *arg = shift_args(&argc, &argv);
    if (flag_compare(arg, "-c")) {
        PrintColorCharacterSet = shift_args(&argc, &argv);
    }

    if (flag_compare(arg, "-g")) {
        char *path = shift_args(&argc, &argv);
        if (path == NULL) path = "./";
        printf("path: %s\n", path);
        BitmapRawData bitmap = read_bitmap_file(path);
        write_bitmap_file(bitmap, "./teste");
    } 
    // Print every image path provided
    else {
        // TODO  Read until no more args, print everything
        printf("aa %s\n", argv[0]);
        BitmapRawData bitmap = read_bitmap_file(arg);
        print_bitmap(bitmap);
        free(bitmap.data);
    }
    return (0);
}

