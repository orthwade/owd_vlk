#include "app.h"
#include "glfw_error.h"

using namespace std;
using namespace owd;

int main(int32_t arg_count, char *args[])
{
    c_logger::set_global_mode_both();
    c_logger::ptr logger_ptr_ = c_logger::make(L"Ëמדדונ");

    c_logger& logger_ = *logger_ptr_;

    c_app& app_ = c_app::get();
    
    glfwPlatformSupported(188888);
    c_glfw_errors& errors_ = c_glfw_errors::get();

    //errors_.print_last_error();
    //app_.run();
    glfwWindowHint(2, 99);

    app_.terminate();
   
    //auto& m = c_glfw_init::get();
   

    c_singleton::terminate_all_singletons();


    glfwCreateStandardCursor(1);
    return 0;
}
