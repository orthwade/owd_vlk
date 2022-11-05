#include "app.h"
#include "glfw_error.h"

using namespace std;
using namespace owd;

int main(int32_t arg_count, char *args[])
{
    std::wstring ww_ = current_date_wstr();

    c_logger::set_global_mode_both();

    c_logger::ptr logger_ptr_ = c_logger::make(L"Ëמדדונ");

    c_logger& logger_ = *logger_ptr_;

    c_app& app_ = c_app::get();
    
    c_glfw_errors& errors_ = c_glfw_errors::get();

    app_.run();

    app_.terminate();
   
    c_singleton::terminate_all_singletons();

    return 0;
}
