#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "ItemList.h"
#include "Iterator.h"

template <class Item>
class ListIterator : public Iterator<Item> {
public:
    ListIterator(const List<Item>* aList);
    ListIterator(const ListIterator& a);
    ListIterator& operator=(const ListIterator& other);
    virtual void First();
    virtual void Next();
    virtual bool IsDone() const;
    virtual Item CurrentItem() const;

private:
    const List<Item>* _list;
    long _current;
};

#include "ListIterator.cpp"

#endif /* LIST_ITERATOR_H */
