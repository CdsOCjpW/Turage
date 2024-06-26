#include <Simlan/Standard.hpp>
using namespace Simlan;

int main(int argc, char* argv[]) {
    UnorderedSet<string_view> argset;
    for (int i = 1; i < argc; ++i) {
        argset.insert(argv[i]);
    }
    Simlan::SimlanMain(argset);
    return 0;
}