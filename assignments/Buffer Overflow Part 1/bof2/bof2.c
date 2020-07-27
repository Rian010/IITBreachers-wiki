#include <stdio.h>
#include <string.h>

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
    
    char check[8];
    char inp[8];

    puts("Happy pwning n0000b :D");
    gets(inp);
    if (strncmp(check,"hello_me",8) == 0) {
        puts("flag{fake_flag_lol}");
    }
}