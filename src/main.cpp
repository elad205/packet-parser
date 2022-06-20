#include "packet.h"
#include <stdio.h>

struct Test {
    Test()
    {
        printf("Whihihih\n");
    }
    bool Deserialize(uint8_t *data)
    {
        return true;
    }
    uint32_t a;
};
int main(void)
{
    Packet::Packet<300, Test> x{};
    printf("sizoef data: %u\n sizeof test: %u\n", sizeof(x), sizeof(Test));
    Test l{};
    x.Set(l);
    return 0;
}