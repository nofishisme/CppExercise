#include <nofish_header.h>

#define THREAD_SIZE 2
pthread_mutex_t a_mutex;
static int total_ticket = 20;
static int flag = 0;

void *sale_for_ticket(void *arg){
    while(1) {
        sleep(1);
        srand(time(NULL));
        int buy_or_not = rand() % 10;
        //小于5表示要买票
        if(buy_or_not < 5){
            pthread_mutex_lock(&a_mutex);
            if(total_ticket > 0) {
                //确保第一次小于5一定加票
                while(total_ticket < 5 && flag == 0) {
                    pthread_mutex_unlock(&a_mutex);
                    sleep(1);
                    pthread_mutex_lock(&a_mutex);
                }
                total_ticket--;
                printf("sell 1 ticket, ticket left: %d\n", total_ticket);
                if(total_ticket == 0) {
                    printf("all tickets has sold out.\n");
                    pthread_mutex_unlock(&a_mutex);
                    break;
                }
            }else{
                printf("all tickets has sold out.\n");
                pthread_mutex_unlock(&a_mutex);
                break;
            }
            pthread_mutex_unlock(&a_mutex);
        }
    }
    pthread_exit(NULL);
}

void *add_ticket(void *arg){
    while(1){
        pthread_mutex_lock(&a_mutex);
        if(total_ticket < 5){
            printf("add 10 tickets for total_ticket.\n");
            printf("total_ticket: %d\n", total_ticket);
            total_ticket += 10;
            pthread_mutex_unlock(&a_mutex);
            flag = 1;
            break;
        }
        pthread_mutex_unlock(&a_mutex);
        sleep(1);
    }
    pthread_exit(NULL);

}

int main(int argc, char** argv)
{
    int res;
    pthread_t a_thread1;
    pthread_t a_thread2;

    printf("tickets on sale ......\n");
    printf("total_ticket: %d\n", total_ticket);
    res = pthread_create(&a_thread1, NULL, sale_for_ticket, NULL);
    THREAD_ERROR_CHECK(res, "pthread_create1");
    res = pthread_create(&a_thread2, NULL, add_ticket, NULL);
    THREAD_ERROR_CHECK(res, "pthread_create1");

    pthread_join(a_thread1, NULL);
    pthread_join(a_thread2, NULL);

    printf("Done!\n");

    return 0;
}


