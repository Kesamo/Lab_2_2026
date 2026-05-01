#pragma once

template <class T>
struct IEnumerator{
    public:
    virtual ~IEnumerator() = default;
    virtual bool MoveNext() = 0;
    virtual T Current() const = 0;
    virtual void Reset() = 0;
}; 