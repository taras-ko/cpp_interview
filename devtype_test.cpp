#include <iostream>
#include <cstring>

class DeviceType {
public:
    enum class Id {
        UNKNOWN_DEVICE = -1,
        ECHO_STAR,
        DIRECT_TV,
        SIZE,
    };

private:
    struct tab_record {
        Id type_id;
        const char *type_str;
    };
    static const tab_record tab[];

public:
    static const char *get(Id type_id) {
        for (int i = 0; i < (int)Id::SIZE; i++) {
            if (type_id == tab[i].type_id)
                return tab[i].type_str;
        }
        return nullptr;
    }
    static const int get(const char *type_str) { // return negative when not found
        for (int i = 0; i < (int)Id::SIZE; i++) {
            if (strcmp(type_str, tab[i].type_str) == 0) // found match
                return (const int)tab[i].type_id;
        }
        return (const int)Id::UNKNOWN_DEVICE;
    }
};

const DeviceType::tab_record DeviceType::tab[] = {
    { Id::ECHO_STAR, "urn:schemas-echostar-com:device:EchoStarDevice:1" },
    { Id::DIRECT_TV, "TODO: Need to determine this type!" }
};

int main()
{
    const char* res = DeviceType::get();
    if (res)
        std::cout << res << std::endl;

    std::cout << DeviceType::get("TODO: Need to determine this type!");

}
