/*
** EPITECH PROJECT, 2023
** include
** File description:
** Misc
*/

#pragma once

#include <random>

double gaussian_rand();

double standardise_gaussian();

double rdm_value(double min, double max);

double zero_one_rdm();

double sigmoid(double value);

static const std::mt19937 SEED{};
