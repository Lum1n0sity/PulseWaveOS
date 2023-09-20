#include <stdio.h>

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

void my_putchar(char c) 
{
    volatile char *video_memory = (volatile char *)VIDEO_ADDRESS;
    *video_memory = c;
}

void clear_screen() 
{
    volatile char *video_memory = (volatile char *)VIDEO_ADDRESS;
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) 
    {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = WHITE_ON_BLACK;
    }
}

void my_puts(const char *str) 
{
    for (int i = 0; str[i] != '\0'; i++) 
    {
        my_putchar(str[i]);
    }
}

void kernel_main() 
{
    clear_screen();

    my_puts("Hello from the Kernel\n");

    my_puts("Starting kernel_main...\n");
}

void _kernel_start()
{
    my_puts("Kernel started!\n");

    kernel_main();

    while(1){}
}