#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <elma/elma.h>

class Integrator : public elma::Process {
public:
    Integrator(std::string name, double delta);
    void init();
    void update();
    void start();
    void stop();
    double value();

private:
    double _delta;
    double _integral;
    elma::Channel& _link;
};

#endif // INTEGRATOR_H
