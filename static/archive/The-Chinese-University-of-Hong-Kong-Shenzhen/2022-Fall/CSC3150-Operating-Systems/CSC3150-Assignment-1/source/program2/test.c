#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int i = 0;

        printf("--------USER PROGRAM--------\n");
        raise(SIGBUS);
        sleep(5);
        printf("user process success!!\n");
        printf("--------USER PROGRAM--------\n");
        return 0;
}