// uuid.cpp
#include "uuid/uuid.hpp"
#include <algorithm>

// Generate random UUID (version 4)
void UUID::generateRandom()
{
    // Use random device for seeding
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned> dis(0, 255);
    
    // Generate 16 random bytes
    for (int i = 0; i < 16; ++i) 
    {
        data_[i] = static_cast<std::byte>(dis(gen));
    }
    
    // Set version (bits 4-7 of byte 6 to 0100)
    data_[6] = (data_[6] & static_cast<std::byte>(0x0F)) | static_cast<std::byte>(0x40);
    
    // Set variant (bits 6-7 of byte 8 to 10)
    data_[8] = (data_[8] & static_cast<std::byte>(0x3F)) | static_cast<std::byte>(0x80);
}

// Convert to standard UUID string format (8-4-4-4-12)
std::string UUID::toString() const
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    
    for (int i = 0; i < 16; ++i) {
        // Convert std::byte to unsigned for output
        oss << std::setw(2) << static_cast<unsigned>(data_[i]);
        
        // Add hyphens at the correct positions
        if (i == 3 || i == 5 || i == 7 || i == 9) {
            oss << '-';
        }
    }
    return oss.str();
}

std::string UUID::toString2() const
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    
    for (int i = 0; i < 16; ++i) {
        oss << std::setw(2) << static_cast<unsigned>(data_[i]);
    }
    return oss.str();
}