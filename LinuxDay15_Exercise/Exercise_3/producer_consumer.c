#include <nofish_header.h>

#define MAX_SIZE 20
#define PRODUCER_NUM 2
#define CONSUMER_NUM 3
static int commodities = 10;
pthread_cond_t cond_t_producer;
pthread_cond_t cond_t_consumer;
pthread_mutex_t mutex_t;

void *produce(void *arg){
    while(1) {
        pthread_mutex_lock(&mutex_t);
        while(commodities >= MAX_SIZE){
            pthread_cond_wait(&cond_t_producer, &mutex_t);
        }
        commodities++;
        printf("producer %ld produce 1 commoditiy\n", (long)arg);
        printf("total commodities: %d\n", commodities);
        pthread_cond_signal(&cond_t_consumer);
        pthread_mutex_unlock(&mutex_t);
        sleep(3);
    }
    pthread_exit(&mutex_t);
}

void *consume(void *arg){
    sleep(5);
    while(1) {
        pthread_mutex_lock(&mutex_t);
        while(commodities <= 0){
            pthread_cond_wait(&cond_t_consumer, &mutex_t);
        }
        commodities--;
        printf("consumer %ld consume 1 commoditiy\n", (long)arg);
        printf("total commodities: %d\n", commodities);
        pthread_cond_signal(&cond_t_producer);
        pthread_mutex_unlock(&mutex_t);
        sleep(1);
    }
    pthread_exit(&mutex_t);
}

int main(int argc, char** argv)
{
    int res;
    pthread_t producer[PRODUCER_NUM];
    pthread_t consumer[CONSUMER_NUM];

    pthread_cond_init(&cond_t_producer, NULL);
    pthread_cond_init(&cond_t_consumer, NULL);
    pthread_mutex_init(&mutex_t, NULL);

    printf("**********Welcome**********\n");
    printf("total commodities: %d\n", commodities);
    for(int i = 0; i < PRODUCER_NUM; i++){
        res = pthread_create(&(producer[i]), NULL, produce, (void *)(long)(i + 1));
        THREAD_ERROR_CHECK(res, "pthread_create");
    }
    for(int j = 0; j < CONSUMER_NUM; j++){
        res = pthread_create(&(consumer[j]), NULL, consume, (void *)(long)(j + 1));
        THREAD_ERROR_CHECK(res, "pthread_create");
    }


    for(int i = 0; i < PRODUCER_NUM; i++){
        pthread_join(producer[i], NULL);
        sleep(1);
    }
    for(int j = 0; j < CONSUMER_NUM; j++){
        pthread_join(consumer[j], NULL);
        sleep(1);
    }

    pthread_cond_destroy(&cond_t_producer);
    pthread_cond_destroy(&cond_t_consumer);
    pthread_mutex_destroy(&mutex_t);

    return 0;
}


