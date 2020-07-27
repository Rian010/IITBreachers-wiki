#include <stdio.h>
#include <stdlib.h>

void win() {
    system("cat flag.txt");
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
    
    char inp[8];

    puts("Hello there! Happy pwning and calling fns:)");
    gets(inp);
}