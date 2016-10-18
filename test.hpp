#include <string>

constexpr char fmt_str[] = \
"{\n"
"   \"controlPointId\" : \"%s\",\n"
"   \"upnpData\"       :\n"
"     {\n"
"        \"controlPointInfo\" :\n"
"         {\n"
"            \"appProperties\" : {}\n"
"         }\n"
"     }\n"
"}";

class JString {
    std::string fmt;
public:
    JString(const char _fmt[] = "{}") : fmt(_fmt) {}

private:
};

