#pragma once

#include <memory>

#include "WinDef.hpp"
#include "WinClass.hpp"

namespace WinCore::Core
{
    enum class MessageBoxIcon : uint32_t
    {
        None = 0,                           //< No icon is displayed.
        Information = MB_ICONINFORMATION,   //< Displays an information icon.
        Warning = MB_ICONWARNING,           //< Displays a warning icon.
        Error = MB_ICONERROR,               //< Displays an error icon.
        Question = MB_ICONQUESTION          //< Displays a question mark icon.
    };

    enum class MessageBoxButton : uint32_t
    {
        OK = MB_OK,                          //< Displays an OK button.
        OKCancel = MB_OKCANCEL,              //< Displays OK and Cancel buttons.
        YesNo = MB_YESNO,                    //< Displays Yes and No buttons.
        YesNoCancel = MB_YESNOCANCEL         //< Displays Yes, No, and Cancel buttons.
    };

    enum class MessageBoxResult : int32_t
    {
        OK = IDOK,                            //< The user clicked the OK button.
        Cancel = IDCANCEL,                    //< The user clicked the Cancel button.
        Yes = IDYES,                          //< The user clicked the Yes button.
        No = IDNO,                            //< The user clicked the No button.
        Retry = IDRETRY,                      //< The user clicked the Retry button.
        Ignore = IDIGNORE                     //< The user clicked the Ignore button.
    };

    /**
     * Combines two MessageBoxIcon enum values using a bitwise OR operation.
     * @param lhs The left-hand side MessageBoxIcon value.
     * @param rhs The right-hand side MessageBoxIcon value.
     * @return A uint32_t value representing the combination of the input values.
     */
    inline uint32_t operator|(MessageBoxIcon lhs, MessageBoxIcon rhs)
    {
        return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
    }

    /**
     * Combines two MessageBoxButton enum values using a bitwise OR operation.
     * @param lhs The left-hand side MessageBoxButton value.
     * @param rhs The right-hand side MessageBoxButton value.
     * @return A uint32_t value representing the combination of the input values.
     */
    inline uint32_t operator|(MessageBoxButton lhs, MessageBoxButton rhs)
    {
        return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
    }

    /**
     * Combines a MessageBoxIcon enum value and a MessageBoxButton enum value using a bitwise OR operation.
     * @param icon The MessageBoxIcon value to combine.
     * @param button The MessageBoxButton value to combine.
     * @return A uint32_t value representing the combination of the input values.
     */
    inline uint32_t operator|(MessageBoxIcon icon, MessageBoxButton button)
    {
        return static_cast<uint32_t>(icon) | static_cast<uint32_t>(button);
    }

    /**
     * @class MsgBox
     * @brief Represents a message used for internal communication.
     *
     * The MsgBox class provides mechanisms for handling messages
     * within the system. It is not copyable or movable to ensure
     * message integrity.
     */
    class MsgBox
    {
        /**
         * [Challenge-Time]
         * I can not think of a better name for this class.
         * because MessageBox is already used in the Windows API.
         * So, any suggestion for a better name is welcome.
         */
        
        private:
            MsgBox() = default;  
            ~MsgBox() = default; 

            MsgBox(const MsgBox&) = delete;           
            MsgBox& operator=(const MsgBox&) = delete; 
            MsgBox(MsgBox&&) = delete;                 
            MsgBox& operator=(MsgBox&&) = delete;      

        public:
            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(const wchar_t* text, const wchar_t* title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            
            static MessageBoxResult Show(const char* text, const char* title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(const std::wstring& text, const std::wstring& title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(const std::string& text, const std::string& title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            
            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param windowHandle The handle of the window to associate with the message box.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(WindowHandle windowHandle, const wchar_t* text, const wchar_t* title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param windowHandle The handle of the window to associate with the message box.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(WindowHandle windowHandle, const char* text, const char* title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param windowHandle The handle of the window to associate with the message box.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(WindowHandle windowHandle, const std::wstring& text, const std::wstring& title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);

            /**
             * Displays a message box with the specified text, title, icon, buttons, default button, and mode.
             * @param windowHandle The handle of the window to associate with the message box.
             * @param text The text to display in the message box.
             * @param title The title of the message box.
             * @param icon The icon to display in the message box.
             * @param buttons The buttons to display in the message box.
             * @return The result of the message box (e.g., which button was clicked).
             */
            static MessageBoxResult Show(WindowHandle windowHandle, const std::string& text, const std::string& title,
                                         MessageBoxIcon icon = MessageBoxIcon::None,
                                         MessageBoxButton buttons = MessageBoxButton::OK);
    };

    /**
     * @class Monitor
     * @brief Provides information about the monitors connected to the system.
     *
     * The Monitor class provides methods to retrieve information about the monitors,
     * including DPI awareness, work area, area, and DPI scaling.
     */
    class Monitor
    {
        public:
            /**
             * @enum DPIAwareness
             * @brief Represents the DPI awareness of a monitor.
             *
             * This enum defines the different DPI awareness that can be set for a monitor.
             * It is used to determine how the application should handle DPI scaling.
             */
            enum class DPIAwareness : int32_t
            {
                Unaware = -1,                //< DPI awareness is not set.
                SystemAware = 0,             //< DPI awareness is system-wide.
                PerMonitorAware = 1,         //< DPI awareness is per-monitor.
                PerMonitorAwareV2 = 2,       //< Enhanced per-monitor DPI awareness.
                UnawareGDIScaled = 3         //< GDI scaling is applied but not per-monitor aware.
            };

            /**
             * @struct MonitorWorkArea
             * @brief Represents the work area of a monitor.
             *
             * This structure contains the coordinates of the monitor's work area,
             * which is the area available for application windows, excluding taskbars and docked windows.
             */
            struct MonitorWorkArea
            {
                long Top{0};        //< The top coordinate of the monitor's work area.
                long Left{0};       //< The left coordinate of the monitor's work area.
                long Right{0};      //< The right coordinate of the monitor's work area.
                long Bottom{0};     //< The bottom coordinate of the monitor's work area.
            };

            /**
             * @struct MonitorArea
             * @brief Represents the area of a monitor.
             *
             * This structure contains the coordinates of the monitor's area,
             * which includes the entire screen space available on the monitor.
             */
            struct MonitorArea
            {
                long Top{0};        //< The top coordinate of the monitor's area.
                long Left{0};       //< The left coordinate of the monitor's area.
                long Right{0};      //< The right coordinate of the monitor's area.
                long Bottom{0};     //< The bottom coordinate of the monitor's area.
            };

            /**
             * @struct MonitorDPIScaling
             * @brief Represents the DPI scaling factors for a monitor.
             *
             * This structure contains the horizontal and vertical DPI scaling factors,
             * which are used to scale UI elements appropriately on high-DPI displays.
             */
            struct MonitorDPIScaling
            {
                uint32_t X{0};      //< The horizontal DPI scaling factor.
                uint32_t Y{0};      //< The vertical DPI scaling factor.
            };

            /**
             * @struct MonitorInfo
             * @brief Represents information about a monitor.
             *
             * This structure contains various properties of a monitor,
             * including its name, work area, area, DPI scaling, awareness,
             * dimensions, refresh rate, color depth, and support for high DPI and HDR.
             */
            struct MonitorInfo
            {
                std::wstring MonitorName{L"undefined"};                 //< The name of the monitor.
                MonitorWorkArea WorkArea{};                             //< The work area of the monitor.
                MonitorArea Area{};                                     //< The area of the monitor.
                MonitorDPIScaling DPIScaling{};                         //< The DPI scaling of the monitor.
                DPIAwareness Awareness{DPIAwareness::Unaware};          //< The DPI awareness of the monitor.

                uint32_t Width{0};                            //< The width of the monitor in pixels.
                uint32_t Height{0};                           //< The height of the monitor in pixels.
                uint32_t RefreshRate{0};                      //< The refresh rate of the monitor in Hz.
                uint32_t BitsPerPixel{0};                     //< The color depth of the monitor in bits per pixel.
                bool IsPrimary{false};                        //< Indicates if the monitor is the primary monitor. 
                bool IsSupportHightDPI{false};                //< Indicates if the monitor supports high DPI scaling.
                
                MonitorInfo() = default;  
                ~MonitorInfo() = default; 
            };

        private:
            Monitor() = default;  
            ~Monitor() = default; 

            Monitor(const Monitor&) = delete;           
            Monitor& operator=(const Monitor&) = delete; 
            Monitor(Monitor&&) = delete;                 
            Monitor& operator=(Monitor&&) = delete;

        public:          
            /**
             * @brief Sets the DPI awareness of the application.
             * @param awareness The DPI awareness to set for the application.
             *
             * This function sets the DPI awareness of the application,
             * which determines how the application handles DPI scaling on high-DPI monitors.
             */
            static void SetProcessDPIAwareness(DPIAwareness awareness);

            /**
             * @brief Gets the current DPI awareness of the application.
             * @return The current DPI awareness of the application.
             *
             * This function retrieves the DPI awareness of the application,
             * which indicates how the application handles DPI scaling on high-DPI monitors.
             */
            static DPIAwareness GetProcessDPIAwareness();

            /**
             * @brief Gets the DPI awareness of the system.
             * @return The DPI awareness of the system.
             *
             * This function retrieves the DPI awareness of the system,
             * which indicates how the system handles DPI scaling on high-DPI monitors.
             */
            static DPIAwareness GetSystemDPIAwareness();

            /**
             * @brief Gets the DPI scaling of the primary monitor.
             * @return A MonitorDPIScaling object containing the DPI scaling factors for the primary monitor.
             *
             * This function retrieves the DPI scaling factors (X and Y) for the primary monitor,
             * which are used to scale UI elements appropriately on high-DPI displays.
             */
            static std::shared_ptr<MonitorInfo> GetPrimaryMonitor();
    };
}