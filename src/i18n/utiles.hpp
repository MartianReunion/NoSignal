// #include <codecvt>
// #include <locale>
// #include <string>

// // Not Useful AT ALL! (a stupid AI gives me this)
// std::string gbktoutf8(const std::string& gbkStr) 
// {
//     // Step 1: GBK to Unicode
//     std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> conv(
//     new std::codecvt_byname<wchar_t, char, std::mbstate_t>("zh_CN.GBK"));
//     std::wstring unicodeStr = conv.from_bytes(gbkStr);

//     // Step 2: Unicode to UTF-8
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8Conv;
//     return utf8Conv.to_bytes(unicodeStr);
// }

// std::string Wstring2String(const std::wstring& wstr)
// {
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//     return converter.to_bytes(wstr);
// }

// std::wstring String2Wstring(const std::string& str)
// {
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//     return converter.from_bytes(str);
// }