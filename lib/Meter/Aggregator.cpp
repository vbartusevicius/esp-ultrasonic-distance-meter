#include "Aggregator.h"
#include "Parameter.h"

Aggregator::Aggregator(Storage* storage, Logger* logger)
{
    this->storage = storage;
    this->logger = logger;
}

float Aggregator::aggregate(float value)
{
    const int averageWindow = atol(this->storage->getParameter(Parameter::AVG_SAMPLE_COUNT, "10").c_str());
    
    if (this->buffer.size() + 1 > averageWindow) {
        this->buffer.clear();
    }
    if (this->buffer.size() >= averageWindow) {
        this->buffer.erase(this->buffer.begin());
    }
    
    if (round(value) > 0) {
        this->buffer.push_back(value);
    } else {
        this->logger->info("Zero value given, skipping aggregation");
    }

    float data = 0.0;

    for (auto &element : this->buffer) {
        data += element;
    }

    return data / this->buffer.size();
}