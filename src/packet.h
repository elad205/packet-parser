#ifndef PACKET_H
#define PACKET_H

#include "ILayer.h"
#include <functional>
#include <stddef.h>
#include "utils.h"

namespace Packet
{
template <Layers::Deserializable... Layers>
class Packet
{
public:
    Packet()
    {
        size_t total_size{};
        init_layers<sizeof...(Layers), Layers...>(total_size);
    }

    template<typename Layer>
    auto &Fetch()
    {
        return _Get<sizeof...(Layers), 0, Layer, Layers...>(); 
    }

    const uint8_t *Serialize()
    {
        return m_data;
    }

    bool Deserialize(const uint8_t *data, size_t data_size)
    {
        if (data_size < sizeof(m_data))
        {
            return false;
        }

        return _Deserialize<0, Layers...>(data);
    }

private:
    uint8_t m_data[Utils::total_size<Layers...>()];

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
    
    template<size_t LAYER_NUMBER, size_t DATA_OFFSET, typename Target, class First, class... Rest>
    constexpr Target &_Get()
    {

        static_assert(!(LAYER_NUMBER == 1 && !std::is_same<Target, First>::value), "Tried to fetch a non existing layer");

        if constexpr (std::is_same<Target, First>::value)
        {
            return *reinterpret_cast<Target*>(m_data + DATA_OFFSET);
        }
        else
        {
            return _Get<LAYER_NUMBER - 1, DATA_OFFSET + sizeof(First), Target, Rest...>();
        }
    }

    template<size_t CURRENT_OFFSET, class First, class... Rest>
    bool _Deserialize(const uint8_t *data)
    {
        return (*reinterpret_cast<First*>(m_data + CURRENT_OFFSET)).Deserialize(data) && \
                _Deserialize<CURRENT_OFFSET + sizeof(First), Rest...>(data + sizeof(First));
    }

    template<size_t CURRENT_OFFSET>
    bool _Deserialize(const uint8_t *data)
    {
        return true;
    }

};
} // namespace Packet

#endif // !PACKET_H