#include <catch2/catch_test_macros.hpp>
#include "network/message.hpp"
#include "network/utiles.hpp"
#include <vector>
#include <cstddef>
#include <algorithm>
using namespace Network;
TEST_CASE("int <==> bytes helper", "[network]")
{
    // 16-bit
    uint16_t value = 0x0102;
    std::array<std::byte, 2> bytes = uint16_to_be_bytes(value);
    uint8_t raw_data1[] = {0x01, 0x02};
    std::array<std::byte, sizeof(raw_data1)> byte_array;

    std::transform(std::begin(raw_data1), std::end(raw_data1),
                   byte_array.begin(),
                   [](uint8_t val)
                   { return static_cast<std::byte>(val); });
    REQUIRE(bytes == byte_array);
    REQUIRE(be_bytes_to_uint16(bytes) == value);

    // 64-bit
    uint64_t value2 = 0x0102030405060708;
    std::array<std::byte, 8> bytes64 = uint64_to_be_bytes(value2);
    uint8_t raw_data64[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::array<std::byte, sizeof(raw_data64)> byte_array64;
    std::transform(std::begin(raw_data64), std::end(raw_data64),
                   byte_array64.begin(),
                   [](uint8_t val)
                   { return static_cast<std::byte>(val); });
    REQUIRE(bytes64 == byte_array64);
    REQUIRE(be_bytes_to_uint64(bytes64) == value2);
}
TEST_CASE("Message Test", "[network]")
{
    SECTION("Type Safety")
    {
        Message::Ping ping;
        Message message(ping);
        REQUIRE(message.is<Message::Ping>());
        const Message::Ping *pingPtr = message.getIf<Message::Ping>();
        REQUIRE(pingPtr != nullptr);
        REQUIRE_FALSE(message.is<Message::Unknown>());
        const Message::Unknown *unknownPtr = message.getIf<Message::Unknown>();
        REQUIRE(unknownPtr == nullptr);
    }
    SECTION("Unknown")
    {
        std::vector<std::byte> data = {std::byte(0x01), std::byte(0x02), std::byte(0x03)};
        Message::Unknown unknownMessage{data};
        Message message(unknownMessage);
        auto serializedData = message.serialize();
        REQUIRE(serializedData.size() == sizeof(uint16_t) + sizeof(uint64_t) + data.size());
        auto message2 = makeMessage(serializedData);
        REQUIRE(message2.is<Message::Unknown>());
        const Message::Unknown *_unknownMessage = message2.getIf<Message::Unknown>();
        REQUIRE(_unknownMessage != nullptr);
        REQUIRE(_unknownMessage->data == data);
    }
    SECTION("Ping")
    {
        Message::Ping pingMessage;
        Message message(pingMessage);
        auto serializedData = message.serialize();
        REQUIRE(serializedData.size() == sizeof(uint16_t) + sizeof(uint64_t));
        auto message2 = makeMessage(serializedData);
        REQUIRE(message2.is<Message::Ping>());
        const Message::Ping *_pingMessage = message2.getIf<Message::Ping>();
        REQUIRE(_pingMessage != nullptr);
    }
    SECTION("Pong")
    {
        Message::Pong pongMessage;
        Message message(pongMessage);
        auto serializedData = message.serialize();
        REQUIRE(serializedData.size() == sizeof(uint16_t) + sizeof(uint64_t));
        auto message2 = makeMessage(serializedData);
        REQUIRE(message2.is<Message::Pong>());
        const Message::Pong *_pongMessage = message2.getIf<Message::Pong>();
        REQUIRE(_pongMessage != nullptr);
    }
    SECTION("Broken")
    {
        Message::Broken brokenMessage;
        Message message(brokenMessage);
        auto serializedData = message.serialize();
        REQUIRE(serializedData.size() == sizeof(uint16_t) + sizeof(uint64_t));
        auto message2 = makeMessage(serializedData);
        REQUIRE(message2.is<Message::Broken>());
        const Message::Broken *_brokenMessage = message2.getIf<Message::Broken>();
        REQUIRE(_brokenMessage != nullptr);
    }

    SECTION("invaid message test")
    {
        std::vector<std::byte> data = {std::byte(0x01), std::byte(0x02)};
        auto message = makeMessage(data);
        REQUIRE(message.is<Message::Broken>());
        const Message::Broken *brokenPtr = message.getIf<Message::Broken>();
        REQUIRE(brokenPtr != nullptr);

        Message::Ping pingMessage;
        Message message2(pingMessage);
        auto serializedData = message2.serialize();
        serializedData[0] = std::byte(0xFF); // Corrupt the message type
        serializedData[1] = std::byte(0xFF); // Corrupt the message type
        auto message3 = makeMessage(serializedData);
        REQUIRE(message3.is<Message::Unknown>());
    }
}