/*
** EPITECH PROJECT, 2023
** include
** File description:
** NodeGene
*/

#pragma once

enum class type_of_node_gene { INPUT, HIDDEN, OUTPUT };

struct NodeGene {
        int s_id{0};
        type_of_node_gene s_typeof{};
        double value{0};
};
