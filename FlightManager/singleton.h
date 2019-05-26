#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <QDebug>

template <class T>
class Singleton
{
private: static T singleton = NULL;
protected:
    Singleton() {}
    ~Singleton() {}
public:
//    Singleton(Singleton const &) = delete;
//    Singleton& operator=(Singleton const &) = delete;

    static T& getInstance()
    {
        if (singleton == NULL) {
            qDebug() << "NULL";
            return new T();
        } else {
            qDebug() << "NOT NULLL";
            return singleton;
        }
    }
};

#endif // SINGLETON_H
