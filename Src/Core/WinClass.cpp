#include "WinClass.hpp"

namespace WinCore::Core
{
    static std::unordered_map<std::wstring, HandleInstance> s_registeredClasses{};

    void WindowRegistry::Register(const WindowClass& windowClass)
    {
        WNDCLASS wc = {};
        wc.lpfnWndProc = DefWindowProc; //[TODO]: Replace with actual window procedure function.
        wc.hInstance = windowClass.GetInstance();
        wc.lpszClassName = windowClass.GetName().c_str();
        wc.style = GetNativeWindowStyle(windowClass.GetStyles());
        wc.hCursor = SystemCursors::LoadSystemCursor(SystemCursors::Arrow);
        
        if (!RegisterClass(&wc))
        {
            throw std::runtime_error("Failed to register window class.");
        }

        // Store the registered class in the map
        s_registeredClasses[windowClass.GetName()] = windowClass.GetInstance();
    }

    void WindowRegistry::Unregister(const WindowClass& windowClass)
    {
        if (!UnregisterClass(windowClass.GetName().c_str(), windowClass.GetInstance()))
        {
            throw std::runtime_error("Failed to unregister window class.");
        }

        // Remove the class from the registry
        s_registeredClasses.erase(windowClass.GetName());
    }

    bool WindowRegistry::IsRegistered(const std::string& className)
    {
        std::wstring wideClassName = Utils::Convertor::ToWString(className);
        return s_registeredClasses.find(wideClassName) != s_registeredClasses.end();
    }

    WindowClass::WindowClass(const std::string& className, HandleInstance instance)
    {
        className_ = Utils::Convertor::ToWString(className);
        instance_ = instance;
        styles_ = WindowStyles::None;
        extendedStyles_ = WindowExtenedStyle::None;
    }

    WindowClass::WindowClass(const std::string& className, HandleInstance instance, WindowStyles styles)
    {
        className_ = Utils::Convertor::ToWString(className);
        instance_ = instance;
        styles_ = styles;
        extendedStyles_ = WindowExtenedStyle::None;
    }

    WindowClass::WindowClass(const std::string& className, HandleInstance instance, WindowStyles styles, WindowExtenedStyle extendedStyles)
    {
        className_ = Utils::Convertor::ToWString(className);
        instance_ = instance;
        styles_ = styles;
        extendedStyles_ = extendedStyles;
    }


}