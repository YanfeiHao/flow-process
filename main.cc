#include "utility/ReferenceTools.hpp"
#include <string>

int main(int argc, char *argv[])
{
    std::string str;
    const std::string const_string ("xxx");
    utility::move (str);
    //utility::move (std::string ("123"));
    //utility::move (const_string);
}
