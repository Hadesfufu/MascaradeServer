#ifndef SINGLETON_H
#define SINGLETON_H

#include "Log.h"
#include <memory>
////////////////////////////////////////////////////////////
//
//-------------------BY HadesFufu---------------------
// >French<
//Utilisation : Permet d'avoir acces a une unique instance de la classe. 
//
//Fonctionnement : stocke un pointeur vers sa propre classe. 
//
////////////////////////////////////////////////////////////

template<class T>
class Singleton
{
public:

	////////////////////////////
	// Destructor
	////////////////////////////
	virtual ~Singleton(){};

	////////////////////////////
	// function : if the instance doesn't exist : it creates it.
	// @return : return current instance.
	////////////////////////////
	static T*		getInstance(){
		if (!m_Instance){
			m_Instance = new T();
		}
		return m_Instance;
	};

	static T*		I(){
		return getInstance();
	}
	
	static void		clearInstance(){
		delete m_Instance;
	}
protected:

	////////////////////////////
	// Constructor
	////////////////////////////
	Singleton(){};

private:

	////////////////////////////
	// Instance
	////////////////////////////
	static T*				m_Instance;
};

template<class T>
T*	Singleton<T>::m_Instance = nullptr;

#endif
