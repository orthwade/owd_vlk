#include "app.h"

using namespace std;
using namespace owd;

int main(int32_t arg_count, char *args[])
{
    c_logger::ptr logger_ptr_ = c_logger::make(L"Логгер", c_logger::both);

    c_logger& logger_ = *logger_ptr_;

    logger_ << "" << "1111" << L"фвлаыщщоа\n" << L"q34rq3f\n" << L"ФЫвщлфЦЩЛлв\n";
    
    c_app& app_ = c_app::get();

    //app_.run();

    app_.terminate();

    string str_1_{ "String 1" };
    string str_2_{ "String 1" };
    string str_3_{ "String 2" };

    wstring w_str_1_{ L"Строка 1" };
    wstring w_str_2_{ L"Строка 1" };
    wstring w_str_3_{ L"Строка 3" };
    wstring w_str_4_{ L"String 1" };

    wstring w_str_5_{ convert_utf8_to_utf16(str_1_) };

    std::wcout << w_str_5_ << '\n';
    std::wcout << w_str_2_ << '\n';
    //std::cout << str_2_ << '\n';
    std::wcout << w_str_2_ << '\n';

    return 0;
}
