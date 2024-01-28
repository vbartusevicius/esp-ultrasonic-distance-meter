#include "Aggregator.h"

Aggregator::Aggregator() {}

float Aggregator::aggregate(float value)
{
    if (this->buffer.size() >= this->windowSize) {
        this->buffer.erase(this->buffer.begin());
    }
    this->buffer.push_back(value);

    float data = 0.0;

    for (auto &element : this->buffer) {
        data += element;
    }

    return data / this->windowSize;
}