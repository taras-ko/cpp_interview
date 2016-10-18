#if 0
#include <iostream>
#include <boost/regex.hpp>

int main(){

    std::string s {"172.31.149.66"};
    boost::smatch match;

    boost::regex pattern("(\\d{1,3}(\\.\\d{1,3}){3})");


    boost::regex_match(s, match, pattern);

    std::cout << match.size() << std::endl;

    return 0;
}

#include <string>
#include <iostream>
#include <boost/regex.hpp>

int main() {

    std::string text = "User JohnDoe, IP: 121.1.55.86";
    boost::regex expr ("User ([^,]*), IP: (\\d{1,3}(\\.\\d{1,3}){3})");

    boost::smatch matches;

    try
    {
        if (boost::regex_match(text, matches, expr)) {

            std::cout << matches.size() << std::endl;

#if 0
            for (unsinged int i = 1; i < matches.size(); i++) {
                std::string match (matches[i].first, matches[i].second);
                std::cout << "matches[" << i << "] = " << match << std::endl;
            }
#endif

        }
        else {
            std::cout << "\"" << expr << "\" does not match \"" << text << "\". matches size(" << matches.size() << ")" << std::endl;
        }
    } 
    catch (boost::regex_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
#endif

#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;

isdigit
int main()
{
  string s;
  boost::regex re("^{(APPLE|ORANGE),(\\d*)}$");
  boost::cmatch matches;

  while(true)
  {
    cout << "String: ";
    cin >> s;
    if(boost::regex_match(s.c_str(), matches, re))
    {
      for(int i=1; i<(int)matches.size(); i++)
      {
        string match(matches[i].first, matches[i].second);
        cout << "match[" << i << "]:  " << matches[i] << endl;
      }

    }
    else
    {
      cout << "no match" << endl;
    }
  }
  return 0;

}
