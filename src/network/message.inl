// 显然是仿照的SFML的Event设计的
#pragma once
#include "network/message.hpp"
namespace Network
{
    template <typename TMessageSubtype>
    Message::Message(const TMessageSubtype &eventSubtype)
    {
        static_assert(isEventSubtype<TMessageSubtype>, "TMessageSubtype must be a subtype of Network::Message");
        if constexpr (isEventSubtype<TMessageSubtype>)
            m_data = eventSubtype;
    }
    template <typename TMessageSubtype>
    bool Message::is() const
    {
        static_assert(isEventSubtype<TMessageSubtype>, "TMessageSubtype must be a subtype of Network::Message");
        if constexpr (isEventSubtype<TMessageSubtype>)
            return std::holds_alternative<TMessageSubtype>(m_data);
    }
    template <typename TMessageSubtype>
    const TMessageSubtype *Message::getIf() const
    {
        static_assert(isEventSubtype<TMessageSubtype>, "TMessageSubtype must be a subtype of Network::Message");
        if constexpr (isEventSubtype<TMessageSubtype>)
            return std::get_if<TMessageSubtype>(&m_data);
    }
    [[nodiscard]] inline std::vector<std::byte> Message::serialize() const
    {
        return std::visit([](const auto &msg)
                          {
                              return ::Network::serialize(msg);
                          },
                          m_data);
    }
} // namespace Network