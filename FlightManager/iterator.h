#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <assert.h>

template<class V>
class  Iterator : public std::iterator<std::input_iterator_tag, V>
{
    friend class OwnContainer;
private:
    Iterator(V* value);
public:
    Iterator(const V &it);
    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const; //need for BOOST_FOREACH
    typename Iterator::reference operator*() const;
    Iterator& operator++();
private:
    V* value;
};

#endif // ITERATOR_H
