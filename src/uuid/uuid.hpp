#pragma once
#include <array>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>
class UUID {
public:
    // 默认构造函数生成随机UUID
    UUID() {
        generateRandom();
    }

    // 从16字节数据构造UUID
    explicit UUID(const std::array<unsigned char, 16>& data) : data_(data) {}

    // 生成随机UUID（版本4）
    void generateRandom();

    // 转换为标准UUID字符串格式（8-4-4-4-12）
    std::string toString();

    // 转换为标准UUID字符串格式（没有连字符）
    std::string toString2();

    // 获取原始数据
    const std::array<unsigned char, 16>& getData() const { return data_; }

private:
    std::array<unsigned char, 16> data_{};
};