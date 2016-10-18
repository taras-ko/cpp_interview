#include <utility>

enum ControlCode
{
    Success,
    UnknownCommand,
    InvalidParameterValue
};

using ControlResult = std::pair<ControlCode, int>;

int main()
{
}
