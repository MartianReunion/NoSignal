#include <catch2/catch_test_macros.hpp>
#include "network/message.hpp"
using namespace Network;
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
}