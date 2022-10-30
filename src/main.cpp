#include "app.h"
#include "glfw_error.h"

using namespace std;
using namespace owd;

int main(int32_t arg_count, char *args[])
{
    c_logger::set_global_mode_both();

    c_logger::ptr logger_ptr_ = c_logger::make(L"ֻמדדונ");

    c_logger& logger_ = *logger_ptr_;

    logger_ << "" << "1111" << L"פגכאûששמא\n" << L"q34rq3f\n" << L"װÛגשכפײÙֻכג\n" << 156 << L'\n';
    logger_ << "11123";
    c_app& app_ = c_app::get();

    //app_.run();

    app_.terminate();
    c_glfw_errors* errors_ = c_glfw_errors::get_ptr();

    c_singleton::terminate_all_singletons();

    return 0;
}
