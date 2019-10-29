#include<string>
#include<map>
#include<stdio.h>
#include "servicebase/SystemLog.h"
using namespace std;
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

std::map<string,string> iosDevInfos;
void mset(string key,string value)    /* __0x401001_DTFUNCID__ */ {
     //iosDevInfos.insert(make_pair(key,value));
     iosDevInfos[key] = value;
    // printf("size %d,mset,key %s,value %s\n",iosDevInfos.size(),key.c_str(),value.c_str());
}
void mget(string key,string & value)    /* __0x401002_DTFUNCID__ */ {
   // printf("size %d\n",iosDevInfos.size());
    value = iosDevInfos[key];
   // printf("mget,key %s,value %s\n",key.c_str(),value.c_str());
}
}
