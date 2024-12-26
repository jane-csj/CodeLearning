/***
* @Author: 
* @Date: 2024-11-14 15:37:12
* @LastEditTime: 2024-11-14 16:30:11
* @Description: 并发版 find
 */

#include <thread>
#include <algorithm>
#include <future>
#include <vector>
#include <iostream>

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


template<typename Iterator, typename Match>
Iterator parallel_find(Iterator first, Iterator last, Match match){
    struct find_element{
        void operator()(Iterator begin, Iterator end, 
        Match match, 
        std::promise<Iterator>* result_promise, 
        std::atomic<bool>* done_flag)
        {
            try{
                for(; begin != end && !done_flag->load(); ++begin){
                    if(*begin == match){
                        result_promise->set_value(begin);
                        done_flag->store(true);
                        return;
                    }
                }
            }catch(...){
                try{
                    result_promise->set_exception(std::current_exception());
                    done_flag->store(true);
                }catch(...){}

            }
        }
    };
    unsigned long const length = std::distance(first, last);
    if(!length) return last;
    unsigned long const min_pre_thread = 25;
    unsigned long const max_threads = (length+min_pre_thread-1)/min_pre_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size = (length+num_threads-1)/num_threads;
    std::vector<std::thread> threads(num_threads);
    std::atomic<bool> done_flag(false);
    std::promise<Iterator> result;
    {
        join_threads joiner(threads);
        Iterator block_start = first;
        for(unsigned long i=0;i<num_threads - 1;++i){
            Iterator block_end = block_start;
            std::advance(block_end,block_size);
            threads[i] = std::thread(find_element(), 
                                    block_start, block_end, match, 
                                    &result, &done_flag);
            block_start = block_end;
        }
        find_element()(block_start, last, match, &result, &done_flag);
        if(!done_flag.load()){
            return last;
        }
        return result.get_future().get();
    }
}
template<typename Iterator, typename Match>
Iterator parallel_find_async_Impl(Iterator first, Iterator last, Match match, std::atomic<bool>& done_flag){
    try
    {
        unsigned long const length = std::distance(first, last);
        
        unsigned long const min_per_thread = 25000;
        if(length < (2 * min_per_thread)){
            for(; (first != last) && !done_flag.load(); ++first){
                if(*first == match){
                    done_flag = true;
                    return first;
                }
            }
            return last;
        }else{
            Iterator const mid_point = first + length / 2;
            std::future<Iterator> async_result = std::async(
                &parallel_find_async_Impl<Iterator, Match>, mid_point, 
                last, match, std::ref(done_flag)
            );
            Iterator const direct_result = parallel_find_async_Impl(first, mid_point, match, done_flag);
            return (direct_result == mid_point) ?
                async_result.get() : direct_result;
        }
    }
    catch(...)
    {
        done_flag = true;
        throw;
    }
    
}
template<typename Iterator, typename Match>
Iterator parallel_find_async(Iterator first, Iterator last, Match match){
    std::atomic<bool> done_flag(false);
    return parallel_find_async_Impl(first, last, match, done_flag);
}
std::vector<int> data(1000000);
void Test_find_element(){
    for(int i = 0; i < data.size(); ++i){
        data[i] = i;
    }
    // 计时
    auto start = std::chrono::high_resolution_clock::now();
    auto res_iterator =  parallel_find(data.begin(), data.end(), 9999999);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    std::cout << "found at: " << res_iterator - data.begin() << std::endl;
}

void Test_find_element_async(){
    for(int i = 0; i < data.size(); ++i){
        data[i] = i;
    }
    // 计时
    auto start = std::chrono::high_resolution_clock::now();
    auto res_iterator =  parallel_find_async(data.begin(), data.end(), 9999999);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    std::cout << "found at: " << res_iterator - data.begin() << std::endl;
}
int main(){
    Test_find_element();
    Test_find_element_async();
    system("pause");
}
