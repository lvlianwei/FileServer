#include <testIServiceManager.h>



namespace android {

SingletonSmtIService::SingletonSmtIService(){
}


SingletonSmtIService* SingletonSmtIService::instance = NULL;
SingletonSmtIService* SingletonSmtIService::getInstance(){
	if (NULL == instance)
	{
		instance = new SingletonSmtIService();
	}
	return instance;
}
void SingletonSmtIService::delInstance(){
	if (NULL != instance)
	{
		delete instance;
		instance = NULL;
	}
}
IBinder* IServiceManager::onAsBinder()
{
	return NULL;
}

bool  IServiceManager::checkServiceDiedBefore( const char* name)
{
	printf("-------------sp<IServiceManager> checkServiceDiedBefore()--------------------\n");
	return (SingletonSmtIService::getInstance())->checkServiceDiedBefore(name);
}

sp<IServiceManager> defaultServiceManager()
{
    sp<IServiceManager>prt = new IServiceManager();
	printf("-------------sp<IServiceManager> defaultServiceManager()-----success!----------\n");
    return prt;
}


}

