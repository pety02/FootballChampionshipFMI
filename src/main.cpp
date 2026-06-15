#include <iostream>
#include "Map.h"

int main() {
    Map<std::string, unsigned> wins = Map<std::string, unsigned>();
    wins.add("team 1", 6);
    wins.add("team 2", 7);
    wins.add("team 3", 8);

    for(const auto &[fst, snd] : wins) {
        std::cout << fst << " " << snd << std::endl;
    }

    return 0;
}
