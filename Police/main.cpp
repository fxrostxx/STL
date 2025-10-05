#include <iostream>
#include <map>
#include <list>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class PoliceDatabase
{
private:
	std::map<std::string, std::list<std::string>> database;
	std::string license_plate_number;
	std::list<std::string> fines;
public:
	PoliceDatabase()
	{
		cout << "PDDefaultConstructor: " << this << endl;
	}
	PoliceDatabase(const PoliceDatabase& other)
	{
		*this = other;
		cout << "PDCopyConstructor: " << this << endl;
	}
	PoliceDatabase(const PoliceDatabase&& other)
	{
		*this = std::move(other);
		cout << "PDMoveConstructor: " << this << endl;
	}
	PoliceDatabase(const std::initializer_list<std::string>& string_il, const std::initializer_list<std::list<std::string>>& list_il)
	{
		for (std::string const* string_it = string_il.begin(); string_it != string_il.end(); ++string_it)
		{
			//database.insert((std::map<std::string, std::list<std::string>>::iterator)*string_it, );
		}
	}
	~PoliceDatabase()
	{
		database.clear();
		license_plate_number.clear();
		fines.clear();
		cout << "PDDestructor: " << this << endl;
	}

	PoliceDatabase& operator=(const PoliceDatabase& other)
	{
		if (this == &other) return *this;
		database.clear();
		for (std::map<std::string, std::list<std::string>>::iterator* it = other.database.begin(); it != other.database.end(); ++it)
		{

		}
	}
};