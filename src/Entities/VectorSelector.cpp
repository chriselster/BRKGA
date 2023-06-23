#ifndef __VECTORSELECTOR_H__
#define __VECTORSELECTOR_H__

#include <vector>
#include <cmath>

template <typename T>
class VectorSelector
{
    std::vector<T> &values;

public:
    VectorSelector(std::vector<T> &values) : values(values) {}
    T operator()(float i)
    {
        int pos = floor(i * values.size());
        return values[pos];
    }
};

#endif // __VECTORSELECTOR_H__