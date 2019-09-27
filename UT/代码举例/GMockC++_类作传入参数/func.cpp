#include"func.h"
#include"setting.h"
#include<iostream>
using namespace std;
int FUNC::addORmin(Setting *set)
{
    if(NULL == set)
        {
		cout<<"----------------------set is NULL----------------------"<<endl;
		return 8888;
	}
    else
         {
		cout<<"--------set is not NULL------set.m_state is--------"<<set->m_state<<endl;
		if(set->get())
		{
			return 7777;
		}
	}
}

