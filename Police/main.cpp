#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <ctime>
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

class Crime;
std::stringstream& operator>>(std::stringstream& strstr, Crime& obj);

class Crime
{
private:
	int violation;
	std::string place;
	tm time;
public:
	int get_violation() const
	{
		return violation;
	}
	const std::string& get_place() const
	{
		return place;
	}
	std::string get_time() const
	{
		char string_time[256]{};
		strcpy(string_time, asctime(&time));
		string_time[strlen(string_time) - 1] = NULL;
		return string_time;
	}
	time_t get_timestamp() const
	{
		tm time_copy = time;
		return mktime(&time_copy);
	}
	void set_violation(int violation)
	{
		this->violation = violation;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string time)
	{
		char string_time[256] = {};
		strcpy(string_time, time.c_str());
		// YYYY.MM.DD HH:MM
		int parts[5] = {};
		int n = 0;
		const char* delimeters = ".,/-: ";
		for (char* pch = strtok(string_time, delimeters); pch; pch = strtok(NULL, delimeters))
			parts[n++] = std::atoi(pch);
		this->time = {};
		this->time.tm_year = parts[0] - 1900;
		this->time.tm_mon = parts[1] - 1;
		this->time.tm_mday = parts[2];
		this->time.tm_hour = parts[3];
		this->time.tm_min = parts[4];
	}
	void set_time(time_t time)
	{
		this->time = *localtime(&time);
	}
	Crime(int violation, const std::string& place, const std::string& time)
	{
		set_violation(violation);
		set_place(place);
		set_time(time);
	}
	explicit Crime(const std::string& str)
	{
		std::stringstream stream(str);
		stream >> *this;
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	os.width(44);
	os << std::left;
	return os << obj.get_time() << VIOLATIONS.at(obj.get_violation()) << " " << obj.get_place();
}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << " " << obj.get_violation() << " " << obj.get_timestamp() << " " << obj.get_place();
	return ofs;
}
std::stringstream& operator>>(std::stringstream& strstr, Crime& obj)
{
	int violation;
	strstr >> violation;
	time_t time;
	strstr >> time;
	std::string place;
	std::getline(strstr, place);
	obj.set_violation(violation);
	obj.set_place(place);
	obj.set_time(time);
	return strstr;
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename);
std::map<std::string, std::list<Crime>> load(const std::string filename);

//#define INIT_BASE
//#define INIT_BASE_2
#define LOAD_CHECK

int main()
{
	setlocale(LC_ALL, "");

#ifdef INIT_BASE
	std::map<std::string, std::list<Crime>> base =
	{
		{"А777АА", {Crime(4, "ул. Ленина", 7, 10, 2025, 12, 0, 5), Crime(5, "ул. Ленина", 7, 10, 2025, 13, 21, 32), Crime(7, "ул. Энтузисатов", 7, 10, 2025, 18, 9, 48), Crime(8, "ул. Энтузиастов", 7, 10, 2025, 23, 34, 12)}},
		{"А123ЕН", {Crime(2, "ул. Пролетарская", 1, 10, 2025, 12, 0, 5), Crime(3, "ул. Мира", 1, 10, 2025, 13, 21, 32)}},
		{"А001УТ", {Crime(5, "ул. Октябрьская", 2, 10, 2025, 12, 0, 5), Crime(7, "ул. Космическая", 2, 10, 2025, 13, 21, 32)}}
	};
	print(base);
	save(base, "base.txt");
#endif // INIT_BASE

#ifdef INIT_BASE_2
	std::map<std::string, std::list<Crime>> base =
	{
		{"А777АА", {Crime(4, "ул. Ленина", "2025.10.07 12:05"), Crime(5, "ул. Ленина", "2025.01.06 13:21"), Crime(7, "ул. Энтузисатов", "2025.10.07 22:05"), Crime(8, "ул. Энтузиастов", "2025.10.08 00:05")}},
		{"А123ЕН", {Crime(2, "ул. Пролетарская", "2025.11.07 12:05"), Crime(3, "ул. Мира", "2025.10.06 14:55")}},
		{"А001УТ", {Crime(5, "ул. Октябрьская", "2025.10.07 16:05"), Crime(7, "ул. Космическая", "2025.01.16 12:14")}}
	};
	print(base);
	save(base, "base.txt");
#endif // INIT_BASE

#ifdef LOAD_CHECK
	std::map<std::string, std::list<Crime>> base = load("base.txt");
	print(base);
#endif // LOAD_CHECK

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
		fout << plate->first << ":";
		for (std::list<Crime>::const_iterator violation = plate->second.begin(); violation != plate->second.end(); ++violation)
		{
			fout << *violation << ",";
		}
		fout << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}
std::map<std::string, std::list<Crime>> load(const std::string filename)
{
	std::map<std::string, std::list<Crime>> base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string license_plate;
			std::getline(fin, license_plate, ':');
			const int SIZE = 1024 * 512;
			char all_crimes[SIZE];
			fin.getline(all_crimes, SIZE);
			cout << license_plate << tab;
			cout << all_crimes << endl;
			const char* delimeters = ",";
			for (char* pch = strtok(all_crimes, delimeters); pch; pch = strtok(NULL, delimeters))
				base[license_plate].push_back(Crime(pch));
		}
	}
	else std::cerr << "Error: File not found" << endl;
	fin.close();
	return base;
}