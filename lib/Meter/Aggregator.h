#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <queue>

using namespace std;

class Aggregator
{
    private:
        vector<float> buffer;
        const unsigned int windowSize = 10;
    
    public:
        Aggregator();
        float aggregate(float value);

};

#endif