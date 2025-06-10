#pragma once

#include <Windows.h>
#include <string>
#include <stdexcept>

namespace WinCore::Utils
{
    class Convertor
    {
        private:
            Convertor() = default;
            ~Convertor() = default;

            Convertor(const Convertor&) = delete;
            Convertor& operator=(const Convertor&) = delete;
            Convertor(Convertor&&) = delete;
            Convertor& operator=(Convertor&&) = delete;
            
        public:
            /**
             * Converts a wide Unicode string to a UTF-8 encoded string.
             * @param wideString The wide string to be converted.
             * @return A UTF-8 encoded string that represents the input wide string.
             * @throws std::runtime_error If the conversion fails.
             */
            static std::string ToUTF8(const std::wstring& wideString)
            {
                if (wideString.empty())
                    return std::string();

                int size_needed = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), static_cast<int>(wideString.size()), nullptr, 0, nullptr, nullptr);
                if (size_needed <= 0)
                    throw std::runtime_error("Failed to convert wide string to UTF-8.");

                std::string utf8String(size_needed, '\0');
                WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), static_cast<int>(wideString.size()), &utf8String[0], size_needed, nullptr, nullptr);
                return utf8String;
            }

            /**
             * Converts a UTF-8 encoded string to a wide Unicode string.
             * @param utf8String The UTF-8 encoded string to be converted.
             * @return A wide Unicode string that represents the input UTF-8 encoded string.
             * @throws std::runtime_error If the conversion fails.
             */
            static std::wstring ToWString(const std::string& utf8String)
            {
                if (utf8String.empty())
                    return std::wstring();

                int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), static_cast<int>(utf8String.size()), nullptr, 0);
                if (size_needed <= 0)
                    throw std::runtime_error("Failed to convert UTF-8 string to wide string.");

                std::wstring wideString(size_needed, L'\0');
                MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), static_cast<int>(utf8String.size()), &wideString[0], size_needed);
                return wideString;
            }
    };
} 