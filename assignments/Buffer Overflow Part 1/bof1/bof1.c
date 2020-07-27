#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
    int val = 0;
    char inp[8];

    puts("Hey there! Hope you know how to do stuff :)");
    gets(inp);
    if (val != 0) {
        puts("flag{fake_flag_lol}");
    }
}
