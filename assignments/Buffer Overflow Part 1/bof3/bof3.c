#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
    
    unsigned int x = 0;
    char inp[8];

    puts("Ain't you a sweet n00b to be here :P");
    gets(inp);
    if (x == 0xdeadbeef) {
        puts("flag{fake_flag_lol}");
    }
}