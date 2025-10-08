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
	const tm& get_time() const
	{
		return time;
	}
	void set_violation(int violation)
	{
		this->violation = violation;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const tm& time)
	{
		this->time = time;
	}
	void set_time(const int day, const int month, const int year, const int hour, const int minute, const int second)
	{
		time = {};
		time.tm_year = year;
		time.tm_mon = (month > 12 ? 0 : month);
		time.tm_mday = (day > 31 ? 0 : day);
		time.tm_hour = (hour > 23 ? 0 : hour);
		time.tm_min = (minute > 59 ? 0 : minute);
		time.tm_sec = (second > 59 ? 0 : second);
	}
	Crime(int violation, const std::string& place, const int day = 0, const int month = 0, const int year = 0, const int hour = 0, const int minute = 0, const int second = 0)
	{
		set_violation(violation);
		set_place(place);
		set_time(day, month, year, hour, minute, second);
	}
};

std::ostream& operator<<(std::ostream& os, const tm& obj)
{
	/*return os << std::string
	(
		(obj.tm_mday < 10 ? "0" : "") + std::to_string(obj.tm_mday) + "." +
		(obj.tm_mon < 10 ? "0" : "") + std::to_string(obj.tm_mon) + "." +
		std::to_string(obj.tm_year) + " " +
		(obj.tm_hour < 10 ? "0" : "") + std::to_string(obj.tm_hour) + ":" +
		(obj.tm_min < 10 ? "0" : "") + std::to_string(obj.tm_min) + ":" +
		(obj.tm_sec < 10 ? "0" : "") + std::to_string(obj.tm_sec)
	);*/
	return os << (obj.tm_mday < 10 ? "0" : "") << obj.tm_mday << "." <<
				 (obj.tm_mon < 10 ? "0" : "") << obj.tm_mon << "." <<
				 obj.tm_year << " " <<
				 (obj.tm_hour < 10 ? "0" : "") << obj.tm_hour << ":" <<
				 (obj.tm_min < 10 ? "0" : "") << obj.tm_min << ":" <<
				 (obj.tm_sec < 10 ? "0" : "") << obj.tm_sec;
}
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	os.width(44);
	os << std::left;
	return os << VIOLATIONS.at(obj.get_violation()) << " " << obj.get_place() << tab << obj.get_time();
}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_violation() << " " << obj.get_place() << " " << obj.get_time();
	return ofs;
}
std::stringstream& operator>>(std::stringstream& strstr, Crime& obj)
{
	int violation;
	strstr >> violation;
	std::string place;
	std::getline(strstr, place);
	obj.set_violation(violation);
	obj.set_place(place);
	return strstr;
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename);
std::map<std::string, std::list<Crime>> load(const std::string filename);

//#define INIT_BASE

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

	std::map<std::string, std::list<Crime>> base = load("base.txt");
	print(base);

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
			{
				Crime crime(0, "");
				std::stringstream stream(pch);
				stream >> crime;
				base[license_plate].push_back(crime);
			}
		}
	}
	else std::cerr << "Error: File not found" << endl;
	fin.close();
	return base;
}