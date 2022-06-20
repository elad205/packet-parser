#include "packet.h"
#include <stdio.h>

struct Test {
    Test()
    {
        printf("Whihihih\n");
    }
    bool Deserialize(const uint8_t *data)
    {
        return true;
    }
    void print()
    {
        printf("Success! %d\n", a);
    }
    uint32_t a{30};
};

struct Test2 {
    Test2()
    {
        printf("Whihihih\n");
    }
    bool Deserialize(const uint8_t *data)
    {
        return true;
    }

    void print()
    {
        printf("Success! %d\n", a);
    }
    uint32_t a{69};
};


int main(void)
{
    Packet::Packet<Test> x{};
    printf("sizoef data: %lu\n sizeof test: %lu\n", sizeof(x), sizeof(Test));
    auto l{x.Fetch<Test>()};
    uint8_t buf;
    printf("%d --- %d\n", l.Deserialize(&buf), x.Deserialize(&buf, 8));
    l.print();
    return 0;
}