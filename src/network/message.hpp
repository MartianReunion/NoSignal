// 显然是仿照的SFML的Event设计的
// 序列化后的格式为2字节ID，8字节大小，不定长字节数据
#pragma once
#include <type_traits>
#include <variant>
#include <cstddef>
#include <memory>
#include <cstdint>
#include <vector>
namespace Network
{
    class Message
    {
    public:
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
        struct Broken
        {
        };

        template <typename TMessageSubtype>
        Message(const TMessageSubtype &eventSubtype);
        template <typename TMessageSubtype>
        [[nodiscard]] bool is() const;
        template <typename TMessageSubtype>
        [[nodiscard]] const TMessageSubtype *getIf() const;
        [[nodiscard]] inline std::vector<std::byte> serialize() const;

    private:
        std::variant<Unknown,
                     Ping,
                     Pong,
                     Broken>
            m_data;
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
    struct MessageTypeId;
    template <>
    struct MessageTypeId<Message::Unknown>
    {
        static constexpr uint16_t value = 0;
    };
    template <>
    struct MessageTypeId<Message::Ping>
    {
        static constexpr uint16_t value = 1;
    };
    template <>
    struct MessageTypeId<Message::Pong>
    {
        static constexpr uint16_t value = 2;
    };
    template <>
    struct MessageTypeId<Message::Broken>
    {
        static constexpr uint16_t value = 3;
    };

    std::vector<std::byte> serialize(const Message::Unknown &msg);
    std::vector<std::byte> serialize(const Message::Ping &);
    std::vector<std::byte> serialize(const Message::Pong &);
    std::vector<std::byte> serialize(const Message::Broken &);
};
#include "network/message.inl"