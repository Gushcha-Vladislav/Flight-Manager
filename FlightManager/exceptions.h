#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include "edge.h"

class Exception  {
public:
    Exception() {printError();}
    Exception(const std::string& msg) : msg_(msg) {printError();}
    ~Exception(){}
    std::string getMessage( ) const {return(msg_);}
    void printError() {
        std::cerr << getMessage( ) << std::endl;
    }
private:
    std::string msg_;
};

class FileException: public Exception {
private:
    std::string file_name;
public:
    FileException(std::string file_name): Exception("Cannot open file:" + file_name) {
        this->file_name = file_name;
    }
    std::string getFileName(){return this->file_name;}
};

class EdgeLoopException: public Exception {
private:
    int from_id;
    Edge *edge;
public:
    EdgeLoopException(int from_id, Edge *edge): Exception("Edge id: " + std::to_string(edge->get_id())) {
        this->from_id = from_id;
        this->edge = edge;
    }
    int getFromId(){ return  this->from_id; }
    Edge *getEdge(){ return this->edge; }
};

class EdgeDeletingException: public Exception {
private:
    int to_id, fly_time;
public:
    EdgeDeletingException(int to_id, int fly_time): Exception("Edge to id " + std::to_string(to_id)
                                                                           + " with fly time " + std::to_string(fly_time) + " does not existing") {
        this->to_id = to_id;
        this->fly_time = fly_time;
    }
    int getToId(){ return this->to_id; }
    int getFlyTime(){ return this->fly_time; }
};

#endif // EXCEPTIONS_H
