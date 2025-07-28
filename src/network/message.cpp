#include "network/message.hpp"
#include "network/utiles.hpp"
#include "log/logger.hpp"
using namespace Network;

Log::Logger logger("NetworkMessage");

// Serializes
uint64_t Network::serialize(const Message::Broken &msg, std::vector<std::byte>::iterator &out)
{
    logger.debug("Serializing Broken message");
    auto size = msg.data.size();
    out = std::copy(msg.data.begin(), msg.data.end(), out);
    return size;
}
uint64_t Network::serialize(const Message::Ping &msg, std::vector<std::byte>::iterator &out)
{
    logger.debug("Serializing Ping message");
    return 0; // Ping has no data
}
uint64_t Network::serialize(const Message::Pong &msg, std::vector<std::byte>::iterator &out)
{
    logger.debug("Serializing Pong message");
    return 0; // Pong has no data
}
uint64_t Network::serialize(const Message::Unknown &msg, std::vector<std::byte>::iterator &out)
{
    logger.debug("Serializing Unknown message");
    auto size = msg.data.size();
    out = std::copy(msg.data.begin(), msg.data.end(), out);
    return size;
}

// Deserializes
Message::Broken Network::deserializeBroken(const std::vector<std::byte> &data)
{
    logger.debug("Deserializing Broken message");
    Message::Broken brokenMessage;
    brokenMessage.data = data;
    return brokenMessage;
}
Message::Ping Network::deserializePing(const std::vector<std::byte> &data)
{
    logger.debug("Deserializing Ping message");
    if (!data.empty())
    {
        logger.warning("Ping message should not contain data, ignoring it");
    }
    return Message::Ping();
}
Message::Pong Network::deserializePong(const std::vector<std::byte> &data)
{
    logger.debug("Deserializing Pong message");
    if (!data.empty())
    {
        logger.warning("Pong message should not contain data, ignoring it");
    }
    return Message::Pong();
}
Message::Unknown Network::deserializeUnknown(const std::vector<std::byte> &data)
{
    logger.debug("Deserializing Unknown message");
    Message::Unknown unknownMessage;
    unknownMessage.data = data;
    return unknownMessage;
}

//
std::vector<std::byte> Message::serialize(UUID &remote) const
{
    return std::visit([&](const auto &msg)
                      {
            std::vector<std::byte> packet(METADATA_SIZE+INITIAL_BUFFER_SIZE);
            auto magic = uint16_to_be_bytes(MAGIC_NUMBER);
            auto messageId = uint16_to_be_bytes(MessageType<std::decay_t<decltype(msg)>>::id);
            auto remoteUuid = remote.getData();
            auto i = packet.begin();
            i+=METADATA_SIZE;
            auto payloadSize = ::Network::serialize(msg,i);
            auto payloadSize_b = uint64_to_be_bytes(::Network::serialize(msg,i));
            i = packet.begin();
            std::copy(magic.begin(), magic.end(), i);
            i += MAGIC_NUMBER_SIZE;
            std::copy(remoteUuid.begin(), remoteUuid.end(), i);
            i += REMOTE_UUID_SIZE;
            std::copy(messageId.begin(), messageId.end(), i);
            i += MESSAGE_ID_SIZE;
            std::copy(payloadSize_b.begin(), payloadSize_b.end(), i);
            i += MESSAGE_SIZE_SIZE;
            return std::vector<std::byte>(packet.begin(), packet.begin()+METADATA_SIZE+payloadSize); },
                      m_data);
}
//
Message Network::makeMessage(const std::vector<std::byte> &data)
{
    if (data.size() < METADATA_SIZE)
    {
        logger.error("Message is too small");
        Message::Broken brokenMessage;
        brokenMessage.data = std::vector<std::byte>(data.begin(), data.end());
        return Message(brokenMessage, UUID::nil());
    }
    std::vector<std::byte> metadata(data.begin(), data.begin() + METADATA_SIZE);
    std::vector<std::byte> messageData(data.begin() + METADATA_SIZE, data.end());
    std::array<std::byte, MAGIC_NUMBER_SIZE> magic = vectorToArray<MAGIC_NUMBER_SIZE>(metadata.begin());
    if (be_bytes_to_uint16(magic) != MAGIC_NUMBER)
    {
        logger.error("Invalid magic number in message");
        Message::Broken brokenMessage;
        brokenMessage.data = std::vector<std::byte>(data.begin(), data.end());
        return Message(brokenMessage, UUID::nil());
    }
    std::array<std::byte, REMOTE_UUID_SIZE> remoteuuid = vectorToArray<REMOTE_UUID_SIZE>(metadata.begin() + MAGIC_NUMBER_SIZE);
    UUID remote(remoteuuid);
    if (remote.isNil())
    {
        logger.error("Invalid UUID in message");
        Message::Broken brokenMessage;
        brokenMessage.data = std::vector<std::byte>(data.begin(), data.end());
        return Message(brokenMessage, UUID::nil());
    }
    std::array<std::byte, MESSAGE_ID_SIZE> messageIdBytes = vectorToArray<MESSAGE_ID_SIZE>(metadata.begin() + MAGIC_NUMBER_SIZE + REMOTE_UUID_SIZE);
    uint16_t messageId = be_bytes_to_uint16(messageIdBytes);
    std::array<std::byte, MESSAGE_SIZE_SIZE> messageSizeBytes = vectorToArray<MESSAGE_SIZE_SIZE>(metadata.begin() + MAGIC_NUMBER_SIZE + REMOTE_UUID_SIZE + MESSAGE_ID_SIZE);
    uint64_t messageSize = be_bytes_to_uint64(messageSizeBytes);
    if (messageSize != messageData.size())
    {
        logger.error("Message size mismatch: expected " + std::to_string(messageSize) + ", got " + std::to_string(messageData.size()));
        Message::Broken brokenMessage;
        brokenMessage.data = std::vector<std::byte>(data.begin(), data.end());
        return Message(brokenMessage, remote);
    }
    switch (messageId)
    {
    case MessageType<Message::Broken>::id:
        return Message(deserializeBroken(messageData), remote);
    case MessageType<Message::Ping>::id:
        return Message(deserializePing(messageData), remote);
    case MessageType<Message::Pong>::id:
        return Message(deserializePong(messageData), remote);
    case MessageType<Message::Unknown>::id:
        return Message(deserializeUnknown(messageData), remote);
    default:
        logger.error("Unknown message type: " + std::to_string(messageId));
        return Message(Message::Unknown{messageData}, remote);
    }
}