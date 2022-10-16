#pragma once

namespace owd
{
    /// @brief Singleton class of application
    class c_app
    {
        public:
        inline static c_app &get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_app)); }

        protected:
        static c_app *m_singleton;
    
    };
} // namespace owd
