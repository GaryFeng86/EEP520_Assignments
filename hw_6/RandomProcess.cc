#include "RandomProcess.h"

RandomProcess::RandomProcess(std::string name)
        : Process(name), _generator(std::random_device{}()), _distribution(0, 1), _link(channel("link")) {}

void RandomProcess::init() {}

void RandomProcess::update() {
    _link.send(_distribution(_generator));
}

void RandomProcess::start() {}

void RandomProcess::stop() {}
