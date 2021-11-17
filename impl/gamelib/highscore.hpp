#ifndef GAME_HIGHSCORE_INCLUDEUARD_HPP
#define GAME_HIGHSCORE_INCLUDEUARD_HPP

#include <vector>

std::vector<int> loadHighscores();
void saveHighscores(std::vector<int> const& scores);

#endif
