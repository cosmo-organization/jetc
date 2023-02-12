#include "jetc.hpp"
/**
*Supported type of short,float,char,bool,int,double,long,long long,std::string,std::map,std::list,std::pair,std::vector
* Combine any possibility with given above supported types
* for example
* std::map<std::string,std::vector<std::string>> complexTypes;
* std::vector<std::map<std::string,std::vector<int>>> veryComplexTypes;
* Any types you can combine
* For defining custom types an example given below printing output std::ostream operator<< overload is optional 
* but two with SerializedBufferStream >> and << is mendatory
* just include jetc.hpp and use it 
* @autor Sonu Aryan 
**/
struct Person {
	std::string name;
	std::string favColor;
	std::string address;
	int age;
	int houseNumber;
	int carNumber;
	std::vector<Person> favTeachers;

	Person(std::string name, std::string favColor, std::string address, int age, int houseNumber, int carNumber) {
		this->name = name;
		this->favColor = favColor;
		this->address = address;
		this->age = age;
		this->houseNumber = houseNumber;
		this->carNumber = carNumber;
	}

	Person(){}
	
	//Mendatory implementation
	friend jetc::SerializedBufferStream& operator<<(jetc::SerializedBufferStream& out, Person& person) {
		out << person.name << person.favColor << person.address << person.age << person.houseNumber << person.carNumber<<person.favTeachers;
		return out;
	}
	//Mendatory implementation
	friend jetc::SerializedBufferStream& operator>>(jetc::SerializedBufferStream& in, Person& person) {
		in >> person.name >> person.favColor >> person.address >> person.age >> person.houseNumber >> person.carNumber>>person.favTeachers;
		return in;
	}

	//Optional for output
	friend std::ostream& operator<<(std::ostream& ostream, Person& person) {
		ostream << "Person{name:" << person.name << ",favColor:" << person.favColor << ",address:" << person.address << ",age:" << person.age << ",houseNumber:" << person.houseNumber << ",carNumber:" << person.carNumber<<",favTeachers:"<<person.favTeachers << "}";
		return ostream;
	}
	//Optional for any other overloads
	friend std::ostream& operator<<(std::ostream& ostream, std::vector<Person>& vecs) {
		ostream << "[";
		if (!vecs.empty()) {
			int len = vecs.size();
			len -= 1;
			for (int i = 0; i < len; i++) {
				ostream << vecs.at(i) << ",";
			}
			ostream << vecs.at(vecs.size() - 1) << "]";
		}
		else {
			ostream << "]";
		}
		return ostream;
	}
};

int main()
{
	try {
		Person sonu;
		sonu.name = "Sonu Aryan";
		sonu.favColor = "Blue";
		sonu.address = "Badhi Tola Sherghati";
		sonu.age = 19;
		sonu.houseNumber = 71;
		sonu.carNumber = 3778;
		std::vector<Person> favTeachers= { Person("Walter Levin","Don't know","I think Near MIT",87,-1,-1)};
		sonu.favTeachers = favTeachers;
		std::cout << "Original" << std::endl;
		std::cout << sonu << std::endl;

		jetc::SerializedBufferStream sbs=jetc::serialize(sonu);


		Person result = jetc::deserialize<Person>(sbs);
		std::cout << "Recovered" << std::endl;
		std::cout << result << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}
}
