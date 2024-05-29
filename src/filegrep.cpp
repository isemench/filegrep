#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Filegrep\n";
    std::cout << "Arguments are: ";
    for (auto i = 1; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
