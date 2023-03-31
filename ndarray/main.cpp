#include "NDArray.h"
#include <iostream>
#include <vector>


void test() {
	std::vector<int> shape = { 2, 5 };

	NDArray<int> arr1(shape);
	NDArray<int> arr2(shape);

	for (int i = 0; i < arr1.GetSize(); i++) {
		arr1[i] = 10 - i;
		arr2[i] = i;
	}

	std::cout << arr1 << arr2 << "\n";

	auto new_arr = arr1 + 2;
	std::cout << new_arr;
	new_arr += 2;
	std::cout << new_arr;
	new_arr = arr1 + new_arr;
	std::cout << new_arr;
	new_arr += arr2;
	std::cout << new_arr << "\n";

	new_arr = NDArray<int>::FillOne({3, 3, 3});
	std::cout << new_arr;
	new_arr = new_arr * 3;
	std::cout << new_arr;
	new_arr *= 2;
	std::cout << new_arr;

	new_arr = arr1 - 2;
	std::cout << new_arr;
	new_arr -= 2;
	std::cout << new_arr;
	new_arr = arr1 - new_arr;
	std::cout << new_arr;
	new_arr -= arr2;
	std::cout << new_arr << "\n";

	new_arr = NDArray<int>::FillOne({ 4, 4 });
	new_arr *= 100;
	std::cout << new_arr;
	new_arr = new_arr / 3;
	std::cout << new_arr;
	new_arr /= 2;
	std::cout << new_arr;
	new_arr = (arr1 + 11) / (arr2 - 12);
	std::cout << new_arr;
	new_arr /= new_arr;
	std::cout << new_arr << "\n";

	new_arr = arr1.transpose();
	std::cout << arr1 << new_arr;

	NDArray<int> mat1({ 2, 2 });
	NDArray<int> mat2({ 2, 1 });

	mat1[{0, 0}] = 15;
	mat1[{0, 1}] = 27;
	mat1[{1, 0}] = 18;
	mat1[{1, 1}] = 10;

	mat2[{0, 0}] = 35;
	mat2[{1, 0}] = 16;
	auto res = mat1 * mat2;
	std::cout << res;
	mat1 *= mat2;
	std::cout << mat1 ;

}

int main()
{
	test();
	return 0;
}