#include "integrator.h"

Integrator::Integrator(int name, double delta) {}ntegrator(std::string name, double delta)
        : Process(name), _delta(delta), _integral(0), _link(channel("link")) {}

void Integrator::init() {}

void Integrator::update() {
    while (!_link.empty()) {
        _integral += _delta * _link.latest();
    }
}

void Integrator::start() {}

void Integrator::stop() {}

double Integrator::value() {
    return _integral;
}
