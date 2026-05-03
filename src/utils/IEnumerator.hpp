#pragma once

template <class T>
struct IEnumerator{
    public:
    virtual ~IEnumerator() = default;
    virtual bool MoveNext() = 0;
    virtual T& Current() const = 0;
    virtual void Reset() = 0;
}; 

template <class T>
class IEnumerable {
    public:
    virtual ~IEnumerable() = default;

    virtual IEnumerator<T>* GetEnumerator() const = 0;
};