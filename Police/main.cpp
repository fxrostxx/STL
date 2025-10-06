#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n----------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{0, "N/A"},
	{1, "Парковка в неположенном месте"},
	{2, "Непристегнутый ремень безопасности"},
	{3, "Пересечение сплошной полосы"},
	{4, "Превышение скорости"},
	{5, "Проезд на красный свет светофора"},
	{6, "Выезд на встречную полосу"},
	{7, "Езда в нетрезвом виде"},
	{8, "Оскорбление сотрудника полиции"}
};

class Crime
{
private:
	int violation;
	std::string place;
public:
	int get_violation() const
	{
		return violation;
	}
	const std::string& get_place() const
	{
		return place;
	}
	void set_violation(int violation)
	{
		this->violation = violation;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	Crime(int violation, const std::string& place)
	{
		set_violation(violation);
		set_place(place);
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	os.width(44);
	os << std::left;
	return os << VIOLATIONS.at(obj.get_violation()) << " " << obj.get_place();
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename);

int main()
{
	setlocale(LC_ALL, "");

	std::map<std::string, std::list<Crime>> base =
	{
		{"А777АА", {Crime(4, "ул. Ленина"), Crime(5, "ул. Ленина"), Crime(7, "ул. Энтузисатов"), Crime(8, "ул. Энтузиастов")}},
		{"А123ЕН", {Crime(2, "ул. Пролетарская"), Crime(3, "ул. Мира")}},
		{"А001УТ", {Crime(5, "ул. Октябрьская"), Crime(7, "ул. Космическая")}}
	};
	print(base);
	save(base, "base.txt");

	return 0;
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator plate = base.begin(); plate != base.end(); ++plate)
	{
		cout << plate->first << ":\n";
		for (std::list<Crime>::const_iterator violation = plate->second.begin(); violation != plate->second.end(); ++violation)
		{
			cout << tab << *violation << endl;
		}
		cout << delimeter << endl;
	}
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator plate = base.begin(); plate != base.end(); ++plate)
	{
		fout << plate->first << ":\n";
		for (std::list<Crime>::const_iterator violation = plate->second.begin(); violation != plate->second.end(); ++violation)
		{
			fout << tab << *violation << endl;
		}
		fout << delimeter << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}