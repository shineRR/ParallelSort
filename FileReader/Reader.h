//
// Created by shine on 11/12/2020.
//

#ifndef PARALLELSORT_READER_H
#define PARALLELSORT_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../QueueHandler/QueueHandler.h"

class Reader {
    typedef std::function<void()> Func;
    private:
        std::vector<std::string>* lines = new std::vector<std::string>();
        std::vector< std::vector<std::string>*>* tasks = new std::vector<std::vector<std::string>*>();

        QueueHandler* queueHandler;
    public:
        int _threads = 0;
        Reader(int threads, QueueHandler* _queueHandler) {
            _threads = threads;
            queueHandler = _queueHandler;
            std::string line;
            std::ifstream in(R"(C:\Users\shine\Desktop\Dev\ParallelSort\FileReader\text.txt)");
            if(in.is_open()) {
                while (getline(in, line))
                {
                    lines->push_back(line);
                }
            }
            in.close();
            SendTasksToQueue();
            std::this_thread::sleep_for (std::chrono::seconds(1));
            queueHandler->Dispose();
            std::cout << "123" << std:: endl;
            std::this_thread::sleep_for (std::chrono::seconds(4));
            outputVector(*(*tasks)[0]);
        }

        void SendTasksToQueue() {
            int numOfTasks = (lines->size() + (_threads - 1)) / _threads;
            int maxTaskSize = lines->size() / numOfTasks;
            int currPos = 0;
            for (int i = 0; i < numOfTasks; ++i) {
                auto* taskLines = new std::vector<std::string>();
                int j = 0;
                while (currPos < lines->size()) {
                    if (j == maxTaskSize)
                        break;
                    taskLines->push_back((*lines)[currPos]);
                    j++;
                    currPos++;
                }
                tasks->push_back(taskLines);
                AddTask(taskLines);
            }
        }

        void AddTask(std::vector<std::string>* vector) {
            queueHandler->EnqueueTask([vector] {
                std::sort(vector->begin(), vector->end());
                std::cout << "Sorted!" << std::endl;
            });
        }

         void outputVector(std::vector<std::string> vector) {
            for (int i = 0; i < vector.size(); i++) {
                std::cout << vector[i].c_str() << std::endl;
            }
        }
};


#endif //PARALLELSORT_READER_H
