#include <catch2/catch_test_macros.hpp>
#include "network/message.hpp"
#include <vector>
#include <cstddef>
#include "network/utiles.hpp"

TEST_CASE("Message construction and type checking", "[message]") {
    Network::Message::Ping ping;
    Network::Message::Pong pong;
    Network::Message::Broken broken;
    Network::Message::Unknown unknown;
    
    UUID testUuid;
    
    SECTION("Construct with Ping") {
        Network::Message msg(ping, testUuid);
        REQUIRE(msg.is<Network::Message::Ping>());
        REQUIRE_FALSE(msg.is<Network::Message::Pong>());
        REQUIRE(msg.getIf<Network::Message::Ping>() != nullptr);
        REQUIRE(msg.getIf<Network::Message::Pong>() == nullptr);
        REQUIRE(msg.getRemote() == testUuid);
    }
    
    SECTION("Construct with Pong") {
        Network::Message msg(pong, testUuid);
        REQUIRE(msg.is<Network::Message::Pong>());
        REQUIRE_FALSE(msg.is<Network::Message::Ping>());
        REQUIRE(msg.getIf<Network::Message::Pong>() != nullptr);
        REQUIRE(msg.getIf<Network::Message::Ping>() == nullptr);
        REQUIRE(msg.getRemote() == testUuid);
    }
    
    SECTION("Construct with Broken") {
        broken.data = {std::byte{0x01}, std::byte{0x02}};
        Network::Message msg(broken, testUuid);
        REQUIRE(msg.is<Network::Message::Broken>());
        REQUIRE_FALSE(msg.is<Network::Message::Ping>());
        REQUIRE(msg.getIf<Network::Message::Broken>() != nullptr);
        REQUIRE(msg.getIf<Network::Message::Ping>() == nullptr);
        REQUIRE(msg.getRemote() == testUuid);
        REQUIRE(msg.getIf<Network::Message::Broken>()->data.size() == 2);
    }
    
    SECTION("Construct with Unknown") {
        unknown.data = {std::byte{0x01}, std::byte{0x02}};
        Network::Message msg(unknown, testUuid);
        REQUIRE(msg.is<Network::Message::Unknown>());
        REQUIRE_FALSE(msg.is<Network::Message::Ping>());
        REQUIRE(msg.getIf<Network::Message::Unknown>() != nullptr);
        REQUIRE(msg.getIf<Network::Message::Ping>() == nullptr);
        REQUIRE(msg.getRemote() == testUuid);
        REQUIRE(msg.getIf<Network::Message::Unknown>()->data.size() == 2);
    }
}

TEST_CASE("Message serialization and deserialization", "[message]") {
    UUID sender;
    UUID receiver;
    
    SECTION("Ping roundtrip") {
        Network::Message original(Network::Message::Ping{}, sender);
        auto serialized = original.serialize(receiver);
        auto deserialized = Network::makeMessage(serialized);
        
        REQUIRE(deserialized.is<Network::Message::Ping>());
        REQUIRE(deserialized.getRemote() == receiver);
    }
    
    SECTION("Pong roundtrip") {
        Network::Message original(Network::Message::Pong{}, sender);
        auto serialized = original.serialize(receiver);
        auto deserialized = Network::makeMessage(serialized);
        
        REQUIRE(deserialized.is<Network::Message::Pong>());
        REQUIRE(deserialized.getRemote() == receiver);
    }
    
    SECTION("Broken roundtrip") {
        Network::Message::Broken broken;
        broken.data = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}};
        Network::Message original(broken, sender);
        auto serialized = original.serialize(receiver);
        auto deserialized = Network::makeMessage(serialized);
        
        REQUIRE(deserialized.is<Network::Message::Broken>());
        REQUIRE(deserialized.getRemote() == receiver);
        REQUIRE(deserialized.getIf<Network::Message::Broken>()->data.size() == 3);
    }
    
    SECTION("Unknown roundtrip") {
        Network::Message::Unknown unknown;
        unknown.data = {std::byte{0x01}, std::byte{0x02}, std::byte{0x03}};
        Network::Message original(unknown, sender);
        auto serialized = original.serialize(receiver);
        auto deserialized = Network::makeMessage(serialized);
        
        REQUIRE(deserialized.is<Network::Message::Unknown>());
        REQUIRE(deserialized.getRemote() == receiver);
        REQUIRE(deserialized.getIf<Network::Message::Unknown>()->data.size() == 3);
    }
    
    SECTION("Invalid message handling") {
        // Too small message
        std::vector<std::byte> smallMessage = {std::byte{0x00}, std::byte{0x00}};
        auto deserialized = Network::makeMessage(smallMessage);
        REQUIRE(deserialized.is<Network::Message::Broken>());
        REQUIRE(deserialized.getRemote().isNil());
        
        // Invalid magic number
        std::vector<std::byte> invalidMagic(Network::METADATA_SIZE, std::byte{0x00});
        deserialized = Network::makeMessage(invalidMagic);
        REQUIRE(deserialized.is<Network::Message::Broken>());
        REQUIRE(deserialized.getRemote().isNil());
        
        // Size mismatch
        std::vector<std::byte> sizeMismatch(Network::METADATA_SIZE + 10, std::byte{0x00});
        // Set magic number
        auto magic = uint16_to_be_bytes(Network::MAGIC_NUMBER);
        std::copy(magic.begin(), magic.end(), sizeMismatch.begin());
        // Set size to 5 (but actual payload is 10)
        auto wrongSize = uint64_to_be_bytes(5);
        std::copy(wrongSize.begin(), wrongSize.end(), 
                 sizeMismatch.begin() + Network::MAGIC_NUMBER_SIZE + Network::REMOTE_UUID_SIZE + Network::MESSAGE_ID_SIZE);
        
        deserialized = Network::makeMessage(sizeMismatch);
        REQUIRE(deserialized.is<Network::Message::Broken>());
        REQUIRE_FALSE(deserialized.getRemote().isNil()); // Should have UUID from message
    }
}

TEST_CASE("Message edge cases", "[message]") {
    SECTION("Empty Broken message") {
        Network::Message::Broken broken;
        Network::Message msg(broken, UUID::nil());
        REQUIRE(msg.is<Network::Message::Broken>());
        REQUIRE(msg.getIf<Network::Message::Broken>()->data.empty());
    }
    
    SECTION("Empty Unknown message") {
        Network::Message::Unknown unknown;
        Network::Message msg(unknown, UUID::nil());
        REQUIRE(msg.is<Network::Message::Unknown>());
        REQUIRE(msg.getIf<Network::Message::Unknown>()->data.empty());
    }
    
    SECTION("Large Broken message") {
        Network::Message::Broken broken;
        broken.data.resize(1024, std::byte{0xAA});
        Network::Message msg(broken, UUID::nil());
        REQUIRE(msg.is<Network::Message::Broken>());
        REQUIRE(msg.getIf<Network::Message::Broken>()->data.size() == 1024);
    }
}