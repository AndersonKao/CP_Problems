#include "class.h"
void MagicBox::add(string name){ // 0: add book
    if (size == capacity){
        Box *newbookbox = new Box(capacity*2);
        for (int i=0 ; i<size ; i++) newbookbox->books[i] = bookbox->books[i];
        delete bookbox;
        bookbox = newbookbox;
        capacity *= 2;
    }
    bookbox -> books[size] = name;
    size ++;
    return;
}

void MagicBox::remove(){ // 1: remove the last book
    if (size != 0) size --;
    return;
}

void MagicBox::resize(int newsize){ // 2: resize (increase then new; otherwise remain the same)
    if (newsize > capacity){
        Box *newbookbox = new Box(newsize);
        for (int i=0 ; i<size ; i++) newbookbox->books[i] = bookbox->books[i];
        delete bookbox;
        bookbox = newbookbox;
        capacity = newsize;
    }else if (newsize < size) size = newsize;
    return;
}

MagicBox* MagicBox::split(){ // 3: return pointer of new case
    MagicBox *splitout = new MagicBox;
    for (int i=size/2 ; i<size ; i++) splitout->add(bookbox->books[i]);
    size /= 2;
    return splitout;
}

void MagicBox::append(MagicBox *added){// 4: D append to C and damage D
    if (added == nullptr) return;
    for (int i=0 ; i<added->size ; i++) add(added->bookbox->books[i]);
    delete added;
    return;
}