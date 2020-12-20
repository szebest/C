#include <iostream>

template<typename T>
class dynamicArray
{
private:
	T* buffer;
	size_t currSize;
	size_t capacity;

	void realloc(size_t _newCapacity)
	{
		T* temporary = new T[_newCapacity];
		
		memcpy(temporary, buffer, currSize * sizeof(int));

		delete[] buffer;
		buffer = temporary;

		capacity = _newCapacity;
	}

public:
	dynamicArray(size_t _capacity = 1) noexcept : capacity(_capacity), currSize(0)
	{
		buffer = new T[capacity];
	}

	~dynamicArray()
	{
		delete[] buffer;
	}

	void push_back(T _element)
	{
		if (currSize >= capacity)
			realloc(2 * capacity);

		buffer[currSize] = _element;

		currSize++;
	}

	constexpr size_t size() const noexcept
	{
		return currSize;
	}

	T& operator[](const size_t index)
	{
		return buffer[index];
	}
};

int main()
{
	dynamicArray<int> dArray;
	dArray.push_back(1);
	dArray.push_back(1);
	dArray.push_back(1);
	dArray.push_back(1);
	dArray.push_back(1);

	for (size_t i = 0; i < dArray.size(); i++)
		std::cout << dArray[i] << '\n';

	return 0;
}