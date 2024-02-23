#include "Filter.h"

Filter::Filter(std::string name)
        : Process(name), _running_average(0), _link(channel("link")) {}

void Filter::init() {}

void Filter::update() {
    while (!_link.empty()) {
        double value = _link.latest();
        _received_values.push(value);
        _running_average += (value - _running_average) / _received_values.size();
        if (_received_values.size() > 10) {
            _running_average -= _received_values.front() / _received_values.size();
            _received_values.pop();
        }
    }
}

void Filter::start() {}

void Filter::stop() {}

double Filter::value() {
    return _running_average;
}
