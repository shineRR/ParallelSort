#include <iostream>
#include <mutex>
#include "TaskQueue/TaskQueue.h"
#include "QueueHandler/QueueHandler.h"
#include "FileReader/Reader.h"

int main() {
    QueueHandler queueHandler = QueueHandler(13);
    Reader reader = Reader(13, &queueHandler);
    return 0;
}