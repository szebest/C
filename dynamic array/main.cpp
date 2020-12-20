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
		if (_newCapacity == 0)
			return;

		T* temporary = new T[_newCapacity];
		
		memmove(temporary, buffer, currSize * sizeof(T));

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

	void erase(T* _pointer)
	{
		if ((_pointer - buffer) / sizeof(T) - currSize < 0)
			return;

		if (_pointer + 1 < end())
			memmove(_pointer, _pointer + 1, currSize - (_pointer - buffer) / sizeof(T) + 1);

		currSize--;

		if (currSize <= capacity / 2)
			realloc(capacity / 2);
	}

	void pop_back()
	{
		if (currSize > 0)
			erase(begin() + currSize - 1);
	}

	T* begin() const noexcept
	{
		return buffer;
	}

	T* end() const noexcept
	{
		return (buffer + currSize);
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
	dynamicArray<int> dArray(5);
	dArray.push_back(1);
	dArray.push_back(2);
	dArray.push_back(4);
	dArray.push_back(3);
	dArray.push_back(5);

	dArray.erase(dArray.begin() + 4);

	dArray.pop_back();
	dArray.pop_back();
	dArray.pop_back();
	dArray.pop_back();

	dArray.push_back(1);
	dArray.push_back(2);
	dArray.push_back(4);
	dArray.push_back(3);
	dArray.push_back(5);

	for (size_t i = 0; i < dArray.size(); i++)
		std::cout << dArray[i] << '\n';

	std::cout << "Range-based loop\n";

	for (int elem : dArray)
	{
		std::cout << elem << '\n';
	}

	return 0;
}