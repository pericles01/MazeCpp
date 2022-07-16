#pragma once

#include <string>
#include <utility>
#include <vector>

using Position = std::pair<unsigned int, unsigned int>;
using GameState = std::vector<std::string>;
using Obstacles = std::vector<Position>;

constexpr unsigned int LEN_X = 5;
constexpr unsigned int LEN_Y = 5;

constexpr uint32_t NUM_OBSTACLES = 3U;

enum class ConsoleInput : int
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    INVALID
};
class Game
{
public:
    Game();
    void execute();

private:
    static ConsoleInput map_user_input(const char user_input);

    GameState update_game_state(const Position &player, const Obstacles &obstacles);

    static uint32_t random_uint(const uint32_t lower, const uint32_t upper);

    static Position random_position(const uint32_t lower_x,
                                    const uint32_t upper_x,
                                    const uint32_t lowery,
                                    const uint32_t upper_y);

    void print_game_state(const Position &player, const Obstacles &obstacles);

    Position execute_move(Position &player, const ConsoleInput move);

    bool is_finished(const Position &player);

    bool is_dead(const Position &player, const Obstacles &obstacles);

    void move_obstacles();

    const Position m_start = std::make_pair(4U, 4U);
    const Position m_goal = std::make_pair(0U, 0U);

    Position m_player = std::make_pair(0U, 0U);
    Obstacles m_obstacles = std::vector<Position>{NUM_OBSTACLES};
};
