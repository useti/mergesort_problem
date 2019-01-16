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

// STAGE 0 - READ INPUT FILE AND SPLIT TO THE CHUNKS
void stage0(){
    std::cout << "STAGE 0 - READ INPUT FILE AND SPLIT TO THE CHUNKS" << std::endl;
    std::cout << std::endl;
}

// STAGE 1 - MERGE CHUNKS
void stage1(){
    std::cout << "STAGE 1 - MERGE CHUNKS" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "PROBLEM 1 SOLUTION by Yury Tikhoglaz" << std::endl;
    std::cout << std::endl;
    std::cout << "\tMemory limit \t\t- " << MEMORY_SIZE_AVAILABLE << std::endl;
    std::cout << "\tKernels limit \t\t- " << KERNELS_NUM << std::endl;
    std::cout << "\tInput file name \t- " << INPUT_FILE << std::endl;
    std::cout << "\tOutput file name \t- " << OUTPUT_FILE_NAME << std::endl;
    std::cout << std::endl;

    stage0();

    stage1();

    return 0;
}