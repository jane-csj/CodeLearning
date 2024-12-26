/***
* @Author: 
* @Date: 2024-11-13 18:22:11
* @LastEditTime: 2024-11-14 16:00:02
* @Description: 并发版 for_each
 */
#include <iostream>
#include <thread>
#include <algorithm>
#include <future>
#include <vector>
#include <random>

class join_threads{
    std::vector<std::thread>& threads;
public:
    explicit join_threads(std::vector<std::thread>& threads_):threads(threads_){}
    ~join_threads(){
        for(unsigned long i = 0; i < threads.size(); i++){
            if(threads[i].joinable())
                threads[i].join();
        }
    }
};


template<typename Iterator, typename Function>
void paraller_for_each(Iterator first, Iterator last, Function f){
    unsigned long const length = std::distance(first, last);
    if(length == 0) return;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;
    std::vector<std::thread> threads(num_threads - 1);
    join_threads joiner(threads);
    Iterator block_start = first;
    for(auto i = 0; i < num_threads - 1; i++){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        std::packaged_task<void(void)> task([=](){
           std::for_each(block_start, block_end, f);
        });
        threads[i] = std::thread(std::move(task));
        block_start = block_end;
    }
    std::for_each(block_start, last, f);
}

/*
 *      使用async实现并行版for_each
 */
template<typename Iterator, typename Func>
void paraller_for_each_async(Iterator first, Iterator last, Func f){
    unsigned long const length = std::distance(first, last);
    if(!length) return;
    unsigned long const min_per_thread = 25;
    if(length < 2 * min_per_thread){
        std::for_each(first, last, f);
    }else{
        Iterator const mid_point = first + length / 2;
        std::future<void> first_half = std::async(
            &paraller_for_each_async<Iterator, Func>, first, mid_point, f
        );
        paraller_for_each(mid_point, last, f);
        first_half.get();
    }
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 100);
std::vector<int> v(10000000);
void test_for_ecah(){
     std::generate(v.begin(), v.end(), [&](){return dis(gen);});
    auto start = std::chrono::high_resolution_clock::now();
    std::for_each(v.begin(), v.end(), [](int i){i *= 2;});
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "std for_each cost time: " << duration.count() << "ms" << std::endl;
}
void test_parallel(){
    std::generate(v.begin(), v.end(), [&](){return dis(gen);});
    auto start = std::chrono::high_resolution_clock::now();
    paraller_for_each(v.begin(), v.end(), [](int i){i *= 2;});
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "parallel for_each cost time: " << duration.count() << "ms" << std::endl;
}
void test_async(){
    std::generate(v.begin(), v.end(), [&](){return dis(gen);});
    auto start = std::chrono::high_resolution_clock::now();
    paraller_for_each_async(v.begin(), v.end(), [](int i){i *= 2;});
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "async for_each cost time: " << duration.count() << "ms" << std::endl;
}
int main(){
    test_for_ecah();
    test_parallel();
    test_async();
    system("pause");
}
