#include <iostream>
#include "Application.hpp"

int main(int argc, char const *argv[])
{
    try
    {
        Application app(900, 650);
        app.run();
    }
    catch (const std::exception &error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return -1;
    }

    return 0;
}