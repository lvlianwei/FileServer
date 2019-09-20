#include"SmartIosTool.h"
using namespace goni;
int main() {
    static const char *serinum1 = "64a7a56e10b49abbc512bd377c798808ea12026f"; 
    static const char *serinum2 = "3eefc48c61c4fc48bc8d98f6dfa8717e2ff97a5e"; 
    int status = SmartIosTool::getInstance()->searchPopDevice(serinum1);
    SMTLOGD("status = %d",status);
    status = SmartIosTool::getInstance()->searchPopDevice(serinum2);
    SMTLOGD("status = %d",status);
    return 0;
}
