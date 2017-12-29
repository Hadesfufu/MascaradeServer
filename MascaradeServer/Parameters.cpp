#include "Parameters.h"

Parameters::Parameters()
{
	load();
}
Parameters::~Parameters()
{
	m_doc.save_file("data/param.ini");
	m_datas.clear();
}

void Parameters::load(void){
	std::string path("data/param.ini");
	if (!m_doc.load_file(path.c_str())){
		Log::error("Parameters") << "Unable to open the parameters file";
		return;
	}
	m_root = m_doc.first_child();
}

void Parameters::save(){
	m_doc.save_file("data/param.ini");
}

void Parameters::set(std::string paramName, int value){
	pugi::xml_node elem = m_root.child(paramName.c_str());
	if (elem){
		elem.first_attribute().set_value(value);
	}

	if (get<int>(paramName)){
		m_datas[paramName] = std::make_shared<int>(value);
	}
}
void Parameters::set(std::string paramName, float value){
	pugi::xml_node elem = m_root.child(paramName.c_str());
	if (elem){
		elem.first_attribute().set_value(value);
	}

	if (get<float>(paramName)){
		m_datas[paramName] = std::make_shared<float>(value);
	}
}
void Parameters::set(std::string paramName, unsigned int value){
	pugi::xml_node elem = m_root.child(paramName.c_str());
	if (elem){
		elem.first_attribute().set_value(value);
	}

	if (get<unsigned int>(paramName)){
		m_datas[paramName] = std::make_shared<unsigned int>(value);
	}
}
void Parameters::set(std::string paramName, double value){
	pugi::xml_node elem = m_root.child(paramName.c_str());
	if (elem){
		elem.first_attribute().set_value(value);
	}

	if (get<double>(paramName)){
		m_datas[paramName] = std::make_shared<double>(value);
	}
}
