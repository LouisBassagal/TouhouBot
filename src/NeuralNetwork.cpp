/*
** EPITECH PROJECT, 2023
** src
** File description:
** NeuralNetwork
*/

#include "NeuralNetwork.hh"
#include "ConnectionGene.hh"
#include "GlobalParameter.hh"
#include "Misc.hh"
#include "NodeGene.hh"
#include <algorithm>
#include <vector>

void NeuralNetwork::add_neuron(NodeGene &neuron)
{
    if (neuron.s_typeof == type_of_node_gene::INPUT)
        m_neurons_input.push_back(neuron);
    if (neuron.s_typeof == type_of_node_gene::HIDDEN)
        m_neurons_hidden.push_back(neuron);
    if (neuron.s_typeof == type_of_node_gene::OUTPUT)
        m_neurons_output.push_back(neuron);
}

std::vector<NodeGene> NeuralNetwork::feed_forward(std::vector<NodeGene> &inputs)
{
    std::vector<NodeGene> tmp{m_neurons_hidden};
    ssize_t sizeof_hidden{static_cast<long>(tmp.size())};
    tmp.insert(tmp.end(), m_neurons_output.begin(), m_neurons_output.end());
    std::vector<NodeGene> output{};

    for (size_t i{0}; i < inputs.size(); i++) {
        if (m_neurons_input.size() < i) {
            m_neurons_input.emplace_back(inputs[i]);
        } else {
            m_neurons_input[i] = inputs[i];
        }
    }
    for (size_t i{0}; i < tmp.size(); i++) {
        std::vector<ConnectionGene> feeding_into{};
        auto lambda = [&](const ConnectionGene &value) {
            if (value.s_enabled)
                if (value.s_id_out == tmp[i].s_id)
                    feeding_into.emplace_back(value);
        };
        std::for_each(m_weight.begin(), m_weight.end(), lambda);
        auto lambda2 = [&](const ConnectionGene &value) {
            for (size_t k{0}; i < m_neurons_input.size(); k++) {
                if (m_neurons_input[k].s_id == value.s_id_in)
                    tmp[i].value += m_neurons_input[k].value * value.s_weight;
            }
        };
        std::for_each(feeding_into.begin(), feeding_into.end(), lambda2);
        tmp[i].value = sigmoid(tmp[i].value);
    }

    m_neurons_hidden.clear();
    m_neurons_hidden.insert(m_neurons_hidden.begin(), tmp.begin(), tmp.begin() + sizeof_hidden);
    m_neurons_output.clear();
    m_neurons_output.insert(m_neurons_output.begin(), tmp.begin() + sizeof_hidden, tmp.end());
    output = m_neurons_output;
    for (NodeGene &value : m_neurons_input)
        value.value = 0;
    for (NodeGene &value : m_neurons_hidden)
        value.value = 0;
    for (NodeGene &value : m_neurons_output)
        value.value = 0;
    return output;
}

void NeuralNetwork::mutate_weight()
{
    for (size_t i{0}; i < m_weight.size(); i++) {
        double rdm{zero_one_rdm()};

        if (rdm < MUTATION_CHANCE) {
            m_weight[i].s_weight = rdm_value(-1.00, 1.00);
        } else {
            m_weight[i].s_weight += standardise_gaussian() / NON_MUTATE_DIVIDER;
        }
    }
}
