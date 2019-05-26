#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class Exception  {
public:
    Exception() {printError();}
    Exception(const std::string& msg) : msg_(msg) {printError();}
    ~Exception(){}
    std::string getMessage( ) const {return(msg_);}
    void printError() {
        std::cout << getMessage( ) << std::endl;
    }
private:
    std::string msg_;
};

class FileException: public Exception {
private:
   std::string file_name;
public:
    FileException(std::string file_name): Exception("Cannot open file:" + file_name) {}
};

class SimilarVertexException: public Exception {
private:
   std::string vertex;
public:
    SimilarVertexException(std::string vertex): Exception("Similar Vertices:" + vertex) {}
};

class EdgeLoopException: public Exception {
private:
   std::string edge_id;
public:
    EdgeLoopException(std::string edge_id): Exception("Loop at vertex. Edge id:" + edge_id) {}
};

#endif // EXCEPTIONS_H
