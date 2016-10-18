#include <iostream>
#include <string>

#include <cstdio>
#include <cctype>

int extract_ip(char *dest, const char *src)
{
    char *p = dest;

    while (!isdigit(*src)) // find first IP address digit.
        src++;

    while (*src != ':' && *src != '/') {
        *p = *src;
        p++;
        src++;
    }

    *p = '\0';

    return dest - p; // length of string
}

inline bool extractIp(std::string& dest, const std::string& src)
{
    char ip_str[16] = "";

    int n = extract_ip(ip_str, src.c_str());

    dest = std::string(ip_str);

    return (n >= 7) ? true : false;
}

int main()
{
    const char url[] =  "http://172.31.149.111:2869/upnphost";

    std::string ip;

    extractIp(ip, std::string(url));

    std::cout << ip << std::endl;
}
