/**
 * A game for GitHub Jam 2021
 * 
 * 
 * 
 * @author Zach Mertens-McConnell github.com/users/zmertens
 */ 


#include <stdexcept>
#include <iostream>

#include "Needle.hpp"

int main(int argc, char** argv)
{
    try
    {
        Needle needle (argc, argv);
        const int stuff = needle.doStuff();
    }
    catch (std::exception& exception)
    {
        std::cerr << "Application exception: " << exception.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
