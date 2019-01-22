/*
 Задача №1
 Необходимо написать программу, которая будет сортировать по возрастанию большой файл беззнаковых 32-х разрядных
 целых чисел. При этом:
 - Размер входного файла значительно больше объема доступной оперативной памяти, которой есть всего 128 Мб.
 - Числа в файле записаны в бинарном виде.
 - Есть достаточно дискового пространства для хранения результата сортировки в отдельном файле и для хранения
   промежуточных результатов.
 - Программа будет компилироваться при помощи g++-5.3.0 с опциями -std=c++14 -D_NDEBUG -O3 -lpthread.
 - Файлы будут находиться на SSD диске. А компьютере стоит 2-х ядерный процессор.
 - Входной файл будет находиться в той же директории что и исполняемый файл и будет называться input. Мы ожидаем там же
   увидеть отсортированный файл с именем output.
 - Из вашей программы должен получиться исполняемый файл, а значит нужно чтобы в ней была функция main.
 - Никаких дополнительных библиотек на компьютере не установлено. (Например, нет boost).
 - Решение должно быть кросс-платформенным.
 - Входной файл менять нельзя.
 - Для того, чтобы у всех были равные условия, мы 2 раза запустим сортировку вхолостую, а затем еще 3 раза. Измерим
   время, за которое файл был отсортирован в течении каждой из 3-х попыток и усредним его.
 - В качестве решения можно загрузить или один cpp-файл, или zip-архив c h- или cpp-файлами.
*/

// Solution by Yury Tikhoglaz

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "MergeWorker.h"

using namespace std;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Log data
#define LOGDATA

// Memory size
#define MEMORY_SIZE_AVAILABLE 131072

#define ELEMENTS_PER_CHUNK 32000
//#define ELEMENTS_PER_CHUNK 16000

// Number of kernels
#define KERNELS_NUM 2

// Number of workers
#define WORKERS_NUM 4

// Input file name
#define INPUT_FILE "input"

// Output file name
#define OUTPUT_FILE_NAME "output"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

uint32_t _levelOne = 0;

uint32_t _numberOfChunks = 0;

uint32_t splitFile();

void initialInfo();

void saveChunk(uint32_t chunk, vector<uint32_t> &currentChunk, uint32_t level = 0);

void stage1();

void stage0();

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTIONS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

uint32_t splitFile() {

    uint32_t totalElements = 0, chunkElement = 0, chunk = 0, numb;
    vector<uint32_t> currentChunk;

    FILE *inputFile = fopen(INPUT_FILE, "rb");
    while(fread(&numb, sizeof(uint32_t), 1, inputFile)) {

        currentChunk.push_back(numb);

        totalElements++;
        chunkElement++;
        if(chunkElement >= ELEMENTS_PER_CHUNK){
            chunkElement = 0;

            sort(currentChunk.begin(), currentChunk.end());

            saveChunk(chunk, currentChunk);

            currentChunk.clear();
            currentChunk.shrink_to_fit();

            chunk++;
        }

    }

    if(!currentChunk.empty()) {
        sort(currentChunk.begin(), currentChunk.end());
        saveChunk(chunk, currentChunk);
    }

    fclose(inputFile);

    _numberOfChunks = chunk;

    return totalElements;
}

void saveChunk(uint32_t chunk, vector<uint32_t> &currentChunk, uint32_t level) {

    std::ostringstream outFileName;

    outFileName << "chnk" << chunk << "lvl" << level;

    FILE *outputFile = fopen(outFileName.str().c_str(), "wb");

    for(vector<uint32_t>::iterator element = currentChunk.begin(); element!=currentChunk.end(); ++ element){
        fwrite(&element, sizeof(uint32_t),1,outputFile);
    }

    fclose(outputFile);

#ifdef LOGDATA
    cout << "\t\tChunk " << chunk << " saved (" << currentChunk.size() << " elements)" << endl;
#endif
}

void initialInfo() {
    cout << "PROBLEM 1 SOLUTION by Yury Tikhoglaz" << endl;
    cout << endl;
    cout << "\tMemory limit \t\t- " << MEMORY_SIZE_AVAILABLE << " Bytes" << endl;
    cout << "\tElements per chunk \t- " << ELEMENTS_PER_CHUNK << endl;
    cout << "\tKernels limit \t\t- " << KERNELS_NUM << endl;
    cout << "\tInput file name \t- " << INPUT_FILE << endl;
    cout << "\tOutput file name \t- " << OUTPUT_FILE_NAME << endl;
    cout << endl;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// STAGES
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// STAGE 1 - READ INPUT FILE AND SPLIT TO THE CHUNKS
void stage0(){
#ifdef LOGDATA
    cout << "STAGE 1 - READ INPUT FILE AND SPLIT TO THE CHUNKS" << endl;
    cout << endl;
#endif

    _levelOne = splitFile();

#ifdef LOGDATA
    cout << "\tRead " << _levelOne << " numbers" << endl;
    cout << std::endl;
#endif
}

// STAGE 2 - MERGE CHUNKS
void stage1(){
#ifdef LOGDATA
    cout << "STAGE 2 - MERGE CHUNKS" << endl;
    cout << endl;
#endif

    // TODO: Refactor this code to move code below to the worker class

    uint32_t level = 0;

    bool exitCondition = false;

    while (!exitCondition)
    {

        uint32_t element = 0;

#ifdef LOGDATA
        cout << "LEVEL " << level << endl;
#endif

        for (int i = 0; i <= _numberOfChunks; i+= WORKERS_NUM * 2) {
            for (int j = 0; j < WORKERS_NUM; ++j) {

                std::ostringstream inFileName1;
                std::ostringstream inFileName2;
                std::ostringstream outFileName;

                inFileName1 << "chnk" <<i + j*2     << "lvl" << level;
                inFileName2 << "chnk" <<i + j*2 + 1 << "lvl" << level;
                outFileName << "chnk" << element + 1 << "lvl" << level + 1;


                // check if input chunks exists

                ifstream input1(inFileName1.str().c_str(), ios::binary);
                ifstream input2(inFileName2.str().c_str(), ios::binary);

                if (input1 && input2){
                    // both files exist - merging

#ifdef LOGDATA
                    cout << "\t\tMerging chunk " << inFileName1.str() << " with chunk " << inFileName2.str() << endl;
                    cout << "\t\tOutput file "<< outFileName.str() << endl;
#endif

                    FILE *outputFile = fopen(outFileName.str().c_str(), "wb");

                    // MERGE

                    uint32_t left;
                    uint32_t right;

                    // compare left and right, move less number to the output
                    // make step on the file smaller number belongs to

                    fclose(outputFile);

#ifdef LOGDATA
                    cout << "\t\tRemoving chunk " << inFileName1.str() << endl;
#endif
                    remove(inFileName1.str().c_str());

#ifdef LOGDATA
                    cout << "\t\tRemoving chunk " << inFileName2.str() << endl;
#endif
                    remove(inFileName2.str().c_str());
                    element++;
                } else{
                    if(input1){
                        // file 1 exist - moving to next level

#ifdef LOGDATA
                        cout << "\t\tMoving chunk " << inFileName1.str() << " to level " << level + 1 << endl;
                        cout << "\t\tOutput file "<< outFileName.str() << endl;

#endif

                        FILE *outputFile = fopen(outFileName.str().c_str(), "wb");

                        fclose(outputFile);

#ifdef LOGDATA
                        cout << "\t\tRemoving chunk " << inFileName1.str() << endl;
#endif
                        remove(inFileName1.str().c_str());

                        element++;
                    }
                    if(input2){
                        // file 2 exist - moving to next level

#ifdef LOGDATA
                        cout << "\t\tMoving chunk " << inFileName2.str() << " to level " << level + 1 << endl;
                        cout << "\t\tOutput file "<< outFileName.str() << endl;
#endif

                        FILE *outputFile = fopen(outFileName.str().c_str(), "wb");

                        fclose(outputFile);

#ifdef LOGDATA
                        cout << "\t\tRemoving chunk " << inFileName2.str() << endl;
#endif
                        remove(inFileName2.str().c_str());
                        element++;
                    }
                }


            }
        }

        level++;

        exitCondition = true;
    }

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main() {

#ifdef LOGDATA
    initialInfo();
#endif

    stage0();

    stage1();

    return 0;
}
