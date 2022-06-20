#ifndef PACKET_H
#define PACKET_H

#include "ILayer.h"
#include <functional>
#include <stddef.h>
#include "utils.h"

namespace Packet
{
template <uint32_t SIZE, Layers::Deserializable... Layers>
class Packet
{
public:
    Packet()
    {
        size_t total_size{};
        init_layers<sizeof...(Layers), Layers...>(total_size);
    }

    template<typename Layer>
    bool Set(Layer &&layer)
    {
        size_t size{};
        auto curr{this->GetLayer<sizeof...(Layers), Layer, Layers...>(size)};
        curr = layer;
        return true;
    }

private:
    uint8_t m_data[Utils::total_size<Layers...>() + SIZE];

    /**
     * Constructs each layer inside the packet's data.
     */
    template <size_t N, class First, class... Rest>
    void init_layers(size_t& total_size)
    {
        if constexpr (N == 0)
        {
            return;
        }
        new (m_data + total_size) First;
        total_size += sizeof(First);
        if constexpr (N == 1)
        {
            return;
        }
        else
        {
            init_layers<N - 1, Rest...>(total_size);
        }
    }
    template<size_t N, typename Target, class First, class... Rest>
    constexpr Target &GetLayer(size_t &total_size)
    {
        if constexpr (N == 0)
        {
            return m_data;
        }

        if constexpr (std::is_same<Target, First>::value)
        {
            return m_data + total_size;
        }

        total_size += sizeof(First);
        if constexpr (N == 1)
        {
            return m_data;
        }
        else
        {
            GetLayer<N - 1, Target, Rest...>(total_size);
        }
    }
};
} // namespace Packet

#endif // !PACKET_H