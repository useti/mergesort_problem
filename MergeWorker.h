//
// Created by YURY TIKHOGLAZ on 2019-01-20.
//

#ifndef MERGESORT_MERGEWORKER_H
#define MERGESORT_MERGEWORKER_H
#include <cstdint>


class MergeWorker {
public:
    MergeWorker(uint32_t start, uint32_t stop, uint32_t level);

    MergeWorker();
};


#endif //MERGESORT_MERGEWORKER_H
