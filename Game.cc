
#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <random>

uint32_t Game::random_uint(const uint32_t lower, const uint32_t upper)
{
    std::random_device gen;
    std::uniform_int_distribution<uint32_t> dist(lower, upper);
    return dist(gen);
}

Position Game::random_position(const uint32_t lower_x,
                               const uint32_t upper_x,
                               const uint32_t lower_y,
                               const uint32_t upper_y)
{
    return Position{random_uint(lower_x, upper_x), random_uint(lower_y, upper_y)};
}
ConsoleInput Game::map_user_input(const char user_input)
{
    switch (user_input)
    {
    case 'a':
        return ConsoleInput::LEFT;
    case 'd':
        return ConsoleInput::RIGHT;
    case 'w':
        return ConsoleInput::UP;
    case 's':
        return ConsoleInput::DOWN;
    default:
        return ConsoleInput::INVALID;
    }
}
Game::Game()
{
    for (auto &obs : m_obstacles)
    {
        obs = random_position(1, LEN_X - 1, 1, LEN_Y - 1);
    }
}
void Game::print_game_state(const Position &player, const Obstacles &obstacles)
{
    GameState game_state(LEN_X, std::string(LEN_Y, '.'));

    game_state[m_start.first][m_start.second] = '|';
    game_state[m_goal.first][m_goal.second] = '|';
    game_state[player.first][player.second] = 'P';

    for (const auto &obs : obstacles)
    {
        game_state[obs.first][obs.second] = 'X';
    }

    for (unsigned int i = 0; i < LEN_X; i++)
    {
        for (unsigned int j = 0; j < LEN_Y; j++)
            std::cout << game_state[i][j] << " ";
        std::cout << std::endl;
    }
}
Position Game::execute_move(Position &player, const ConsoleInput move)
{
    switch (move)
    {
    case ConsoleInput::LEFT:
        if (player.second > m_start.second)
        {
            player.second--;

            std::cout << "You moved to the left!" << std::endl;
        }
        else
        {
            std::cout << "You bounced!" << std::endl;
        }
        break;

    case ConsoleInput::RIGHT:
    {
        if (player.second < m_start.second)
        {
            player.second++;

            std::cout << "You moved to the right!" << std::endl;
        }
        else
        {
            std::cout << "You bounced!" << std::endl;
        }
        break;
    }
    case ConsoleInput::UP:
    {
        if (player.first > m_goal.first)
        {
            player.first--;

            std::cout << "You moved up!" << std::endl;
        }
        else
        {
            std::cout << "You bounced!" << std::endl;
        }
        break;
    }
    case ConsoleInput::DOWN:
    {
        if (player.first < m_goal.first)
        {
            player.first++;

            std::cout << "You moved down!" << std::endl;
        }
        else
        {
            std::cout << "You bounced!" << std::endl;
        }
        break;
    }
    case ConsoleInput::INVALID:
    default:
    {
        std::cout << "Unrecognized move!" << std::endl;
    }
    }

    return player;
}


bool Game::is_finished(const Position &player)
{
    if (m_goal == player)
    {
        std::cout << "You won the game!" << std::endl;
        return true;
    }
    return false;
}

bool Game::is_dead(const Position &player, const Obstacles &obstacles)
{
    for (const auto &obs : obstacles)
    {
        if (player == obs)
        {
            std::cout << "You Died!" << std::endl;
            return true;
        }
    }
    return false;
}
void Game::move_obstacles()
{
    for (auto &obs : m_obstacles)
    {
        Position offset = random_position(-1, 1, -1, 1);
        if (obs.first + offset.first < LEN_X && obs.second + offset.second < LEN_Y)
        {
            obs.first += offset.first;
            obs.second += offset.second;
        }
    }
}

void Game::execute()
{
    char user_input = 0;
    ConsoleInput move;

    while (true)
    {
        if (is_finished(m_player) || is_dead(m_player, m_obstacles))
        {
            break;
        }

        print_game_state(m_player, m_obstacles);

        std::cin >> user_input;
        move = map_user_input(user_input);
        system("clear");

        m_player = execute_move(m_player, move);
        move_obstacles();
    }
}
