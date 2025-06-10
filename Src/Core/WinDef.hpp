#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>

namespace WinCore::Core
{
    using Handle = HANDLE;              
    using HandleInstance = HINSTANCE;   
    using CursorHandle = HCURSOR;       
    using IconHandle = HICON;           
    using BrushHandle = HBRUSH;         
    using FontHandle = HFONT;           
    using MenuHandle = HMENU;          
    using WindowHandle = HWND;        

    enum class WindowStyles : uint32_t
    {
        None = NULL,                                //< No window style is applied.                                                      
        TitleBars = WS_CAPTION,                     //< The window has a title bar.
        Border = WS_BORDER,                         //< The window has a thin-line border.
        SysMenu = WS_SYSMENU,                       //< The window has a system menu.
        MinimizeButton = WS_MINIMIZEBOX,            //< The window has a minimize button.
        MaximizeButton = WS_MAXIMIZEBOX,            //< The window has a maximize button.
        ResizeBorder = WS_THICKFRAME,               //< The window has a thick frame that can be resized.
        Visible = WS_VISIBLE,                       //< The window is visible.
        Child = WS_CHILD,                           //< The window is a child window.
        Popup = WS_POPUP,                           // The window is a pop-up window.
        Dialog = WS_DLGFRAME,                       //< The window is a dialog box.
        Overlapped = WS_OVERLAPPED,                 // The window is an overlapped window.
        OverlappedWindow = WS_OVERLAPPEDWINDOW      //< The window is an overlapped window with a title bar, border, and system menu.
    };

    inline WindowStyles operator|(WindowStyles lhs, WindowStyles rhs)
    {
        return static_cast<WindowStyles>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
    }

    /**
     * Converts a WindowStyles enum value to its native window style representation.
     * @param styles The WindowStyles enum value representing the desired window styles.
     * @return The corresponding native window style as a uint32_t.
     */
    inline uint32_t GetNativeWindowStyle(WindowStyles styles)
    {
        return static_cast<uint32_t>(styles);
    }

    enum class WindowExtenedStyle : uint32_t
    {
        None = NULL,
        ToolWindow = WS_EX_TOOLWINDOW,
        AppWindow = WS_EX_APPWINDOW,
        Transparent = WS_EX_TRANSPARENT,
        Topmost = WS_EX_TOPMOST,
    };

    inline WindowExtenedStyle operator|(WindowExtenedStyle lhs, WindowExtenedStyle rhs)
    {
        return static_cast<WindowExtenedStyle>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
    }

    /**
     * Converts a WindowExtenedStyle enum value to its native window extended style representation.
     * @param styles The WindowExtenedStyle enum value representing the desired window styles.
     * @return The corresponding native window extended style as a uint32_t.
     */
    inline uint32_t GetNativeWindowExStyle(WindowExtenedStyle styles)
    {
        return static_cast<uint32_t>(styles);
    }

    struct DefaultSettings
    {
        static constexpr uint32_t UseDefaultPosition = CW_USEDEFAULT;                   //< The default position for a window, typically centered on the screen.
        static constexpr uint32_t UseDefaultSize = CW_USEDEFAULT;                       //< The default size for a window, typically the size of the default window.     
        static constexpr uint32_t UseDefaultStyle = WS_OVERLAPPEDWINDOW;                //< The default window style, which includes a title bar, border, and system menu.
        static constexpr uint32_t UseDefaultExStyle = WS_EX_APPWINDOW;                  //< The default extended window style, which is typically used for application windows.
        static constexpr uint32_t UseDefaultClassStyle = CS_HREDRAW | CS_VREDRAW;       //< The default class style for a window, which redraws the window when it is resized or moved. 
        
        DefaultSettings() = default;
        ~DefaultSettings() = default;

        DefaultSettings(const DefaultSettings&) = delete;
        DefaultSettings& operator=(const DefaultSettings&) = delete;
        DefaultSettings(DefaultSettings&&) = delete;
        DefaultSettings& operator=(DefaultSettings&&) = delete;
    };

    struct SystemCursors
    {
        static constexpr wchar_t* Arrow = IDC_ARROW;                    //< The arrow cursor.                            
        static constexpr wchar_t* IBeam = IDC_IBEAM;                    //< The I-beam cursor for text selection.                
        static constexpr wchar_t* Wait = IDC_WAIT;                      //< The wait cursor, typically shown during processing.                            
        static constexpr wchar_t* Crosshair = IDC_CROSS;                //< The crosshair cursor, often used for precision selection.            
        static constexpr wchar_t* Hand = IDC_HAND;                      //< The hand cursor, typically used for hyperlinks or clickable items.                  
        static constexpr wchar_t* SizeAll = IDC_SIZEALL;                //< The size all cursor, indicating that the object can be moved in any direction.           
        static constexpr wchar_t* No = IDC_NO;                          //< The no cursor, indicating that an action is not allowed.                      
        static constexpr wchar_t* AppStarting = IDC_APPSTARTING;        //< The app starting cursor, indicating that an application is starting.    
        static constexpr wchar_t* Help = IDC_HELP;                      //< The help cursor, typically shown when the user requests help.                  
        static constexpr wchar_t* Size = IDC_SIZE;                      //< The size cursor, indicating that the object can be resized.
        static constexpr wchar_t* SizeNWSE = IDC_SIZENWSE;              //< The size northwest-southeast cursor, indicating that the object can be resized diagonally.
        static constexpr wchar_t* SizeNESW = IDC_SIZENESW;              //< The size northeast-southwest cursor, indicating that the object can be resized diagonally.
        static constexpr wchar_t* SizeWE = IDC_SIZEWE;                  //< The size west-east cursor, indicating that the object can be resized horizontally.
        static constexpr wchar_t* SizeNS = IDC_SIZENS;                  //< The size north-south cursor, indicating that the object can be resized vertically.

        /**
         * Loads a system cursor of the specified type.
         * @param cursorType The type of the cursor to load (e.g. IDC_ARROW, IDC_IBEAM, etc.).
         * @return The handle of the loaded cursor.
         * @throws std::runtime_error If the cursor could not be loaded.
         */
        static CursorHandle LoadSystemCursor(const wchar_t* cursorType)
        {
            CursorHandle cursorHandle = LoadCursor(nullptr, cursorType);
            if (!cursorHandle)
                throw std::runtime_error("Failed to load system cursor.");

            return cursorHandle;
        }

        /**
         * Loads a system cursor from the given instance.
         * @param instance The handle of the module to load the cursor from.
         * @param cursorType The type of the cursor to load (e.g. IDC_ARROW, IDC_IBEAM, etc.).
         * @return The handle of the loaded cursor.
         * @throws std::runtime_error If the cursor could not be loaded.
         */
        static CursorHandle LoadSystemCursor(HandleInstance instance, const wchar_t* cursorType)
        {
            CursorHandle cursorHandle = LoadCursor(instance, cursorType);
            if (!cursorHandle)
                throw std::runtime_error("Failed to load system cursor.");

            return cursorHandle;
        }

        SystemCursors() = default;
        ~SystemCursors() = default;

        SystemCursors(const SystemCursors&) = delete;
        SystemCursors& operator=(const SystemCursors&) = delete;
        SystemCursors(SystemCursors&&) = delete;
        SystemCursors& operator=(SystemCursors&&) = delete;
    };
}