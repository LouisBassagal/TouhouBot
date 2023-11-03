/*
** EPITECH PROJECT, 2023
** src
** File description:
** misc
*/

#include "Misc.hh"

double zero_one_rdm()
{

    std::uniform_real_distribution value{0.00, 1.00};
    return value(SEED);
}

double rdm_value(double min, double max)
{

    std::uniform_real_distribution value{min, max};
    return value(SEED);
}

double gaussian_rand()
{
    double rdm{0.00};

    for (int i{0}; i < 6; i++) {
        rdm += zero_one_rdm();
    }

    return rdm / 6;
}
