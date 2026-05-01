#pragma once
#include "Sequence.hpp"

template <class T>
class EnumeratorSequence : public IEnumerator<T>{
    private:
    const Sequence<T>* sequence;
    int index;
    bool flag;
    
    public:
    EnumeratorSequence(const Sequence<T>* seq);

    bool MoveNext() override;
    T Current() const override;
    void Reset() override;
};

#include "EnumeratorSequence.tpp"