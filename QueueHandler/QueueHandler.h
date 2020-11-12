//
// Created by shine on 11/11/2020.
//

#ifndef PARALLELSORT_QUEUEHANDLER_H
#define PARALLELSORT_QUEUEHANDLER_H

#include "windows.h"
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include "../TaskQueue/TaskQueue.h"
#include <tchar.h>
#include <iostream>

class QueueHandler {
    typedef std::function<void()> Func;
    private:
        std::mutex mutex;
        TaskQueue _taskQueue;
        bool isActive = true;
        std::vector<std::thread> workers;
    public:
        int _threads = 0;
        static void Print() {
            std::cout << "Print" << std::endl;
        }

        static long start_thread(void *param) {
            auto *obj = (QueueHandler *) param;
            obj->TaskSelectionQueue();
            return 0;
        }

        explicit QueueHandler(int threads) {
            _threads = threads;
            for (int i = 0; i < _threads; ++i) {
                workers.emplace_back(start_thread, this);
            }
        }

        void TaskSelectionQueue() {
            while (isActive) {
                mutex.lock();
                Func function = _taskQueue.DequeueTask();
                mutex.unlock();
                if (function != nullptr)
                    function();
                std::this_thread::sleep_for (std::chrono::seconds(1));
            }
        }

        void EnqueueTask(Func func) {
            _taskQueue.EnqueueTask(func);
        }

        void Dispose() {
            while (true)
            {
                std::this_thread::sleep_for (std::chrono::seconds(1));
                mutex.lock();
                if (_taskQueue.queue_size() == 0) break;
                mutex.unlock();
            }
            isActive = false;
            mutex.unlock();
            for(auto &worker : workers) {
                worker.join();
            }
        }
};


#endif //PARALLELSORT_QUEUEHANDLER_H
