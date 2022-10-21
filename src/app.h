#pragma once
#include "window.h"
#include "shader/shader.h"

namespace owd
{
    /// @brief Singleton class of application.
    class c_app
    {
        public:
        /// <summary>
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_app& get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_app)); }

        /// <summary>
        /// Start updating the window.
        /// </summary>
        inline void run() { m_window->run(); }

        /// <summary>
        /// Terminate the app. Close the window, terminate GLFW and delete this class singleton object.
        /// get() will be required to use this class further.
        /// </summary>
        void terminate();

        /// <summary>
        /// Get reference to window.
        /// </summary>
        /// <returns></returns>
        inline const c_window& get_window() { return *m_window; }

        c_app(const c_app&) = delete;
        c_app& operator=(const c_app&) = delete;

        protected:
        c_window* m_window;
        c_shaders* m_shaders;

        c_app();
        ~c_app();

        static c_app* m_singleton;
    };
} // namespace owd
