#include "highscore.hpp"
#include <filesystem>
#include <fstream>

namespace {
constexpr auto filename = "data.tts";

} // namespace

std::vector<int> loadHighscores()
{
    std::filesystem::path path { filename };
    if (!std::filesystem::exists(path)) {
        std::vector<int> v {};
        v.resize(5, 0);
        return v;
    }

    std::ifstream in {};
    in.open(path, std::ios_base::binary);
    if (in.fail()) {
        throw std::logic_error { "cannot open highscores file for read." };
    }
    std::vector<int> scores;
    int a {};
    while (in >> a) {
        if (a < 0) {
            throw std::invalid_argument { "time score can not be negative." };
        }
        scores.push_back(a);
    }
    return scores;
}

void saveHighscores(std::vector<int> const& scores)
{
    std::ofstream out {};
    out.open(filename, std::ios_base::binary);

    if (out.fail()) {
        throw std::logic_error { "cannot open highscores file for write." };
    }

    for (auto const& v : scores) {
        out << v << std::endl;
    }
}
