#pragma once
#include <vector>
#include <iostream>
#include <numeric>
#include <time.h>

template <typename T>
class NDArray {
	//std::vector<T> values;
	T* values;
	std::vector<int> shape;
    int size;
public:
    // Конструктор
    NDArray(std::vector<int> nshape);

    // Заполнение матрицы нулями
    static NDArray FillZero(std::vector<int> shape);

    // Заполнение матрицы единицами
    static NDArray FillOne(std::vector<int> shape);

    // Заполнение матрицы случайными числами
    static NDArray FillRandom(std::vector<int> shape, T max = 100);

    // размер ndarray
    int GetSize();

    // Операторы +
    NDArray<T> operator +(T other);
    NDArray<T> operator +(NDArray<T> other);
    NDArray<T>* operator +=(T other);
    NDArray<T>* operator +=(NDArray<T> other);

    // Операторы -
    NDArray<T> operator -(T other);
    NDArray<T> operator -(NDArray<T> other);
    NDArray<T>* operator -=(T other);
    NDArray<T>* operator -=(NDArray<T> other);

    // Операторы *
    NDArray<T> operator *(T other);
    NDArray<T> operator *(NDArray<T> other);
    NDArray<T>* operator *=(T other);
    NDArray<T>* operator *=(NDArray<T> other);

    // Операторы /
    NDArray<T> operator /(T other);
    NDArray<T> operator /(NDArray<T> other);
    NDArray<T>* operator /=(T other);
    NDArray<T>* operator /=(NDArray<T> other);


    NDArray<T> transpose();

    //
    T& operator[](const int index) { return values[index]; };
    T& operator[](std::vector<int> indexes);

	void print_shape(int deep, std::vector<std::vector<int>> indexs);

	friend std::ostream& operator<<(std::ostream& out, const NDArray& arr);
};

template<typename T>
void NDArray<T>::print_shape(int deep, std::vector<std::vector<int>> indexes){
	std::cout << "deep = " << deep << "\n";
	if (deep == shape.size()){
		return;
	}
	for (auto idx : indexes){
		for (auto id : idx){
			std::cout << id << " ";
		}
		std::cout << "; ";
	}

	if (deep == size){
		for (auto idx : indexes){
			for (auto id : idx){
				std::cout << id << " ";
			}
			std::cout << "; ";
		}
		return;
	}
	
	if (deep == 0){
		for (int i = 0; i < shape[deep]; i++){
			std::vector<int> buf;
			buf.push_back(i);
			indexes.push_back(buf);
			std::cout << i << ", ";
		}
		std::cout << "first - idx " << "\n";
		for (auto &idx : indexes){
			for (auto id : idx){
				std::cout << id << " ";
			}
			std::cout << "; ";
		}
		std::cout << "\n";
	} 
	else {
		for (auto &idx : indexes){
			for (int i = 0; i < shape[deep]; i++){
				auto copy = idx;
				copy.push_back(i);
			}
			
		}
		std::cout << "\n";
	}

	print_shape(deep + 1, indexes);
}


template<typename T>
std::ostream& operator<<(std::ostream& out, NDArray<T>& arr)
{
    for (int i = 0; i < arr.GetSize() - 1; i++) {
        out << arr[i] << ", ";
    }
    out << arr[arr.GetSize() - 1] << "\n";
    return out;
}

template<typename T>
NDArray<T>::NDArray(std::vector<int> nshape) {
    int new_size = 1;
    shape = nshape;
    for (auto num : nshape)
        new_size *= num;
    size = new_size;
    values = new T[size];
};


template<typename T>
NDArray<T> NDArray<T>::FillZero(std::vector<int> shape) {
    NDArray<T> arr(shape);
    for (int i = 0; i < arr.size; i++) {
        arr[i] = 0;
    }
    return arr;
};

template<typename T>
NDArray<T> NDArray<T>::FillOne(std::vector<int> shape) {
    NDArray<T> arr(shape);
    for (int i = 0; i < arr.size; i++) {
        arr[i] = 1;
    }
    return arr;
};

template<typename T>
int NDArray<T>::GetSize()
{
    return this->size;
};

template<typename T>
NDArray<T> NDArray<T>::FillRandom(std::vector<int> shape, T max){
    srand(time(NULL));
    NDArray arr(shape);
    for (int i = 0; i < arr.size; i++) {
        arr[i] = rand() % max;
    }
    return arr;
}

template<typename T>
inline T& NDArray<T>::operator[](std::vector<int> indexes){
    int index = 0;
    for (int i = 0; i < indexes.size(); i++) {
        int delta_index = indexes[i];
        for (int j = i + 1; j < shape.size(); j++) {
            delta_index *= shape[j];
        }
        index += delta_index;
    }

    return values[index];
}


// Математические операторы


// Сложение
template<typename T>
NDArray<T> NDArray<T>::operator+(T other){
    auto copy = *this;
    for (int i = 0; i < size; i++) {
        copy.values[i] += other;
    }
    return copy;
}

template<typename T>
NDArray<T>* NDArray<T>::operator+=(T other){
    for (int i = 0; i < size; i++) {
        values[i] += other;
    }
    return this;
}

template<typename T>
NDArray<T> NDArray<T>::operator+(NDArray<T> other){
    if (shape != other.shape) {
        throw std::invalid_argument("Shapes are not same!");
    }
    auto copy = *this;
    for (int i = 0; i < size; i++) {
       copy.values[i] += other.values[i];
    }

    return copy;
}

template<typename T>
NDArray<T>* NDArray<T>::operator+=(NDArray<T> other){
    if (shape != other.shape) {
        throw std::invalid_argument("Shapes are not same!");
    }

    for (int i = 0; i < size; i++) {
        values[i] += other.values[i];
    }

    return this;
}

// Вычитание

template<typename T>
NDArray<T> NDArray<T>::operator-(T other){
    return *this + (-other);
}

template<typename T>
NDArray<T>* NDArray<T>::operator-=(T other){

    for (int i = 0; i < size; i++) {
        values[i] -= other;
    }

    return this;
}

template<typename T>
NDArray<T> NDArray<T>::operator-(NDArray<T> other)
{
    return *this + (other * -1);
}

template<typename T>
NDArray<T>* NDArray<T>::operator-=(NDArray<T> other)
{
    if (shape != other.shape) {
        throw std::invalid_argument("Shapes are not same!");
    }

    for (int i = 0; i < size; i++) {
        values[i] -= other.values[i];
    }

    return this;
}


// Умножение
template<typename T>
NDArray<T> NDArray<T>::operator*(T other) {
    auto copy = *this;
    for (int i = 0; i < size; i++) {
        copy.values[i] *= other;
    }
    return copy;
}

template<typename T>
NDArray<T>* NDArray<T>::operator*=(T other) {
    for (int i = 0; i < size; i++) {
        values[i] *= other;
    }
    return this;
}

template<typename T>
NDArray<T> NDArray<T>::operator*(NDArray<T> other) {
    if (shape != other.shape && shape.size() != 2) {
        throw std::invalid_argument("Shapes are not same!");
    }

    auto result = FillZero({ shape[0], other.shape[1]});
    
    for (int i = 0; i < shape[0]; i++) {
        for (int j = 0; j < other.shape[1]; j++) {
            T value = 0;
            for (int c = 0; c < shape[0]; c++) {
                value += (*this)[{i, c}] * other[{c, j}];
            }
            result[{i, j}] = value;
        }
    }

    return result;
}

template<typename T>
NDArray<T>* NDArray<T>::operator*=(NDArray<T> other) {
    *this = (*this) * other;
    return this;
}

// Деление
template<typename T>
NDArray<T> NDArray<T>::operator/(T other) {
    auto copy = *this;
    for (int i = 0; i < size; i++) {
        copy.values[i] /= other;
    }
    return copy;
}

template<typename T>
NDArray<T>* NDArray<T>::operator/=(T other) {
    for (int i = 0; i < size; i++) {
        values[i] /= other;
    }
    return this;
}

template<typename T>
NDArray<T> NDArray<T>::operator/(NDArray<T> other) {
    if (shape != other.shape) {
        throw std::invalid_argument("Shapes are not same!");
    }
    auto copy = *this;
    for (int i = 0; i < size; i++) {
        copy.values[i] /= other.values[i];
    }

    return copy;
}

template<typename T>
NDArray<T>* NDArray<T>::operator/=(NDArray<T> other) {
    if (shape != other.shape) {
        throw std::invalid_argument("Shapes are not same!");
    }

    for (int i = 0; i < size; i++) {
        values[i] /= other.values[i];
    }

    return this;
}


// Транспониравание матрицы

template<typename T>
NDArray<T> NDArray<T>::transpose(){
    if (shape.size() != 2) {
        throw std::invalid_argument("Can transponse onli 2-dimensional matrix");
    }

    std::vector<int> transposed_shape = {shape[1], shape[0]};
    NDArray<T> new_mat = FillZero(transposed_shape);
    
    for (int i = 0; i < shape[1]; i++) {
        for (int j = 0; j < shape[0]; j++) {
            new_mat[{i, j}] = (* this)[{j, i}];
        }
    }
    return new_mat;

}