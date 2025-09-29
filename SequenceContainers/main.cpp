#include <iostream>
#include <array>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

#define STL_ARRAY

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

	return 0;
}