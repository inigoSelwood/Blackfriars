#pragma once

#include "templates/passive.hpp"
#include "templates/component.hpp"

class Inductor : public Passive, public Component {

public:

    double value;

    static std::shared_ptr<Inductor> parse(TextBuffer &buffer);

    void simulate(const std::shared_ptr<Transient> &transient,
            const Schematic &schematic, const double &time) override;

};

std::shared_ptr<Inductor> Inductor::parse(TextBuffer &buffer) {
    return Passive::parse<Inductor>(buffer, 'L');
}

void Inductor::simulate(const std::shared_ptr<Transient> &transient,
        const Schematic &schematic, const double &time) {

    const double value = (1 / value) * transient->voltage_integral(nodes[0],
            nodes[1]);
    transient->add_current(nodes[1], nodes[0], name, value);
}
