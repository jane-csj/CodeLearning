/***
* @Author: 
* @Date: 2024-10-29 01:30:59
* @LastEditTime: 2024-11-06 01:32:17
* @Description: 
 */
#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T>
class threadsafe_queue_ptr{
private:
    mutable std::mutex mtx;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue_ptr(){}
    void wait_and_pop(T& value){
        std::unique_lock<std::mutex> lock(mtx);
        data_cond.wait(lock,[this]{return !data_queue.empty();});
        value=std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(T& value){
        std::lock_guard<std::mutex> lock(mtx);
        if(data_queue.empty()) return false;
        value=std::move(*data_queue.front());
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<std::mutex> lock(mtx);
        data_cond.wait(lock,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res=data_queue.front();
        data_queue.pop();
        return res;
    }
    std::shared_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lock(mtx);
        if(data_queue.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> res=data_queue.front();
        data_queue.pop();
        return res;
    }
    void push(T new_value){
        std::shared_ptr<T> data_ptr=std::make_shared<T>(std::move(new_value));
        std::lock_guard<std::mutex> lock(mtx);
        data_queue.push(data_ptr);
        data_cond.notify_one();
    }
    bool empty() const{
        std::lock_guard<std::mutex> lock(mtx);
        return data_queue.empty();
    }
};
