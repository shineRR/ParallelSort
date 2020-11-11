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

#define MAX_THREADS 2

typedef void (*Func)();

class QueueHandler {
    private:
        std::mutex mutex;
        TaskQueue _taskQueue;
        bool isActive = true;
        HANDLE  hThreadArray[MAX_THREADS]{};
    public:

        static void Print() {
            std::cout << "Print" << std::endl;
        }

        static long start_thread(void *param) {
            auto *obj = (QueueHandler *) param;
            obj->TaskSelectionQueue();
            return 0;
        }

        QueueHandler() {
            for (int i = 0; i < 5; ++i) {
                _taskQueue.EnqueueTask(Print);
            }
            for (int i = 0; i < MAX_THREADS; ++i) {
                hThreadArray[i] = CreateThread(
                        nullptr,                          // default security attributes
                        0,                                    // use default stack size
                        (LPTHREAD_START_ROUTINE)start_thread,           // thread function name
                        this,                                 // argument to thread function
                        0,                                 // use default creation flags
                        nullptr);                              // returns the thread identifier
            }
            for (int i = 0; i < 5; ++i) {
                _taskQueue.EnqueueTask(Print);
            }
            WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
        }

        void TaskSelectionQueue() {
            while (isActive) {
                mutex.lock();
                Func function = _taskQueue.DequeueTask();
                if (function != nullptr)
                    function();
                mutex.unlock();
                std::this_thread::sleep_for (std::chrono::seconds(1));
                if (_taskQueue.queue_size() == 0)
                    Dispose();
            }
        }

        void Dispose() {
            mutex.lock();
            isActive = false;
            mutex.unlock();
        }
};


#endif //PARALLELSORT_QUEUEHANDLER_H
