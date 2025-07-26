// 显然是仿照的SFML的Event设计的
#pragma once
#include <type_traits>
#include <variant>
#include <cstddef>
namespace Network
{
    class Message
    {
    public:
        struct Unknown
        {
            char *data = nullptr;
            size_t size = 0;
        };
        struct Ping
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
                     Ping>
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