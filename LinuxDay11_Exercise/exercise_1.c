#include <nofish_header.h>


int main(int argc, char** argv)
{
    printf("current real process uid: %d\n", getuid());
    printf("current real process group uid: %d\n", getgid());
    printf("current effective process uid: %d \n", geteuid());
    printf("current effective process group uid: %d \n", getegid());

    while(1){

    }
    return 0;
}


