#include <ShellScalingApi.h>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Kernel32.lib")

#include "Platform.hpp"

namespace WinCore::Core
{

    MessageBoxResult MessageBox::Show(const wchar_t * text, const wchar_t * title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return static_cast<MessageBoxResult>(MessageBoxW(nullptr, text, title, icon | buttons));
    }

    MessageBoxResult MessageBox::Show(const char * text, const char * title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return static_cast<MessageBoxResult>(MessageBoxA(nullptr, text, title, icon | buttons));
    }

    MessageBoxResult MessageBox::Show(const std::wstring & text, const std::wstring & title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return Show(text.c_str(), title.c_str(), icon, buttons);
    }

    MessageBoxResult MessageBox::Show(const std::string & text, const std::string & title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return Show(text.c_str(), title.c_str(), icon, buttons);
    }

    MessageBoxResult MessageBox::Show(WindowHandle windowHandle, const wchar_t * text, const wchar_t * title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return static_cast<MessageBoxResult>(MessageBoxW(windowHandle, text, title, icon | buttons));
    }

    MessageBoxResult MessageBox::Show(WindowHandle windowHandle, const char * text, const char * title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return static_cast<MessageBoxResult>(MessageBoxA(windowHandle, text, title, icon | buttons));
    }

    MessageBoxResult MessageBox::Show(WindowHandle windowHandle, const std::wstring & text, const std::wstring & title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return Show(windowHandle, text.c_str(), title.c_str(), icon, buttons);
    }

    MessageBoxResult MessageBox::Show(WindowHandle windowHandle, const std::string & text, const std::string & title, MessageBoxIcon icon, MessageBoxButton buttons)
    {
        return Show(windowHandle, text.c_str(), title.c_str(), icon, buttons);
    }



    void Monitor::SetProcessDPIAwareness(DPIAwareness awareness)
    {
        SetProcessDpiAwareness(static_cast<PROCESS_DPI_AWARENESS>(awareness));
    }

    Monitor::DPIAwareness Monitor::GetProcessDPIAwareness()
    {
        PROCESS_DPI_AWARENESS awareness{PROCESS_DPI_UNAWARE};
        if (FAILED(GetProcessDpiAwareness(nullptr, &awareness)))
            return Monitor::DPIAwareness::Unaware;

        return static_cast<Monitor::DPIAwareness>(awareness);
    }

    Monitor::DPIAwareness Monitor::GetSystemDPIAwareness()
    {
        HDC screen = GetDC(nullptr);
        uint32_t dpi = GetDeviceCaps(screen, LOGPIXELSX);
        ReleaseDC(nullptr, screen);

        if (dpi <= 96)
            return Monitor::DPIAwareness::Unaware;
        else if (dpi <= 120)
            return Monitor::DPIAwareness::SystemAware;
        else if (dpi <= 144)
            return Monitor::DPIAwareness::PerMonitorAwareV2;
        else
            return Monitor::DPIAwareness::PerMonitorAware;
    }

    std::shared_ptr<Monitor::MonitorInfo> Monitor::GetPrimaryMonitor()
    {
        static std::shared_ptr<Monitor::MonitorInfo> primaryMonitor{nullptr};
        if(!primaryMonitor)
        {
            primaryMonitor = std::make_shared<Monitor::MonitorInfo>();
            HMONITOR hMonitor = MonitorFromWindow(nullptr, MONITOR_DEFAULTTOPRIMARY);
            if (hMonitor)
            {
                MONITORINFOEXW monitorInfo{};
                monitorInfo.cbSize = sizeof(MONITORINFOEXW);
                if (GetMonitorInfoW(hMonitor, &monitorInfo))
                {
                    primaryMonitor->MonitorName = monitorInfo.szDevice;
                    primaryMonitor->WorkArea.Top = monitorInfo.rcWork.top;
                    primaryMonitor->WorkArea.Left = monitorInfo.rcWork.left;
                    primaryMonitor->WorkArea.Right = monitorInfo.rcWork.right;
                    primaryMonitor->WorkArea.Bottom = monitorInfo.rcWork.bottom;

                    primaryMonitor->Area.Top = monitorInfo.rcMonitor.top;
                    primaryMonitor->Area.Left = monitorInfo.rcMonitor.left;
                    primaryMonitor->Area.Right = monitorInfo.rcMonitor.right;
                    primaryMonitor->Area.Bottom = monitorInfo.rcMonitor.bottom;

                    primaryMonitor->Width = static_cast<uint32_t>(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);
                    primaryMonitor->Height = static_cast<uint32_t>(monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
                    primaryMonitor->IsPrimary = true;

                    UINT dpiX, dpiY;
                    GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
                    primaryMonitor->DPIScaling.X = dpiX;
                    primaryMonitor->DPIScaling.Y = dpiY;

                    DEVMODEW devMode = {};
                    devMode.dmSize = sizeof(devMode);
                    if (EnumDisplaySettingsW(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &devMode))
                    {
                        primaryMonitor->BitsPerPixel = devMode.dmBitsPerPel;
                        primaryMonitor->IsSupportHightDPI = (devMode.dmDisplayFlags & DM_INTERLACED) == 0;
                        primaryMonitor->RefreshRate = devMode.dmDisplayFrequency;
                        primaryMonitor->Awareness = static_cast<Monitor::DPIAwareness>(devMode.dmDisplayFlags & DM_PELSWIDTH ? Monitor::DPIAwareness::PerMonitorAware : Monitor::DPIAwareness::Unaware);
                    }
                }
            }
        }

        return primaryMonitor;
    }

}