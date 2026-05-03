#pragma once
#include<exception>
#include <string>
#include <sstream>

class Exception : public std::exception {
private:
    const char* message;
    const char* files;
    const char* function;
    std::string full_msg;
public:
    Exception(const char* msg, const char* file, const char* func) : message(msg), files(file), function(func) {
        full_msg = std::string(func) + "() " + file + " :: " + msg;
    }
    
    ~Exception() noexcept override = default;

    const char* what() const noexcept override {
      return full_msg.c_str();
    }

};

#define THROW(Type, msg) throw Type(msg, __FILE__, __func__)

class IndexOutOfRangeException : public Exception {
public:
    IndexOutOfRangeException(const char* m, const char* f, const char* fn) : Exception(m, f, fn) {}
};

class InvalidArgumentException : public Exception {
public:
    InvalidArgumentException(const char* m, const char* f, const char* fn) : Exception(m, f, fn) {}
};

class NullPointerException : public Exception {
public:
    NullPointerException(const char* m, const char* f, const char* fn) : Exception(m, f, fn) {}
};

class EmptyListException : public Exception {
public:
    EmptyListException(const char* m, const char* f, const char* fn) : Exception(m, f, fn) {}
};

class IteratorPointerException : public Exception {
public: 
    IteratorPointerException(const char* m, const char* f, const char* fn) : Exception(m, f, fn) {} };