#include <iostream>
#include <array>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define STL_ARRAY
#define FACTORIAL

unsigned long long int Factorial(int n);

int main()
{
	setlocale(LC_ALL, "");

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

#ifdef FACTORIAL
	int n;
	cout << "n = "; cin >> n;
	try
	{
		cout << n << "! = " << Factorial(n);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // FACTORIAL

	return 0;
}

unsigned long long int Factorial(int n)
{
	if (n < 0) throw std::invalid_argument("Фактоиал не определен для отрицательных чисел");
	if (n > 65) throw std::invalid_argument("Арифметическое переполнение");
	if (n == 0 || n == 1) return 1;
	return (unsigned long long int)n * Factorial(n - 1);
}