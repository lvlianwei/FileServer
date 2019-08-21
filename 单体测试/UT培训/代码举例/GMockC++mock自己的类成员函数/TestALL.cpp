#include <gmock/gmock.h>
#include<iostream>
using namespace std;
int main(int argc,char** argv)
{
    testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
