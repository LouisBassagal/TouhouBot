/*
** PROJECT, 2023
** include
** File description:
** Environment
*/

#pragma once

class Environment
{
    public:
        Environment() = default;
        Environment(Environment const &to_copy) = default;
        Environment(Environment &&to_move) = default;
        ~Environment() = default;
        Environment &operator=(Environment const &to_copy) = default;
        Environment &operator=(Environment &&to_move) = default;

    private:
};
