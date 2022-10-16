#include "window.h"

using namespace std;
using namespace owd;

int main(int32_t arg_count, char *args[])
{
    c_window &window = c_window::get();

    // window->init(500, 500, "window", { {GLFW_CLIENT_API, GLFW_NO_API} });
    window.init();

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    window.process();

    window.terminate();
    
    window.close();
    
    return 0;
}
