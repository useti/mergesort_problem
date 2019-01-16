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

using namespace std;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Memory size
#define MEMORY_SIZE_AVAILABLE 131072

// Number of kernels
#define KERNELS_NUM 2

// Input file name
#define INPUT_FILE "input"

// Output file name
#define OUTPUT_FILE_NAME "output"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

uint32_t splitFile();

// STAGE 0 - CHECK INPUT FILE
void stage0(){
    cout << "STAGE 0 - CHECK INPUT FILE" << endl;
    cout << endl;
}

// STAGE 1 - READ INPUT FILE AND SPLIT TO THE CHUNKS
void stage1(){
    cout << "STAGE 1 - READ INPUT FILE AND SPLIT TO THE CHUNKS" << endl;
    cout << endl;

    uint32_t n = splitFile();

    cout << "\tRead " << n << " numbers" << endl;
    cout << std::endl;
}

uint32_t splitFile() {
    uint32_t n = 0, numb;

    FILE *inputFile = fopen(INPUT_FILE, "rb");
    while(fread(&numb, sizeof(uint32_t), 1, inputFile)) {
        n++;
    }
    fclose(inputFile);

    return n;
}

// STAGE 2 - MERGE CHUNKS
void stage2(){
    cout << "STAGE 2 - MERGE CHUNKS" << endl;
    cout << endl;


}

int main() {
    cout << "PROBLEM 1 SOLUTION by Yury Tikhoglaz" << endl;
    cout << endl;
    cout << "\tMemory limit \t\t- " << MEMORY_SIZE_AVAILABLE << endl;
    cout << "\tKernels limit \t\t- " << KERNELS_NUM << endl;
    cout << "\tInput file name \t- " << INPUT_FILE << endl;
    cout << "\tOutput file name \t- " << OUTPUT_FILE_NAME << endl;
    cout << std::endl;

    stage0();

    stage1();

    stage2();

    return 0;
}