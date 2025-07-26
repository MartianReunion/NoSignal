# network模块

network模块用于管理服务端与客户端的网络连接，以及网络数据收发。

## Message的封装格式

| 名称 | 长度（字节） | 起始位置（字节） | 描述                            |
| ---- | ------------ | ---------------- | ------------------------------- |
| 类型 | 2            | 0                | 对应`MessageTypeId`的值，大端序 |
| 长度 | 8            | 2                | 数据长度，大端序                |
| 数据 | -            | 10               | 数据，长度由`长度`字段指定      |

## 如何添加新的消息类型

1. 在`message.hpp`的`Network::Message`类中添加子类型为结构体，使其成为`Network::Message::YOUR_MESSAGE_TYPE`。
2. 在`message.hpp`的`Network::MessageTypeId`一栏下方添加如下代码：

   ```cpp
   template <>
   struct MessageTypeId<Message::YOUR_MESSAGE_TYPE>
   {
       static constexpr uint16_t value = YOUR_MESSAGE_TYPE_ID;//递增，不得占用0xFFFF。
   };
   ```

3. 在`message.hpp`的`serialize`区域中添加如下代码：

   ```cpp
   std::vector<std::byte> serialize(const Message::YOUR_MESSAGE_TYPE &);
   ```

4. 在`message.cpp`中实现你的`serialize`函数，需遵循前文提及的封装格式。
5. 在`message.cpp`的`Network::makeMessage`函数中`switch`部分添加解码逻辑（`switch`前已将封装数据拆开，可直接使用存储其中的数据字段）。
6. 在`/test/message_test.cpp`中`Message Test Case`中添加一个`SECTION`用于测试你的消息类型。
