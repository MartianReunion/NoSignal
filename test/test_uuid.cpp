// uuid_test.cpp
#include "uuid/uuid.hpp"
#include <catch2/catch_test_macros.hpp>
#include <regex>

TEST_CASE("UUID functionality tests", "[uuid]") {
    SECTION("Default constructor generates valid version 4 UUID") {
        UUID uuid;
        
        // Verify version bits (4-7 of byte 6 should be 0100)
        auto data = uuid.getData();
        auto version_byte = static_cast<uint8_t>(data[6]) >> 4;
        REQUIRE(version_byte == 0x4);
        
        // Verify variant bits (6-7 of byte 8 should be 10)
        auto variant_byte = static_cast<uint8_t>(data[8]) >> 6;
        REQUIRE(variant_byte == 0x2);
    }

    SECTION("Nil UUID is all zeros") {
        auto nil_uuid = UUID::nil();
        auto data = nil_uuid.getData();
        
        REQUIRE(std::all_of(data.begin(), data.end(), [](std::byte b) {
            return b == std::byte{0};
        }));
        
        REQUIRE(nil_uuid.isNil());
    }

    SECTION("String conversion") {
        UUID uuid;
        
        // Test toString() format (8-4-4-4-12 with hyphens)
        std::string str = uuid.toString();
        std::regex uuid_pattern("^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");
        REQUIRE(std::regex_match(str, uuid_pattern));
        
        // Test toString2() format (32 hex digits, no hyphens)
        std::string str2 = uuid.toString2();
        REQUIRE(str2.size() == 32);
        REQUIRE(std::all_of(str2.begin(), str2.end(), [](char c) {
            return std::isxdigit(c);
        }));
    }

    SECTION("Equality comparison") {
        UUID uuid1;
        UUID uuid2;
        
        // Two random UUIDs should almost certainly not be equal
        REQUIRE(uuid1 != uuid2);
        
        // A UUID should equal itself
        REQUIRE(uuid1 == uuid1);
        
        // Constructed UUIDs with same data should be equal
        auto data = uuid1.getData();
        UUID uuid3(data);
        REQUIRE(uuid1 == uuid3);
    }

    SECTION("Nil UUID comparison") {
        auto nil1 = UUID::nil();
        auto nil2 = UUID::nil();
        
        REQUIRE(nil1 == nil2);
        REQUIRE(nil1.isNil());
        
        UUID random_uuid;
        REQUIRE(random_uuid != nil1);
    }
}