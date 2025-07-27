#include <codecvt>
#include <locale>
#include <string>

std::string gbktoutf8(const std::string& gbkStr) 
{
    // Step 1: GBK to Unicode
    std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> conv(
    new std::codecvt_byname<wchar_t, char, std::mbstate_t>("zh_CN.GBK"));
    std::wstring unicodeStr = conv.from_bytes(gbkStr);

    // Step 2: Unicode to UTF-8
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8Conv;
    return utf8Conv.to_bytes(unicodeStr);
}