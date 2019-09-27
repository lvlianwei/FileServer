#include "servicebase/ServiceProcess.h"
#include "SmartIosService.h"
#include "SmartIosServiceStub.h"

using namespace goni;
using namespace android;

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    goni::ServiceProcess process("smartios");

    SmartIosService *smartIosServiceStub = new SmartIosService();

    process.addService(smartIosServiceStub);

    process.initialize();
    process.exec();

    process.finalize();

    return 0;
}
