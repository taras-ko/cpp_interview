#include <utility>
#include <string>

class DeviceType {
public:
    enum class Id : char {
        ECHO_STAR,
        DIRECT_TV
    };
private:
    static constexpr char tab[] = {
        "dfsf",
        "dflkj"
    };
    /*
    static constexpr std::pair<Id, std::string> tab[] = {
        (Id::ECHO_STAR, "blah")
    };
    */
};
