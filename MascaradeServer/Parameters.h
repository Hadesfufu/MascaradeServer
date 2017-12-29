////////////////////////////////////////////////////////////
// < Fichier : "Parameters.h"> 
// < Author : Yohan "HadesFufu" Masson >
////////////////////////////////////////////////////////////

#ifndef PARAMETERS_H
#define PARAMETERS_H


#include <map>
#include <memory>
#include "Log.h"
#include "external\pugixml\pugixml.hpp"
#include "Singleton.h"

class Parameters : public Singleton<Parameters>
{
	friend class Singleton < Parameters > ;
public:
	
	template<class T>
	const T* get(std::string& s){
		auto it = m_datas.find(s);
		if (it != m_datas.end()){
			return convert<T>(it);
		}
		else{
			if (load<T>(s))
				return convert<T>(m_datas.find(s));
			else
				return nullptr;
		}
	}

	template<class T>
	const T* get(char* c){
		return get<T>(std::string(c));
	}

	template<class T>
	const T* convert(std::map< std::string, std::shared_ptr<void>>::iterator& it){
		T* result;
		try{
			result = static_cast<T*>(it->second.get());
		}
		catch (...){
			Log::error("Parameters") << "Error on convertion";
			return nullptr;
		};
		return result;
	}

	void save();

	void set(std::string paramName, int value);
	void set(std::string paramName, float value);
	void set(std::string paramName, unsigned int value);
	void set(std::string paramName, double value);

private:
	 Parameters();
	~Parameters();

	void load(); // load all parameters
	
	template< class T >
	const void* load(std::string& s){
		pugi::xml_node elem = m_root.child(s.c_str());
		std::shared_ptr<void> ptr(nullptr);
		if (!elem)
			return nullptr;

		if (typeid(T).hash_code() == typeid(int).hash_code())
			ptr = std::make_shared<int>((int)elem.first_attribute().as_int());
		
		else if (typeid(T).hash_code() == typeid(float).hash_code())
			ptr = std::make_shared<float>((float)elem.first_attribute().as_float());

		else if (typeid(T).hash_code() == typeid(double).hash_code())
			ptr = std::make_shared<double>((double)elem.first_attribute().as_double());

		else if (typeid(T).hash_code() == typeid(unsigned int).hash_code())
			ptr = std::make_shared<unsigned int>((unsigned int)elem.first_attribute().as_uint());
			
		else if (typeid(T).hash_code() == typeid(std::string).hash_code())
			ptr = std::make_shared<std::string>((std::string)elem.first_attribute().as_string());
		
		if (!ptr)
			return nullptr;


		m_datas.insert(m_datas.begin(), std::pair<std::string, std::shared_ptr<void>>(s, ptr));
		return m_datas[s].get();
	}

	////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////

	std::map< std::string, std::shared_ptr<void> > m_datas;

	pugi::xml_node m_root;
	pugi::xml_document m_doc;
};
#endif 