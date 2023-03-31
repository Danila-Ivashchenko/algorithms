#pragma once
#include <vector>
#include <math.h>

bool is_sorted(std::vector<int> &arr) {
    int* last_elem = nullptr;
    for (auto elem : arr) {
        if (last_elem != nullptr) {
            if (*last_elem > elem) {
                return false;
            }
        }
        last_elem = &elem;
    }
    return true;
}

int get_degree(int num, int base = 10) {
    int deg = 0;
    while (num > 0) {
        num /= 10;
        deg++;
    }
    return deg - 1;
}


int get_digit(int num, int degree, int base = 10) {
    num = abs(num);
    while (degree > 0 && num > 0) {
        num /= base;
        degree--;
    }
    return num % base;
}

void msd_sort_work_int(std::vector<int> &arr, int base, int classes_count = 10, bool direction = true){
    if (base < 0) {
        return;
    }
    int n = arr.size();
    std::vector<std::vector<int>> digits(classes_count + 1);

    for (auto& digit : digits) {
        digit.reserve(n / classes_count != 0 ? n / classes_count : 1);
    }

    for (auto num : arr) {
        if (direction) {
            digits[get_digit(num, base)].push_back(num);
        }
        else {
            digits[classes_count - get_digit(num, base) - 1].push_back(num);
        }
    }

    int index = 0;
    for (auto& sub_arr : digits) {
        msd_sort_work_int(sub_arr, base - 1, classes_count, direction);
        for (auto num : sub_arr) {
            arr[index] = num;
            index++;
        }
    }
}

// template <class T>
// concept INT_STR = std::is_same_v<T, std::string> || std::is_same_v<T, int>;

// template <INT_STR T>
void msd_sort(std::vector<int>& arr, int classes_count = 10, bool direction = true) {
    int max = 0, min = 0;
    std::vector<int> higher_zero;
    std::vector<int> below_zero;
    for (auto num : arr) {
        if (num >= 0) {
            higher_zero.push_back(num);
            if (num > max) {
                max = num;
            }
        }
        else {
            below_zero.push_back(num);
            if (num < min) {
                min = num;
            }
        }
    }

    msd_sort_work_int(higher_zero, get_degree(max), classes_count, direction);
    msd_sort_work_int(below_zero, get_degree(abs(min)), classes_count, !direction);
    below_zero.insert(below_zero.end(), higher_zero.begin(), higher_zero.end());
    arr = below_zero;
}