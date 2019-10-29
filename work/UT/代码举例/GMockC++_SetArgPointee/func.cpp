#include"func.h"
#include"setting.h"
#include<iostream>
using namespace std;

int FUNC::divide(int a,int b)
{
    Setting *set = new Setting;
    int aa[5]={0};
    set->get(aa,5);
    for(int i=0;i<5;++i)cout<<"***********************a[i]***************"<<aa[i]<<"**************"<<endl;
		int *p=aa;
		set->get(p);
		cout<<"------------------------get(*p)中*p is-----------------------"<<*p<<"----------"<<endl;
		return 0;
}

