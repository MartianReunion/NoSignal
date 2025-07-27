// 显然是仿照的SFML的Event设计的
// 序列化后的格式为2字节ID，8字节大小，不定长字节数据
#pragma once
#include <type_traits>
#include <variant>
#include <cstddef>
#include <memory>
#include <cstdint>
#include <vector>
#include "uuid/uuid.hpp"
namespace Network
{
    constexpr uint16_t MAGIC_NUMBER = 0x4E53; // 'NS' for NoSignal

    constexpr int MAGIC_NUMBER_SIZE = sizeof(MAGIC_NUMBER);
    constexpr int MESSAGE_ID_SIZE = sizeof(uint16_t);
    constexpr int MESSAGE_SIZE_SIZE = sizeof(uint64_t);
    constexpr int REMOTE_UUID_SIZE = sizeof(UUID);
    constexpr int METADATA_SIZE = MAGIC_NUMBER_SIZE + MESSAGE_ID_SIZE + MESSAGE_SIZE_SIZE + REMOTE_UUID_SIZE;
    constexpr int INITIAL_BUFFER_SIZE = 128;
    class Message
    {
    public:
        struct Broken
        {
            std::vector<std::byte> data;
        };

        struct Unknown
        {
            std::vector<std::byte> data;
        };
        struct Ping
        {
        };
        struct Pong
        {
        };

        template <typename TMessageSubtype>
        Message(const TMessageSubtype &eventSubtype, UUID sender);
        template <typename TMessageSubtype>
        [[nodiscard]] bool is() const;
        template <typename TMessageSubtype>
        [[nodiscard]] const TMessageSubtype *getIf() const;
        std::vector<std::byte> serialize(UUID &remote) const;
        [[nodiscard]] inline UUID getRemote() const { return remote; }

    private:
        std::variant<Broken,
                     Ping,
                     Pong,
                     Unknown>
            m_data;
        UUID remote;
        template <typename T, typename... Ts>
        [[nodiscard]] static constexpr bool isInParameterPack(const std::variant<Ts...> *)
        {
            return std::disjunction_v<std::is_same<T, Ts>...>;
        }
        template <typename T>
        static constexpr bool isEventSubtype = isInParameterPack<T>(decltype (&m_data)(nullptr));
    };

    Message makeMessage(const std::vector<std::byte> &data);

    template <typename T>
    struct MessageType;
    template <>
    struct MessageType<Message::Broken>
    {
        static constexpr uint16_t id = 0;
    };
    template <>
    struct MessageType<Message::Ping>
    {
        static constexpr uint16_t id = 1;
    };
    template <>
    struct MessageType<Message::Pong>
    {
        static constexpr uint16_t id = 2;
    };
    template <>
    struct MessageType<Message::Unknown>
    {
        static constexpr uint16_t id = 0xffff;
    };

    uint64_t serialize(const Message::Broken &msg, std::vector<std::byte>::iterator &out);
    uint64_t serialize(const Message::Ping &msg, std::vector<std::byte>::iterator &out);
    uint64_t serialize(const Message::Pong &msg, std::vector<std::byte>::iterator &out);
    uint64_t serialize(const Message::Unknown &msg, std::vector<std::byte>::iterator &out);
    Message::Broken deserializeBroken(const std::vector<std::byte> &data);
    Message::Ping deserializePing(const std::vector<std::byte> &data);
    Message::Pong deserializePong(const std::vector<std::byte> &data);
    Message::Unknown deserializeUnknown(const std::vector<std::byte> &data);
};
#include "network/message.inl"