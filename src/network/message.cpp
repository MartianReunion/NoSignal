#include "network/message.hpp"
#include "network/utiles.hpp"
#include "log/logger.hpp"
using namespace Network;
const auto metadataSize = sizeof(uint16_t) + sizeof(uint64_t);

Log::Logger logger("NetworkMessage");

std::vector<std::byte> Network::serialize(const Message::Unknown &msg)
{
    std::vector<std::byte> buffer(msg.data.size() + metadataSize);
    auto id = uint16_to_be_bytes(MessageTypeId<Message::Unknown>::value);
    std::copy(id.begin(), id.end(), buffer.begin());
    auto size = uint64_to_be_bytes(msg.data.size());
    std::copy(size.begin(), size.end(), buffer.begin() + sizeof(uint16_t));
    std::copy(msg.data.begin(), msg.data.end(), buffer.begin() + sizeof(uint16_t) + sizeof(uint64_t));
    return std::move(buffer);
}
std::vector<std::byte> Network::serialize(const Message::Ping &)
{
    std::vector<std::byte> buffer(0 + metadataSize);
    auto id = uint16_to_be_bytes(MessageTypeId<Message::Ping>::value);
    std::copy(id.begin(), id.end(), buffer.begin());
    auto size = uint64_to_be_bytes(0);
    std::copy(size.begin(), size.end(), buffer.begin() + sizeof(uint16_t));
    return std::move(buffer);
}
std::vector<std::byte> Network::serialize(const Message::Pong &)
{
    std::vector<std::byte> buffer(0 + metadataSize);
    auto id = uint16_to_be_bytes(MessageTypeId<Message::Pong>::value);
    std::copy(id.begin(), id.end(), buffer.begin());
    auto size = uint64_to_be_bytes(0);
    std::copy(size.begin(), size.end(), buffer.begin() + sizeof(uint16_t));
    return std::move(buffer);
}
std::vector<std::byte> Network::serialize(const Message::Broken &)
{
    logger.warning("Serializing Broken type message.");
    std::vector<std::byte> buffer(0 + metadataSize);
    auto id = uint16_to_be_bytes(MessageTypeId<Message::Broken>::value);
    std::copy(id.begin(), id.end(), buffer.begin());
    auto size = uint64_to_be_bytes(0);
    std::copy(size.begin(), size.end(), buffer.begin() + sizeof(uint16_t));
    return std::move(buffer);
}

Message Network::makeMessage(const std::vector<std::byte> &data)
{
    if (data.size() < metadataSize)
    {
        logger.error("Data size is less than the metadata size, returning broken message");
        Message::Broken brokenMessage;
        return Message(brokenMessage);
    }
    std::array<std::byte, 2> idBytes;
    std::copy(data.begin(), data.begin() + sizeof(uint16_t), idBytes.begin());

    std::array<std::byte, 8> sizeBytes;
    std::copy(data.begin() + sizeof(uint16_t), data.begin() + metadataSize, sizeBytes.begin());

    uint16_t id = be_bytes_to_uint16(idBytes);
    uint64_t size = be_bytes_to_uint64(sizeBytes);

    if (data.size() != metadataSize + size)
    {
        logger.error("Message size mismatch, returning broken message");
        Message::Broken brokenMessage;
        return Message(brokenMessage);
    }

    switch (id)
    {
    case MessageTypeId<Message::Unknown>::value:
        logger.warning("Unknown message type received, returning as Unknown.");
        return Message(Message::Unknown{std::vector<std::byte>(data.begin() + metadataSize, data.end())});
    case MessageTypeId<Message::Ping>::value:
        return Message(Message::Ping{});
    case MessageTypeId<Message::Pong>::value:
        return Message(Message::Pong{});
    case MessageTypeId<Message::Broken>::value:
        logger.error("Broken message received, returning as Broken.");
        return Message(Message::Broken());
    default:
        logger.error("Unknown message type ID: " + std::to_string(id));
        return Message(Message::Unknown{std::vector<std::byte>(data.begin() + metadataSize, data.end())});
    }
}