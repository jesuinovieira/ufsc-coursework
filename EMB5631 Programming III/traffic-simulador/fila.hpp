#ifndef FILA_HPP
#define FILA_HPP

#include <iostream>
#include <memory>
#include "cell.hpp"

using namespace std;

template <typename T>
class List {
public:
    List ();
    ~List ();
    List (T data);
    bool empty () const;
    unsigned int getSize () const;
    T  dataPos (unsigned int pos) const;
    void insertPos (unsigned int pos, T data);
    virtual void insertHead (T data);
    virtual void insertTail (T data);
    T getHeadData () const;
    T getTailData () const;
    void removePos (unsigned int pos);
    virtual void removeHead ();
    virtual void removeTail ();
    void printOut () const;
    void insertOrdenate (T data);
    friend ostream& operator << (ostream &output, const List <T> &_list) {
        shared_ptr <Cell<T>> hold = _list._head;
        if (hold == nullptr) output << "Empty!";
        for (unsigned int i = 0; i < _list._size; i++) {
            output << *hold <<  " ";
            hold = hold->next ();
        }
        return output;
    }

protected:
    shared_ptr <Cell <T>> _head;
    shared_ptr <Cell <T>> _tail;
    static unsigned int _size;
    shared_ptr <Cell<T>> getCellPos (unsigned int pos) const;
    shared_ptr <Cell<T>> getHead () const;
    shared_ptr <Cell<T>> getTail () const;
};

template <typename T>
unsigned int List<T>::_size = 0;

template <typename T>
List<T>::List () {
    _head = nullptr;
    _tail = nullptr;
}

template <typename T>
List<T>::~List () {
    shared_ptr <Cell <T>> temp = _head;
    while (temp != nullptr) {
        shared_ptr <Cell <T>> hold = temp->next ();
        temp->pointPrev (nullptr);
        temp->pointNext (nullptr);
        temp = hold;
    }
}

template <typename T>
List<T>::List (T data) {
    shared_ptr <Cell <T>> hold = make_shared <Cell<T>> (data);
    _head = hold;
    _tail = hold;
    _size++;
}

template <typename T>
unsigned int List<T>::getSize () const {
    return _size;
}

template <typename T>
T List<T>::getHeadData () const {
    return _head->getData ();
}


template <typename T>
T List<T>::getTailData () const {
    return _tail->getData ();
}

template <typename T>
shared_ptr <Cell<T>> List<T>::getHead () const {
    return _head;
}


template <typename T>
shared_ptr <Cell<T>> List<T>::getTail () const {
    return _tail;
}

template <typename T>
void List<T>::insertPos (unsigned int pos, T data) {

    if (pos == 0 || empty () == true) {
        insertHead (data);
        return;
    }

    if (pos >= getSize ()) {
        insertTail (data);
        return;
    }

    shared_ptr <Cell <T>> hold = make_shared <Cell<T>> (data);
    shared_ptr <Cell<T>> temp = _head;

    for (unsigned int i = 0; i < pos - 1; i++) {
        temp = temp->next ();
    }
    shared_ptr <Cell<T>> next = temp->next ();

    temp->pointNext (hold);
    hold->pointNext (next);
    next->pointPrev (hold);
    hold->pointPrev (temp);
    _size++;
}

template <typename T>
bool List<T>::empty () const {
    if (getSize () == 0) return true;
    return false;
}

template <typename T>
T List<T>::dataPos (unsigned int pos) const {
    shared_ptr <Cell<T>> hold = getCellPos (pos);
    return hold->getData ();
}

template <typename T>
void List<T>::removeHead () {
    shared_ptr <Cell<T>> hold = _head->next ();
    _head->pointNext (nullptr);
    hold->pointPrev (nullptr);
    _head = hold;
    _size--;
}

template <typename T>
void List<T>::removeTail () {
    shared_ptr <Cell<T>> hold = _tail->prev ();
    _tail->pointPrev (nullptr);
    hold->pointNext (nullptr);
    _tail = hold;
    _size--;
}

template <typename T>
void List<T>::insertHead (T data) {
    shared_ptr <Cell <T>> hold = make_shared <Cell<T>> (data);

    if (empty () == true) {
        hold->pointNext (nullptr);
        hold->pointPrev (nullptr);
        _head = hold;
        _tail = hold;
        _size++;
        return;
    }

    hold->pointNext (_head);
    _head->pointPrev (hold);
    hold->pointPrev (nullptr);
    _head = hold;
    _size++;
}

template <typename T>
void List<T>::insertTail (T data) {
        shared_ptr <Cell <T>> hold = make_shared <Cell<T>> (data);
        if (empty () == true) {
            hold->pointNext (nullptr);
            hold->pointPrev (nullptr);
            _head = hold;
            _tail = hold;
            _size++;
            return;
        }

        hold->pointNext (nullptr);
        hold->pointPrev (_tail);
        _tail->pointNext (hold);
        _tail = hold;
        _size++;
}




template <typename T>
void List<T>::removePos (unsigned int pos) {
    if (empty () == 1) {
        return;
    }
    if (getSize () == 1) {
        _head->pointNext (nullptr);
        _head->pointPrev (nullptr);
        _head = nullptr;
        _tail = nullptr;
        _size--;
        return;
    }
    if (pos >= getSize ()) {
        removeTail ();
        return;
    }

    if (pos <= 1) {
        removeHead ();
        return;
    }

    shared_ptr <Cell<T>> hold = getCellPos (pos);
    hold->prev ()->pointNext (hold->next ());
    hold->next ()->pointPrev (hold->prev ());
    hold->pointNext (nullptr);
    hold->pointPrev (nullptr);
    _size--;
}

template <typename T>
void List<T>::insertOrdenate (T data) {

    if (empty () == true) {
        insertHead (data);
        return;
    }
    Cell <T> hold (data);
    if (hold <= *_head) {
        insertHead (data);
        return;
    }
    if (hold >= *_tail) {
        insertTail (data);
        return;
    }

    shared_ptr <Cell<T>> temp = _head;
    int pos = 0;
    while (hold >= *temp) {
        temp = temp->next ();
        pos++;
    }
    insertPos (pos, data);
}

template <typename T>
void List<T>::printOut () const {

    shared_ptr <Cell<T>> hold = _head;
    //shared_ptr <Cell<T>> temp = _list._head;
    if (hold == nullptr) {
        cout << "Empty!" << endl;;
        return;
    }
    while (hold != nullptr) {
        cout << *hold <<  " ";
        hold = hold->next ();
    }
    cout << endl;
}

//private methods

template <typename T>
shared_ptr <Cell<T>> List<T>::getCellPos (unsigned int pos) const {

    if (pos == 0) return _head;
    if (pos >= getSize ()) return _tail;

    shared_ptr <Cell<T>> hold = _head;
    for (unsigned int i = 0; i < pos - 1; i++) {
        hold = hold->next ();
    }
    return hold;
}

// ******************************************************************

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class Cell {
public:
    Cell (T data);
    ~Cell ();
    //Cell ();
    T getData () const;
    shared_ptr <Cell <T>> next () const;
    shared_ptr <Cell <T>>  prev () const;
    friend ostream& operator << (ostream &output, const Cell<T> &_cell) {
        output << _cell._data;
        return output;
    }
    friend bool operator == (const Cell<T> &_cell1, const Cell<T> &_cell2) {
        if (_cell1._data == _cell2._data) return true;
        return false;
    }
    friend bool operator != (const Cell<T> &_cell1, const Cell<T> &_cell2) {
        if (_cell1._data != _cell2._data) return true;
        return false;
    }
    friend bool operator <= (const Cell<T> &_cell1, const Cell<T> &_cell2) {
        if (_cell1._data <= _cell2._data) return true;
        return false;
    }
    friend bool operator >= (const Cell<T> &_cell1, const Cell<T> &_cell2) {
        if (_cell1._data >= _cell2._data) return true;
        return false;
    }
    void pointNext (shared_ptr <Cell <T>> _cell);
    void pointPrev (shared_ptr <Cell <T>> _cell);

private:
    T _data;
    shared_ptr <Cell <T>>_next;
    shared_ptr <Cell <T>> _prev;
};

template <typename T>
Cell<T>::Cell (T data):  _next {nullptr}, _prev {nullptr} {
    _data = data;
}

template <typename T>
Cell<T>::~Cell () {
    _next = nullptr;
    _prev = nullptr;
}

template <typename T>
T Cell<T>::getData () const {
    return _data;
}

template <typename T>
shared_ptr <Cell <T>> Cell <T>::next () const {
    return _next;
}

template <typename T>
shared_ptr <Cell <T>> Cell <T>::prev () const {
    return _prev;
}

template <typename T>
void Cell <T>::pointNext (shared_ptr <Cell <T>> _cell)  {
    _next = _cell;
}

template <typename T>
void Cell <T>::pointPrev (shared_ptr <Cell <T>> _cell)  {
    _prev = _cell;
}

// ********************************************************

template <typename T>
class Queue: private List<T> {
public:
    void insertQueue (T data);
    void removeQueue ();
    Cell <T> getHead () const;
    T getHeadData () const;
    T getTail () const;
    unsigned int getSize () const;
    bool empty () const;
    void printOut () const;
    friend ostream &operator << (ostream &output, const Queue <T> &_queue) {
        output << (const List<T> &)_queue;
        //output << static_cast
        return output;
    }
};

template <typename T>
void Queue<T>::insertQueue (T data) {
    List<T>::insertTail (data);
}

template <typename T>
void Queue<T>::removeQueue () {
    List<T>::removePos (0);
}

template <typename T>
Cell <T> Queue<T>::getHead () const {
    return List<T>::getHead ();
}

template <typename T>
T Queue<T>::getHeadData () const {
    return List<T>::getHeadData ();
}

template <typename T>
void Queue<T>::printOut () const {
    return List<T>::printOut ();
}

template <typename T>
T Queue<T>::getTail () const {
    return List<T>::getTail ();
}

template <typename T>
unsigned int Queue<T>::getSize () const {
    return List<T>::getSize ();
}

template <typename T>
bool Queue<T>::empty () const {
    return List<T>::empty ();
}

#endif // FILA_HPP
