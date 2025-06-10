#pragma once

#include <unordered_map>
#include "WinDef.hpp"
#include "Convertor.hpp"

namespace WinCore::Core
{
    class WindowClass
    {
        public:
            /**
             * Constructs a WindowClass object with the specified class name and instance handle.
             * @param className The name of the window class.
             * @param instance The instance handle associated with the window class.
             * @param styles The styles to apply to the window class (default is WindowStyles::None).
             * @param extendedStyles The extended styles to apply to the window class (default is WindowExtenedStyle::None).
             */
            explicit WindowClass(const std::string& className, HandleInstance instance);

            /**
             * Constructs a WindowClass object with the specified class name, instance handle, styles, and extended styles.
             * @param className The name of the window class.
             * @param instance The instance handle associated with the window class.
             * @param styles The styles to apply to the window class (default is WindowStyles::None).
             * @param extendedStyles The extended styles to apply to the window class (default is WindowExtenedStyle::None).
             */
            explicit WindowClass(const std::string& className, HandleInstance instance, WindowStyles styles = WindowStyles::None);

            /**
             * Constructs a WindowClass object with the specified class name, instance handle, styles, and extended styles.
             * @param className The name of the window class.
             * @param instance The instance handle associated with the window class.
             * @param styles The styles to apply to the window class (default is WindowStyles::None).
             * @param extendedStyles The extended styles to apply to the window class (default is WindowExtenedStyle::None).
             */
            explicit WindowClass(const std::string& className, HandleInstance instance, WindowStyles styles = WindowStyles::None, WindowExtenedStyle extendedStyles = WindowExtenedStyle::None);     

            /**
             * Destructor for the WindowClass object.
             * Cleans up any resources associated with the window class.
             */
            ~WindowClass() = default;

            /**
             * Returns the name of the window class.
             * @return The name of the window class as a constant reference to a std::wstring.
             */
            [[nodiscard]] const std::wstring& GetName() const noexcept { return className_; }

            /**
             * Returns the instance handle associated with the window class.
             * @return The instance handle as a HandleInstance.
             */
            [[nodiscard]] HandleInstance GetInstance() const noexcept { return instance_; }

            /**
             * Returns the styles applied to the window class.
             * @return The styles as a WindowStyles.
             */
            [[nodiscard]] WindowStyles GetStyles() const noexcept { return styles_; }

            /**
             * Returns the extended styles applied to the window class.
             * @return The extended styles as a WindowExtenedStyle.
             */
            [[nodiscard]] WindowExtenedStyle GetExtendedStyles() const noexcept { return extendedStyles_; }
            

        private:
            std::wstring className_;                //< The name of the window class.
            HandleInstance instance_;               //< The instance handle associated with the window class.
            WindowStyles styles_;                   //< The styles applied to the window class.
            WindowExtenedStyle extendedStyles_;     //< The extended styles applied to the window class.
    };

    class WindowRegistry
    {
        public:
            /**
             * Registers a window class with the Windows API.
             * @param windowClass The WindowClass object to register.
             * @throws std::runtime_error If the registration fails.
             */
            static void Register(const WindowClass& windowClass);

            /**
             * Unregisters a window class from the Windows API.
             * @param windowClass The WindowClass object to unregister.
             * @throws std::runtime_error If the unregistration fails.
             */
            static void Unregister(const WindowClass& windowClass);

            /**
             * Checks if a window class is already registered.
             * @param className The name of the window class to check.
             * @return True if the class is registered, false otherwise.
             */
            static bool IsRegistered(const std::string& className);
    };

}