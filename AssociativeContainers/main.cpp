#include <iostream>
#include <map>
#include <list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------------\n"

#define STL_MAP

int main()
{
	setlocale(LC_ALL, "");

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Воскресенье"),
		std::pair<int, std::string>(1, "Понедельник"),
		std::pair<int, std::string>(2, "Вторник"),
		std::pair<int, std::string>(3, "Среда"),
		{4, "Четверг"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{5, "Пятница"},
		{6, "Суббота"},
		{7, "Воскресенье"}
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
	cout << delimeter << endl;
	for (std::pair<int, std::string> i : week) cout << i.first << tab << i.second << endl;
	cout << delimeter << endl;

	std::map<std::string, std::list<std::string>> dictionary =
	{
		{"occasionally", {"изредка", "иногда", "время от времени", "случайно"}},
		{"causes", {"причины", "приводить к"}},
		{"space", {"космос", "пространство", "пробел"}},
		{"void", {"пустота", "вакуум"}},
		{"sequence", {"последовательность", "ряд", "эпизод", "череда"}},
		{"consequence", {"последствие", "следствие", "вывод"}}
	};
	for (std::map<std::string, std::list<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		cout << it->first << " - ";
		for (std::list<std::string>::iterator list_it = it->second.begin(); list_it != it->second.end(); ++list_it)
		{
			cout << *list_it << "; ";
		}
		cout << endl;
	}
#endif // STL_MAP

	return 0;
}