//
// Created by YURY TIKHOGLAZ on 2019-01-20.
//


#include "MergeWorker.h"

using namespace std;


MergeWorker::MergeWorker() {}

MergeWorker::MergeWorker(uint32_t start, uint32_t stop, uint32_t level) {
    _start = start;
    _stop = stop;
    _level = level;
}

uint32_t MergeWorker::doWork() {}
