#include "servicebase/ServiceProcess.h"
#include "wfdService.h"
#include "wfdServiceStub.h"

using namespace goni;
using namespace android;

int main(int argc, char *argv[])/* __0x000000_DTFUNCID__ */
{
    UNUSED(argc);
    UNUSED(argv);
    goni::ServiceProcess process("service");

    wfdService *wfdServiceStub = new wfdService();

    process.addService(wfdServiceStub);

    process.initialize();
    process.exec();

    process.finalize();

    return 0;
}
