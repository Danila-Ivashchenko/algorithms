#include "msd.h"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

int c = 0;



void rand_fill(std::vector<int> &arr, int max = 100) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % max - 50;
    }
}

int main()
{
    srand(time(NULL));
    int n = 10;
    std::vector<int> arr(n);

    rand_fill(arr);
	for (auto num : arr) {
        std::cout << num << ", ";
    }
	std::cout << '\n';
    msd_sort(arr, false);
    for (auto num : arr) {
        std::cout << num << ", ";
    }

    //std::cout << is_sorted(arr) << ", operations = " << c << std::endl;
    //std::cout << get_digit(31, 2) << std::endl;


    return 0;
}