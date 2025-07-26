// 显然是仿照的SFML的Event设计的
#pragma once
#include <type_traits>
#include <variant>
#include <cstddef>
#include <memory>
#include <cinttypes>
namespace Network
{
    template<typename T> struct MessageTypeId;
    template<> struct MessageTypeId<Message::Unknown> { static constexpr u_int16_t value = 0; };
    template<> struct MessageTypeId<Message::Ping> { static constexpr u_int16_t value = 1; };
    template<> struct MessageTypeId<Message::Pong> { static constexpr u_int16_t value = 2; };
    class Message
    {
    public:
        struct Unknown
        {
            std::unique_ptr<std::byte[]> data;
            size_t size = 0;
        };
        struct Ping
        {
        };
        struct Pong
        {
        };

        template <typename TMessageSubtype>
        Message(const TMessageSubtype &eventSubtype);
        template <typename TMessageSubtype>
        [[nodiscard]] bool is() const;
        template <typename TMessageSubtype>
        [[nodiscard]] const TMessageSubtype *getIf() const;

    private:
        std::variant<Unknown,
                     Ping,
                     Pong>
            m_data;
        template <typename T, typename... Ts>
        [[nodiscard]] static constexpr bool isInParameterPack(const std::variant<Ts...> *)
        {
            return std::disjunction_v<std::is_same<T, Ts>...>;
        }
        template <typename T>
        static constexpr bool isEventSubtype = isInParameterPack<T>(decltype (&m_data)(nullptr));
    };
};
#include "network/message.inl"