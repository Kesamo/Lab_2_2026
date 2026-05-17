#pragma once
#include<exception>
#include<string>
#include<format>
#include <source_location>

class Exception : public std::exception {
private:
    std::string full_msg;
    const char* file;
public:
    Exception(std::string msg, const char* file, const char* func){
        full_msg = std::format("{}() {}::{}", func, file, msg);
    }
    
    ~Exception() noexcept override = default;

    const char* what() const noexcept override {
      return full_msg.c_str();
    }

};

class IndexOutOfRangeException : public Exception {
public:
    IndexOutOfRangeException(size_t idx, size_t size, const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Выход за границы. Индекс: {} Размер: {}", idx, size), loc.file_name(), loc.function_name()) {}

    IndexOutOfRangeException(size_t idx, const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Выход за границы. Индекс: {}", idx), loc.file_name(), loc.function_name()) {}

    IndexOutOfRangeException(const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Список пуст"), loc.file_name(), loc.function_name()) {}
};

class InvalidRangeException : public Exception {
public:
    InvalidRangeException(size_t startidx, size_t endidx, const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Не корекнтный диопозон от {} до {}",startidx ,endidx ), loc.file_name(), loc.function_name()) {}
};

class InvalidArgumentException : public Exception {
public:
    InvalidArgumentException(const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Нельзя изменить размер на отрицательное значение"), loc.file_name(), loc.function_name()) {}
};

class NullPointerException : public Exception {
public:
    NullPointerException(const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Передан нулевой указатель"), loc.file_name(), loc.function_name()) {}
};

class EmptyListException : public Exception {
public:
    EmptyListException(const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Лист пуст"), loc.file_name(), loc.function_name()) {}
};

class IteratorPointerException : public Exception {
public: 
    IteratorPointerException(size_t idx, const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Попытка получить элемент вне масива. Индекс: {}", idx), loc.file_name(), loc.function_name()) {};

    IteratorPointerException(const std::source_location loc = std::source_location::current()) 
    : Exception(std::format("Попытка получить элемент вне листа"), loc.file_name(), loc.function_name()) {};
};