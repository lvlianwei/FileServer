#include"func.h"
#include"setting.h"
#include<iostream>
using namespace std;
int FUNC::addORmin(int a,int b)
{
    Setting *set = new Setting;
    if(set->get())
    {
        cout<<"----------------------------FUNC::divide---------------return is true "<<endl;
        return a+b;
    }
    else
    {
        cout<<"----------------------------FUNC::divide---------------return is false "<<endl;
        return a-b;
    }
}
bool FUNC::get()
{
    return false;
}

int FUNC::divide(int a,int b)
{
    Setting *set = new Setting;
    int retsize = 0;
    string size = "hello";
    char ch ='q';
    int *p=set->getptr();//测试返回值为int*类型
    if(NULL == p)
        cout<<"------------------------------Return is NULL--------------------------"<<endl;
    else
        cout<<"------------------------Return is -----------------------"<<*p<<"----------"<<endl;
    if(set->get(size,retsize,ch))//测试输出参数为string，int，char
    {
        cout<<"----------------------------FUNC::divide---------------retsize="<<retsize<<endl;
        cout<<"----------------------------string----------------------"<<size<<"------------"<<endl;
        cout<<"----------------------------char------------------------"<<ch<<"--------------"<<endl;

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
        cout<<"----------------------------string----------------------"<<size<<"------------"<<endl;
        cout<<"----------------------------char------------------------"<<ch<<"--------------"<<endl;
        return 77;
    }
}

