//
// Created by shine on 11/11/2020.
//

#ifndef PARALLELSORT_TASKQUEUE_H
#define PARALLELSORT_TASKQUEUE_H

#include <functional>

#include <queue>
#include <mutex>
#include <iostream>

class TaskQueue {
    typedef std::function<void()> Func;
private:
    std::mutex mutex;
    std::queue<Func> queue;
public:
    void EnqueueTask(const Func& function)
    {
        mutex.lock();
        queue.push(function);
        mutex.unlock();
    }

    Func DequeueTask()
    {
        Func function;
        if(queue.empty()) return nullptr;
        function = queue.front();
        mutex.lock();
        queue.pop();
        mutex.unlock();
        return function;
    }

    int queue_size() {
        int size = queue.size();
        return size;
    }
};


#endif //PARALLELSORT_TASKQUEUE_H
