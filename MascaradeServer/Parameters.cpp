#include "Parameters.h"

Parameters::Parameters()
{
	load();
}
Parameters::~Parameters()
{
	m_fileStream << m_json;
	m_fileStream.close();
}

void Parameters::load(void){
	//std::string path("D:/Users/Hades/Source/Repos/MascaradeServer/MascaradeServer/param.ini");
	try {
		m_fileStream.open("param.ini", std::fstream::in | std::fstream::out);
		if (!m_fileStream.is_open())
			Log::error("Parameters::load") << "file not found";
		m_fileStream >> m_json;
	}
	catch(std::fstream::failure e)
	{
		Log::debug("Parameters::load") << "Error while opening the file" << e.what();
	}
	Log::debug();
}
