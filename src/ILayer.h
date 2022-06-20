#ifndef ILAYER_H
#define ILAYER_H

#include <stdint.h>
#include <concepts>


namespace Layers
{

/* Each layer have to implement a way to make raw data into an object */
template<typename Layer>
concept Deserializable = requires(Layer &l, uint8_t *data)
{
    { l.Deserialize(data) } -> std::same_as<bool>;
};

}
#endif