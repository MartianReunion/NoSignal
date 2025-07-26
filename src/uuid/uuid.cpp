#include "uuid/uuid.hpp"

// 生成随机UUID（版本4）
void UUID::generateRandom()
{
    // 使用随机设备生成种子
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned> dis(0, 255);
    // 生成16个随机字节
    for (int i = 0; i < 16; ++i) 
    {
        data_[i] = static_cast<unsigned char>(dis(gen));
    }
    // 设置版本号（第6字节高4位为0100）
    data_[6] = (data_[6] & 0x0F) | 0x40;  // 版本4
    // 设置变体（第8字节高2位为10）
    data_[7] = (data_[7] & 0x3F) | 0x80;  // RFC 4122变体
}

// 转换为标准UUID字符串格式（8-4-4-4-12）
std::string UUID::toString()
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    // 按分组输出十六进制值
    for (int i = 0; i < 16; ++i) {
        oss << std::setw(2) << static_cast<unsigned>(data_[i]);
        // 在指定位置添加连字符
        if (i == 3 || i == 5 || i == 7 || i == 9) {
            oss << '-';
        }
    }
    return oss.str();
}

std::string UUID::toString2()
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    // 按分组输出十六进制值
    for (int i = 0; i < 16; ++i) {
        oss << std::setw(2) << static_cast<unsigned>(data_[i]);
    }
    return oss.str();
}