////////////////////////////////////////////////////////////
// < Fichier : "Parameters.h"> 
// < Author : Yohan "HadesFufu" Masson >
////////////////////////////////////////////////////////////

#ifndef PARAMETERS_H
#define PARAMETERS_H


#include <map>
#include <memory>
#include "Log.h"
#include "json.hpp"
#include "Singleton.h"
#include <fstream>

using json = nlohmann::json;

class Parameters : public Singleton<Parameters>
{
	friend class Singleton < Parameters > ;
public:
	
	json& getJson() { return m_json; };

private:
	 Parameters();
	~Parameters();

	void load(); // load all parameters

	////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////
	
	json m_json;
	std::fstream m_fileStream;
};
#endif 