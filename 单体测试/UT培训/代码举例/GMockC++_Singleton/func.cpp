#include"func.h"
#include"setting.h"
#include<iostream>
using namespace std;


int FUNC::divide(int a,int b)
{
    Setting *set = new Setting;
    int retsize = 0;
    if(set->get(1,retsize))
    {
        cout<<"----------------------------FUNC::divide---------------retsize="<<retsize<<endl;
        if(retsize>100)
        {
            cout<<"----------------------------true----------if--------"<<retsize<<endl;
            return a/b;
        }
        else
        {
            cout<<"----------------------------true------------else----------"<<retsize<<endl;
            return 88;
        }
    }
    else
    {
        cout<<"----------------------------false----------------------"<<retsize<<endl;
        return 77;
    }
}

