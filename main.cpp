#include "ThreadPool.h"
#include "RequestHandler.h"
#include <iostream>
#include <chrono>
#include "qsort.h"
#include <iomanip>
#include <random>


int main()
{
    auto str_size = 40;
    setlocale(LC_ALL, "");
    //=================================================================================================================
    //создание массивов
    auto start = std::chrono::high_resolution_clock::now();
    double seconds;
    std::cout << std::setw(str_size) <<  "Creating arrays...: ";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1'000'000);
    long constexpr arr_size = 5'000'000;
    std::shared_ptr<int[]> array(new int[arr_size]);
    std::shared_ptr<int[]> array2(new int[arr_size]);
    for (auto i = 0; i < arr_size; i++) {
        array[i] = array2[i] = dist(gen);
    }
    end = std::chrono::high_resolution_clock::now();
    seconds = std::chrono::duration<double>(end - start).count();
    printf("%f s\n", seconds);


    //=================================================================================================================
    // threadPool sort
    quicksort_tasked(array, 0, arr_size - 1);
    std::cout << std::setw(str_size) << "Time thread poll array sorting...: ";
    auto last_end = std::chrono::high_resolution_clock::now();
    while (true)
    { // to count thread pool working time
        if (last_end == end) {
            seconds = std::chrono::duration<double>(end - start).count();
            printf("%f s\n", seconds);
            break;
        }
        last_end = end;
        std::this_thread::sleep_for(std::chrono::milliseconds(700));    
    }
    //=================================================================================================================
    // sort
    start = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(str_size) << "Time single thread array sorting...: ";
    if (arr_size <= 50'000'000) {
        quicksort(array2, 0, arr_size - 1);
    
    
    end = std::chrono::high_resolution_clock::now();
    seconds = std::chrono::duration<double>(end - start).count();
    printf("%f s\n", seconds);
    }
    else {
        std::cout << "to long\n";
    }

    //=================================================================================================================
    //проверка сортировки
    start = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(str_size) << "[check] thread poll array sorting...: ";
    auto i = 0;
    for (; i < arr_size - 1; i++) {
        if (array[i] > array[i + 1]) {
            std::cout << "Unsorted\n" << "\n";
            break;
        }
    }
    if (i == arr_size - 1) {
        end = std::chrono::high_resolution_clock::now();
        seconds = std::chrono::duration<double>(end - start).count();
        printf("%f s sorted OK\n", seconds);
    }
    //=================================================================================================================
    start = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(str_size) << "[check] single thread array sorting...: ";
    i = 0;
    for (; i < arr_size - 1; i++) {
        if (array2[i] > array2[i + 1]) {
            std::cout << "Unsorted\n" << std::endl;
            break;
        }
    }   
    if (i == arr_size - 1) {
        end = std::chrono::high_resolution_clock::now();
        seconds = std::chrono::duration<double>(end - start).count();
        printf("%f s sorted OK\n", seconds);
    }
    return 0;
}
