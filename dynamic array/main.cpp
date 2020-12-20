#include <iostream>

template<typename T>
class dynamicArray
{
private:
	T* buffer;
	size_t currSize;
	size_t currCapacity;

	void realloc(size_t _newCapacity)
	{
		if (_newCapacity == 0)
			return;

		T* temporary = new T[_newCapacity];
		
		memmove(temporary, buffer, currSize * sizeof(T));

		delete[] buffer;
		buffer = temporary;

		currCapacity = _newCapacity;
	}

public:
	dynamicArray(size_t _capacity = 1) noexcept : currCapacity(_capacity), currSize(0)
	{
		buffer = new T[currCapacity];
	}

	~dynamicArray()
	{
		delete[] buffer;
	}

	void push_back(T _element)
	{
		if (currSize >= currCapacity)
			realloc(2 * currCapacity);

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

		if (currSize <= currCapacity / 2)
			realloc(currCapacity / 2);
	}

	void pop_back()
	{
		if (currSize > 0)
			erase(begin() + currSize - 1);
	}

	void shrink_to_fit()
	{
		realloc(currSize);
	}

	void reserve(size_t amount)
	{
		realloc(currCapacity + amount);
	}

	constexpr bool empty() const noexcept
	{
		return currSize == 0;
	}

	constexpr T& at(size_t index) const noexcept
	{
		if (index < currSize)
			return buffer[index];
	}

	constexpr size_t capacity() const noexcept
	{
		return currCapacity;
	}

	constexpr T& first() const noexcept
	{
		return *buffer;
	}

	constexpr T& last() const noexcept
	{
		return *(buffer+currSize-1);
	}

	constexpr T* begin() const noexcept
	{
		return buffer;
	}

	constexpr T* end() const noexcept
	{
		return (buffer + currSize);
	}

	constexpr size_t size() const noexcept
	{
		return currSize;
	}

	constexpr T& operator[](const size_t index)
	{
		return buffer[index];
	}
};

int main()
{
	dynamicArray<int> dArray(5);

	std::cout << dArray.empty() << '\n';

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