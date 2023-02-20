#include <iostream>
#include <map>
#include <time.h>
#include <stdlib.h>


int main(){
	srand((unsigned)time(0));

    int n = 1;

	for (int i = 0; i < 8; i++){
		n *= 10;
		double time_start = clock();
		std::map <int, int> container {};

		for (int j = 0; j < n; j++){
			container[j] = rand() % n;
		}

		std::cout << n << " " << sizeof(container) + n * 2 * sizeof(int) << " " << clock() - time_start << std::endl;
	}
    return 0;
}