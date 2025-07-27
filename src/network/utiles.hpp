#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <algorithm>
inline std::array<std::byte, 2> uint16_to_be_bytes(uint16_t value)
{
    std::array<std::byte, 2> bytes{};

    // 转换为大端序
    bytes[0] = static_cast<std::byte>((value >> 8) & 0xFF); // 高字节
    bytes[1] = static_cast<std::byte>(value & 0xFF);        // 低字节

    return bytes;
}

inline std::array<std::byte, 8> uint64_to_be_bytes(uint64_t value)
{
    std::array<std::byte, 8> bytes{};

    // 转换为大端序（高字节在前，低字节在后）
    bytes[0] = static_cast<std::byte>((value >> 56) & 0xFF); // 字节 0 (最高字节)
    bytes[1] = static_cast<std::byte>((value >> 48) & 0xFF); // 字节 1
    bytes[2] = static_cast<std::byte>((value >> 40) & 0xFF); // 字节 2
    bytes[3] = static_cast<std::byte>((value >> 32) & 0xFF); // 字节 3
    bytes[4] = static_cast<std::byte>((value >> 24) & 0xFF); // 字节 4
    bytes[5] = static_cast<std::byte>((value >> 16) & 0xFF); // 字节 5
    bytes[6] = static_cast<std::byte>((value >> 8) & 0xFF);  // 字节 6
    bytes[7] = static_cast<std::byte>(value & 0xFF);         // 字节 7 (最低字节)

    return bytes;
}
inline uint16_t be_bytes_to_uint16(const std::array<std::byte, 2> &bytes)
{
    // 将大端序字节转换为uint16_t
    uint16_t value = (static_cast<uint16_t>(bytes[0]) << 8) |
                     static_cast<uint16_t>(bytes[1]);
    return value;
}

inline uint64_t be_bytes_to_uint64(const std::array<std::byte, 8> &bytes)
{
    // 将大端序字节转换为uint64_t
    uint64_t value = (static_cast<uint64_t>(bytes[0]) << 56) |
                     (static_cast<uint64_t>(bytes[1]) << 48) |
                     (static_cast<uint64_t>(bytes[2]) << 40) |
                     (static_cast<uint64_t>(bytes[3]) << 32) |
                     (static_cast<uint64_t>(bytes[4]) << 24) |
                     (static_cast<uint64_t>(bytes[5]) << 16) |
                     (static_cast<uint64_t>(bytes[6]) << 8) |
                     static_cast<uint64_t>(bytes[7]);
    return value;
}
template<std::size_t L>
inline std::array<std::byte, L> vectorToArray(typename std::vector<std::byte>::iterator begin) {
    if (std::distance(begin, begin + L) < static_cast<typename std::iterator_traits<decltype(begin)>::difference_type>(L)) {
        throw std::out_of_range("Not enough elements in vector");
    }
    
    std::array<std::byte, L> result;
    std::copy_n(begin, L, result.begin());
    return result;
}