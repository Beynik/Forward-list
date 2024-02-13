#include <iostream>
#include "forwardList.h"

int main()
{
    std::cout << "Hello World!\n";
    forwardList <int> j(5, 4);
    forwardList <int> jo(j);
    jo.push_front(6);
}
