#include <nofish_header.h>

pthread_cond_t cond_t_ab;
pthread_cond_t cond_t_ba;
pthread_mutex_t mutex_t;

void *thread_Func(void *arg){
    while(1){
        pthread_cond_wait(&cond_t_ab, &mutex_t);
        printf("Before B!\n");
        sleep(3);
        printf("After B\n");
        pthread_cond_signal(&cond_t_ba);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    pthread_t thread_t;

    pthread_mutex_init(&mutex_t, NULL);
    pthread_cond_init(&cond_t_ab, NULL);
    pthread_cond_init(&cond_t_ba, NULL);
    pthread_create(&thread_t, NULL, thread_Func, NULL);

    while(1){
        printf("Before A!\n");
        sleep(3);
        printf("After A\n");
        pthread_cond_signal(&cond_t_ab);
        pthread_cond_wait(&cond_t_ba, &mutex_t);
    }

    pthread_join(thread_t, NULL);
    return 0;
}


