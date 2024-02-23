#ifndef FILTER_H
#define FILTER_H

#include <queue>
#include <elma/elma.h>

class Filter : public elma::Process {
public:
    Filter(std::string name);
    void init();
    void update();
    void start();
    void stop();
    double value();

private:
    std::queue<double> _received_values;
    double _running_average;
    elma::Channel& _link;
};

#endif // FILTER_H
