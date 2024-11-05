/***
* @Author: 
* @Date: 2024-10-29 01:30:59
* @LastEditTime: 2024-11-06 01:06:38
* @Description: 线程安全的条件等待的栈
 */
#include <condition_variable>
#include <mutex>
#include <stack>


template<typename T>
class threadsafe_stack_waitable{
private:
    std::stack<T> data;
    std::mutex m;
    std::condition_variable cv;
public:
    threadsafe_stack_waitable(){}
    threadsafe_stack_waitable(const threadsafe_stack_waitable& other){
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    threadsafe_stack_waitable& operator=(const threadsafe_stack_waitable&) = delete;
    void push(T new_value){
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
        cv.notify_one();
    }
    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this](){
            return !data.empty();
        });
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }
    void wait_and_pop(T& value){
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this](){
            return !data.empty();
        });
        value = std::move(data.top());
        data.pop();
    }
    bool empty() const{
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
    bool try_pop(T& value){
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) return false;
        value = std::move(data.top());
        data.pop();
        return true;
    }
    std::shared_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }
};
