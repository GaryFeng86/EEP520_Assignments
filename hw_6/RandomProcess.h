#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <random>
#include <elma/elma.h>

class RandomProcess : public elma::Process {
public:
    RandomProcess(std::string name);
    void init();
    void update();
    void start();
    void stop();

private:
    std::default_random_engine _generator;
    std::uniform_real_distribution<double> _distribution;
    elma::Channel& _link;
};

#endif // RANDOM_PROCESS_H
