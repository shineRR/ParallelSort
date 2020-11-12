#include <iostream>
#include <mutex>
#include "TaskQueue/TaskQueue.h"
#include "QueueHandler/QueueHandler.h"
#include "FileReader/Reader.h"

int main() {
    int threads = 4;
    QueueHandler queueHandler = QueueHandler(threads);
    Reader reader = Reader(&queueHandler);
    return 0;
}