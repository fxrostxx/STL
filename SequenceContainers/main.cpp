#include <iostream>
#include <array>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n----------------------------\n"

template<typename T> void vector_info(const std::vector<T>& vec);

//#define FACTORIAL
//#define STL_ARRAY
#define STL_VECTOR

#ifdef FACTORIAL
unsigned long long int Factorial(int n)
{
	if (n < 0) throw std::invalid_argument("Фактоиал не определен для отрицательных чисел");
	if (n > 20) throw std::invalid_argument("Арифметическое переполнение");
	if (n == 0 || n == 1) return 1;
	return (unsigned long long int)n * Factorial(n - 1);
}
#endif // FACTORIAL

int main()
{
	setlocale(LC_ALL, "");

#ifdef FACTORIAL
	int n;
	cout << "n = "; cin >> n;
	try
	{
		cout << n << "! = " << Factorial(n) << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // FACTORIAL

#ifdef STL_ARRAY
	//throw;
	const int size = 5;
	std::array<int, size> arr;
	for (int i = 0; i < arr.size(); ++i) arr[i] = rand() % 100;
	try
	{
		for (int i = 0; i < arr.size() * 2; ++i) cout << arr.at(i) << tab; cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	/*catch (...)
	{
		std::cout << "Error: Something went wrong" << endl;
	}*/
#endif // STL_ARRAY

#ifdef STL_VECTOR
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < vec.size(); ++i) cout << vec[i] << tab; cout << endl;
	vector_info(vec);
	vec.push_back(55);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) cout << *it << tab; cout << endl;
	for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it) cout << *it << tab; cout << endl;
	vector_info(vec);
	//vec.shrink_to_fit();
	//vec.reserve(1600);
	vec.resize(8);
	for (int i : vec) cout << i << tab; cout << endl;
	vector_info(vec);
	cout << vec.front() << endl;
	cout << vec.back() << endl;
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	vec.insert(vec.begin() + index, value);
	for (int i : vec) cout << i << tab; cout << endl;
#endif // STL_VECTOR

	return 0;
}

template<typename T> void vector_info(const std::vector<T>& vec)
{
	cout << "Size: " << vec.size() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << delimeter << endl;
}