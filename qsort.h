#pragma once
#include"RequestHandler.h"


auto end = std::chrono::high_resolution_clock::now(); // to count thread pool working time
RequestHandler pool;
void quicksort_tasked(std::shared_ptr<int[]> array, long left, long right)
{
    
    end = std::chrono::high_resolution_clock::now();
    if (left >= right) return;
    long left_bound = left;
    long right_bound = right;

    long middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle) {
            left_bound++;
        }
        while (array[right_bound] > middle) {
            right_bound--;
        }

        if (left_bound <= right_bound) {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if ((right_bound - left > 100'000))
    {
        std::packaged_task<void()> task([&]() {
            pool.pushRequest(quicksort_tasked, array, left, right_bound);
            });

        quicksort_tasked(array, left_bound, right);
        //std::future<void> fut = task.get_future();
        task();
    }
    else
    {
        quicksort_tasked(array, left, right_bound);
        quicksort_tasked(array, left_bound, right);
    }
}


void quicksort(std::shared_ptr<int[]> array, long left, long right) {
    if (left >= right) return;
    long left_bound = left;
    long right_bound = right;

    long middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle)
        {
            left_bound++;
        }
        while (array[right_bound] > middle)
        {
            right_bound--;
        }

        if (left_bound <= right_bound)
        {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);
    quicksort(array, left, right_bound);
    quicksort(array, left_bound, right);
}
