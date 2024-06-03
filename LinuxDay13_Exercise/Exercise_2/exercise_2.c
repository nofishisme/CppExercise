#include <nofish_header.h>

void* func1(void *arg){
    printf("This is thread1 func1.\n");
    sleep(1);
    pthread_exit((void *)1);
}

void* func2(void *arg){
    printf("This is thread2 func2.\n");
    sleep(1);
    pthread_exit((void *)2);
}

void* func3(void *arg){
    printf("This is thread3 func3.\n");
    sleep(1);
    pthread_exit((void *)3);
}

int main(int argc, char** argv)
{
    pthread_t thread_1;
    pthread_t thread_2;
    pthread_t thread_3;

    void *result1;
    void *result2;
    void *result3;

    pthread_create(&thread_1, NULL, func1, NULL);
    pthread_create(&thread_2, NULL, func2, NULL);
    pthread_create(&thread_3, NULL, func3, NULL);

    pthread_join(thread_1, &result1);
    pthread_join(thread_2, &result2);
    pthread_join(thread_3, &result3);

    printf("thread_1 exit stat is: %ld\n", (long)result1);
    printf("thread_2 exit stat is: %ld\n", (long)result2);
    printf("thread_3 exit stat is: %ld\n", (long)result3);

    return 0;
}


