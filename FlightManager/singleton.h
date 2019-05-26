#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

template <class T>
class Singleton
{
protected:
    Singleton() {}
    ~Singleton() {}
public:
    Singleton(Singleton const &) = delete;
    Singleton& operator=(Singleton const &) = delete;

    static T& getInstance()
    {
        static T* instance;
        return instance;
    }
};

#endif // SINGLETON_H
