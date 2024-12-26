#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define M 1000
#define LEFT (i + 4) % N
#define RIGHT (i + 1) % N

// 状态定义
typedef enum {
    THINKING,    // 思考
    HUNGRY,      // 饥饿
    GOT_LEFT,    // 获得左筷子
    GOT_RIGHT,   // 获得右筷子
    EATING       // 就餐
} State;

// 全局变量
static int timestamp = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 需要实现的数据结构
typedef struct {
    // 在这里添加必要的数据结构
    // 例如：信号量数组、状态数组等
    sem_t chopsticks[N];
    State state[N];
} DiningPhilosophers;
void init_recursive_mutex(pthread_mutex_t *mutex) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}
// 打印哲学家状态的辅助函数
static void log_philosopher_state(int phil_id, State state) {
    pthread_mutex_lock(&mutex);
    printf("[%03d] Philosopher[%d] %s\n",
           timestamp++,
           phil_id,
           state == THINKING ? "THINKING" :
           state == HUNGRY ? "HUNGRY" :
           state == GOT_LEFT ? "GOT_LEFT_CHOPSTICK" :
           state == GOT_RIGHT ? "GOT_RIGHT_CHOPSTICK" :
           "EATING");
    fflush(stdout);
    pthread_mutex_unlock(&mutex);
}

// 检测哲学家是否可以拿起筷子
void test(int i, DiningPhilosophers* dp){
    if(dp->state[i] == HUNGRY && dp->state[LEFT] != EATING && dp->state[RIGHT] != EATING){
        dp->state[i] = GOT_LEFT;
        log_philosopher_state(i, GOT_LEFT);
        sem_wait(&dp->chopsticks[i]);
        dp->state[i] = GOT_RIGHT;
        sem_wait(&dp->chopsticks[RIGHT]);
        log_philosopher_state(i, GOT_RIGHT);
        dp->state[i] = EATING;
        // log_philosopher_state(i, EATING);
    }
}

// 需要实现的函数
void dining_init(DiningPhilosophers* dp) {
    // 初始化所需的数据结构
    // 例如：初始化信号量、状态数组等
    for(unsigned i = 0; i < N; i++){
        sem_init(&dp->chopsticks[i], 0, 1);
        dp->state[i] = THINKING;
    }
}

void dining_destroy(DiningPhilosophers* dp) {
    // 销毁所有数据结构
    // 例如：销毁信号量等
    for(unsigned i = 0; i < N; i++){
        sem_destroy(&dp->chopsticks[i]);
    }
}

void pickup_chopsticks(DiningPhilosophers* dp, int phil_id) {
    // 实现拿起筷子的逻辑
    // 1. 设置哲学家状态为饥饿
    // 2. 尝试获取左右筷子
    // 3. 正确记录状态变化
    pthread_mutex_lock(&mutex);
    dp->state[phil_id] = HUNGRY;
    test(phil_id, dp);
    
    pthread_mutex_unlock(&mutex);
}

void putdown_chopsticks(DiningPhilosophers* dp, int phil_id) {
    // 实现放下筷子的逻辑
    // 1. 释放筷子
    // 2. 更新状态
    pthread_mutex_lock(&mutex);
    dp->state[phil_id] = THINKING;
    log_philosopher_state(phil_id, THINKING);
    int i = phil_id;
    sem_post(&dp->chopsticks[i]);
    sem_post(&dp->chopsticks[RIGHT]);
    pthread_mutex_unlock(&mutex);
}

// 哲学家线程函数
void* philosopher(void* arg) {
    int i = *(int*)((void**)arg)[0];
    DiningPhilosophers* dp = (DiningPhilosophers*)((void**)arg)[1];
  
    int _pass;
    
    for (_pass = 0; _pass < M; _pass++) {
        // 思考
        log_philosopher_state(i, THINKING);
        usleep(rand() % 100000);
        
        pickup_chopsticks(dp, i);
        
        // 进餐
        log_philosopher_state(i, EATING);
        usleep(rand() % 100000);
        
        putdown_chopsticks(dp, i);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int phil_ids[N];
    DiningPhilosophers dp;
    init_recursive_mutex(&mutex);
    // 初始化
    dining_init(&dp);
    
    // 创建哲学家线程
    void* args[N][2];
    for (int i = 0; i < N; i++) {
        phil_ids[i] = i;
        args[i][0] = &phil_ids[i];
        args[i][1] = &dp;
        pthread_create(&threads[i], NULL, philosopher, args[i]);
    }
    
    // 结束线程
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // 清理资源
    dining_destroy(&dp);
    printf("Program finished.\n");
    
    return 0;
}
