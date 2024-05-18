#include <nofish_header.h>

pthread_cond_t t_cond_ab;
pthread_cond_t t_cond_bc;
pthread_mutex_t t_mutex;
static int flag = 0;

void *thread_Func1(void *arg){
    while(1) {
        printf("---->A\n");
        while(!flag){
            pthread_cond_signal(&t_cond_ab);
        }
        pthread_cond_wait(&t_cond_bc, &t_mutex);
        flag = 0;
        printf("---->C\n");
        /* sleep(1); */
    }
    pthread_exit(NULL);
}

void *thread_Func2(void *arg){
    while(1) {
        pthread_cond_wait(&t_cond_ab, &t_mutex);
        flag = 1;
        printf("---->B\n");
        while(flag){
            pthread_cond_signal(&t_cond_bc);
        }
        /* sleep(1); */
    }
    pthread_exit(NULL);
}
int main(int argc, char** argv)
{
    int res;
    pthread_t thread_t1;
    pthread_t thread_t2;

    pthread_cond_init(&t_cond_ab, NULL);
    pthread_cond_init(&t_cond_bc, NULL);
    pthread_mutex_init(&t_mutex, NULL);

    res = pthread_create(&thread_t1, NULL, thread_Func1, NULL);
    THREAD_ERROR_CHECK(res,"pthread_create1 error.\n");
    res = pthread_create(&thread_t2, NULL, thread_Func2, NULL);
    THREAD_ERROR_CHECK(res,"pthread_create2 error.\n");

    pthread_join(thread_t1, NULL);
    pthread_join(thread_t2, NULL);

    pthread_cond_destroy(&t_cond_ab);
    pthread_cond_destroy(&t_cond_bc);
    pthread_mutex_destroy(&t_mutex);

    return 0;
}


