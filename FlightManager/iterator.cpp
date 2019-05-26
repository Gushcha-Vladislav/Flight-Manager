#include "iterator.h"

template<typename V>
Iterator<V>::Iterator(V *value) :value(value)
{

};

template<typename V>
Iterator<V>::Iterator(const V& it) :value(it.value)
{

};

template<typename V>
bool Iterator<V>::operator!=(Iterator const& other) const
{
    return value != other.value;
};

template<typename V>
bool Iterator<V>::operator==(Iterator const& other) const
{
    return value == other.value;
};

template<typename V>
typename Iterator<V>::reference Iterator<V>::operator*() const
{
    return *value;
};

template<typename V>
Iterator<V> &Iterator<V>::operator++()
{
    ++value;
    return *this;
};
