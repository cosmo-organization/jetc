# jetc

Supported type of short,float,char,bool,int,double,long,long long,std::string,std::map,std::list,std::pair,std::vector,std::array
from example in src/test.cpp

* Combine any possibility with given above supported types
* for example
* std::map<std::string,std::vector<std::string>> complexTypes;
* std::vector<std::map<std::string,std::vector<int>>> veryComplexTypes;
* Any types you can combine
* For defining custom types an example given below printing output std::ostream operator<< overload is optional 
* but two with SerializedBufferStream >> and << is mendatory
* just include jetc.hpp and use it 
