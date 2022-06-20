#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

namespace Utils
{

template <size_t N, class First, class... Rest>
constexpr void do_for(size_t& size)
{
    if constexpr (N == 0)
    {
        return;
    }
    size += sizeof(First);
    if constexpr (N == 1)
    {
        return;
    }
    else
    {
        do_for<N - 1, Rest...>(size);
    }
}

template <class... Args>
constexpr uint32_t total_size()
{
    size_t count{};
    do_for<sizeof...(Args), Args...>(count);
    return count;
}

} // namespace Utils
#endif // !UTILS_H