/***
* @Author: 
* @Date: 2024-10-29 01:30:59
* @LastEditTime: 2024-10-31 23:53:02
* @Description: 
 */
#include <atomic>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <functional>
#include <random>

#define LEFT (i + 4) % N
#define RIGHT (i + 1) % N
const int N = 5;
const int M = 1000;
std::condition_variable cvs[N];
enum State{
    THINKING,
    HUNGRY, 
    GOT_LEFT, 
    GOT_RIGHT, 
    EATING
};
static int timestamp=0;
static std::recursive_mutex _recursive_mtx;
static std::mutex _mtx;
std::random_device rd;
struct DiningPhilosophers
{
    bool chopsticks[N];
    State state[N];
}dp;
static void log_philosopher_state(int phil_id, State state){
    std::lock_guard<std::recursive_mutex> lock(_recursive_mtx);
    printf("[%03d] Philosopher[%d] %s\n",
           timestamp++,
           phil_id,
           state == THINKING ? "THINKING" :
           state == HUNGRY ? "HUNGRY" :
           state == GOT_LEFT ? "GOT_LEFT_CHOPSTICK" :
           state == GOT_RIGHT ? "GOT_RIGHT_CHOPSTICK" :
           "EATING");
    fflush(stdout);
}

// 检测哲学家是否可以拿起筷子
void test(int i, DiningPhilosophers &dp){
    
}
void pickup_chopsticks(int i, DiningPhilosophers &dp){
    // std::lock_guard<std::recursive_mutex> lock(_recursive_mtx);
    _recursive_mtx.lock();
    dp.state[i] = HUNGRY;
    log_philosopher_state(i, dp.state[i]);
    if(dp.state[i] == HUNGRY && 
    dp.state[LEFT] != EATING &&
    dp.state[RIGHT] != EATING){
        dp.state[i] = GOT_LEFT;
        log_philosopher_state(i, dp.state[i]);
        std::unique_lock<std::mutex> lock(_mtx);
        cvs[i].wait(lock, [&](){
            return dp.chopsticks[i] && dp.chopsticks[RIGHT];
        });
        dp.chopsticks[i]=false;
        dp.state[i] = GOT_RIGHT;
        dp.chopsticks[RIGHT]=false;
        log_philosopher_state(i, dp.state[i]);
        dp.state[i]=EATING;
        log_philosopher_state(i, dp.state[i]);
    }
    _recursive_mtx.unlock();
    
}
void pickdown_chopsticks(int i, DiningPhilosophers &dp){
    std::lock_guard<std::recursive_mutex> lock(_recursive_mtx);
    dp.chopsticks[i]=true;
    dp.chopsticks[RIGHT]=(true);
    dp.state[i] = THINKING;
    cvs[LEFT].notify_all();
    cvs[RIGHT].notify_all();
}
void philosopher(int i, DiningPhilosophers &dp){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100000);
    for(int j=0; j<M; j++){
        log_philosopher_state(i, THINKING);
        
        // int sec = dis(gen);
        int sec = rand() % 100000;
        std::this_thread::sleep_for(std::chrono::microseconds(sec));
        pickup_chopsticks(i, dp);
        // sec = dis(gen);
        sec = rand() % 100000;
        std::this_thread::sleep_for(std::chrono::microseconds(sec));
        pickdown_chopsticks(i, dp);
    }
}
void init(){
    for(int i = 0; i < N; i++){
        dp.chopsticks[i]=(true);
        dp.state[i] = THINKING;
    }
}
int main(){
    std::thread threads[N];
    int phil_ids[N];
    init();
    for(int i = 0; i < N; i++){
        phil_ids[i] = i;
        threads[i] = std::thread(philosopher, phil_ids[i], std::ref(dp));
    }
    for(int i =0; i < N; i++){
        if(threads[i].joinable()){
            threads[i].join();
        }
    }
    std::cout << "finished" << std::endl;
    std::cin.get();
}
