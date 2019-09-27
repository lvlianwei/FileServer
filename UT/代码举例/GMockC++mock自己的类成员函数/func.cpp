#include"func.h"
#include<iostream>
using namespace std;
int FUNC::addORmin(int a,int b)
{
    if(get())
        return a+b;
    else
        return a-b;
}
bool FUNC::get()
{
return false;
}
