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