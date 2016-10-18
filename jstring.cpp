#include <string>
#include <boost/format.hpp>

#include "test.hpp"

int main()
{

//    std::cout << boost::format("%1% %2% %3%!") % "Hello" % "World" % i;
    std::string json_str = boost::str( boost::format(fmt_str) % "Hello" );

    std::cout << json_str;
}
