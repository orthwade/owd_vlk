#include "app.h"

using namespace std;
using namespace owd;

int main(int32_t arg_count, char *args[])
{
    c_app& app_ = c_app::get();

    app_.run();

    app_.terminate();
    
    return 0;
}
