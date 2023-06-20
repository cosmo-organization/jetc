#include "jetc.hpp"
/**
*Supported type of short,float,char,bool,int,double,long,long long,std::string,std::map,std::list,std::pair,std::vector,std::array
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
	std::array<int, 2> twoFavNumber;

	Person(std::string name, std::string favColor, std::string address, int age, int houseNumber, int carNumber) {
		this->name = name;
		this->favColor = favColor;
		this->address = address;
		this->age = age;
		this->houseNumber = houseNumber;
		this->carNumber = carNumber;
	}

	Person(){
		
	}
	
	//Mendatory implementation
	friend jetc::SerializedBufferStream& operator<<(jetc::SerializedBufferStream& out, Person& person) {
		out << person.name << person.favColor << person.address << person.age << person.houseNumber << person.carNumber<<person.favTeachers<<person.twoFavNumber;
		return out;
	}
	//Mendatory implementation
	friend jetc::SerializedBufferStream& operator>>(jetc::SerializedBufferStream& in, Person& person) {
		in >> person.name >> person.favColor >> person.address >> person.age >> person.houseNumber >> person.carNumber>>person.favTeachers>>person.twoFavNumber;
		return in;
	}

	//Optional for output
	friend std::ostream& operator<<(std::ostream& ostream, Person& person) {
		ostream << "Person{name:" << person.name << ",favColor:" << person.favColor << ",address:" << person.address << ",age:" << person.age << ",houseNumber:" << person.houseNumber << ",carNumber:" << person.carNumber<<",favTeachers:"<<person.favTeachers<<",twoFavNumber:["<<person.twoFavNumber.front()<<","<<person.twoFavNumber.back() << "]}";
		return ostream;
	}
	//Optional for any other overloads
	friend std::ostream& operator<<(std::ostream& ostream, std::vector<Person>& vecs) {
		ostream << "[";
		if (!vecs.empty()) {
			int len =(int) vecs.size();
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
		std::vector<Person> favTeachers = { Person("Walter Levin","Don't know","I think Near MIT",87,-1,-1) };
		sonu.favTeachers = favTeachers;
		sonu.twoFavNumber = {22,30};
		
		jetc::SerializedBufferStream sbs = jetc::serialize(sonu);


		Person result = jetc::deserialize<Person>(sbs);


		std::array<int, 65> kk{ 65,66,66,67 };

		jetc::SerializedBufferStream bufferOut = jetc::serialize(kk);

		std::cout << bufferOut << std::endl;

		std::array<int, 65> recovery;

		recovery = jetc::deserialize<decltype(recovery)>(bufferOut);

		for (int element : recovery) {
			std::cout << element << std::endl;
		}

	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

}
