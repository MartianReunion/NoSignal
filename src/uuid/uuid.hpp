// uuid.hpp
#pragma once
#include <array>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstddef>  // for std::byte

class UUID {
public:
    // Default constructor generates random UUID
    UUID() {
        generateRandom();
    }

    // Construct UUID from 16 bytes of data
    explicit UUID(const std::array<std::byte, 16>& data) : data_(data) {}

    // Generate nil UUID (all zeros)
    static UUID nil() {
        return UUID(std::array<std::byte, 16>{});
    }

    // Generate random UUID (version 4)
    void generateRandom();

    // Convert to standard UUID string format (8-4-4-4-12)
    std::string toString() const;

    // Convert to UUID string format without hyphens
    std::string toString2() const;

    // Get raw data
    const std::array<std::byte, 16>& getData() const { return data_; }

    // Equality comparison
    bool operator==(const UUID& other) const {
        return data_ == other.data_;
    }

    // Inequality comparison
    bool operator!=(const UUID& other) const {
        return !(*this == other);
    }

    // Check if this is the nil UUID
    bool isNil() const {
        return *this == nil();
    }

private:
    std::array<std::byte, 16> data_{};
};