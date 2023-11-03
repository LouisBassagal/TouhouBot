/*
** EPITECH PROJECT, 2023
** include
** File description:
** NeuralNetwork
*/

#pragma once

#include "ConnectionGene.hh"
#include "NodeGene.hh"
#include <vector>

class NeuralNetwork
{
    public:
        NeuralNetwork() = default;
        NeuralNetwork(NeuralNetwork const &to_copy) = default;
        NeuralNetwork(NeuralNetwork &&to_move) = default;
        ~NeuralNetwork() = default;
        NeuralNetwork &operator=(NeuralNetwork const &to_copy) = default;
        NeuralNetwork &operator=(NeuralNetwork &&to_move) = default;

        void add_neuron(NodeGene &neuron);
        std::vector<NodeGene> feed_forward(std::vector<NodeGene> &inputs);
        void mutate_weight();

    private:
        int m_nb_neurons{};
        int m_fitness{1};
        int m_id_species{0};
        std::vector<NodeGene> m_storage{};
        std::vector<NodeGene> m_neurons_input{};
        std::vector<NodeGene> m_neurons_hidden{};
        std::vector<NodeGene> m_neurons_output{};
        std::vector<ConnectionGene> m_weight{};
};
