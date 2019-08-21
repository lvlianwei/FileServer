#include"setting.h"

Singleton::Singleton(){
}

Singleton::Singleton(const Singleton&){

}

Singleton& Singleton::operator=(const Singleton&){

}
Singleton* Singleton::instance = NULL;
Singleton* Singleton::getInstance(){
	if (NULL == instance)
	{
		instance = new Singleton();
	}
	return instance;
}
void Singleton::delInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}
