#include "class.h"
void MagicBox::add(string name)
{
    if (size == capacity)
    {
        Box *tmp = new Box(capacity * 2);
        for (int i = 0; i < size; i++)
        {
            tmp->books[i] = bookbox->books[i];
        }
        delete bookbox;
        bookbox = tmp;
        capacity *= 2;
    }
    bookbox->books[size++] = name;
}
void MagicBox::remove()
{
    if (size == 0)
    {
        return;
    }
    bookbox->books[--size] = "";
}
void MagicBox::resize(int newsize)
{
    if (newsize <= capacity)
    {
        while (newsize < size)
        {
            remove();
        }
    }
    else
    {
        Box *tmp = new Box(newsize);
        for (int i = 0; i < size; i++)
        {
            tmp->books[i] = bookbox->books[i];
        }
        delete bookbox;
        bookbox = tmp;
        capacity = newsize;
    }
}
MagicBox* MagicBox::split()
{
    MagicBox *B = new MagicBox();
    int i = 0;
    for (int i = size / 2; i < size; i++)
    {
        B->add(bookbox->books[i]);
        bookbox->books[i] = "";
    }
    size /= 2;
    return B;
}
void MagicBox::append(MagicBox *added)
{
    if (added == nullptr)
        return;
    for (int i = 0; i < added->size; i++)
    {
        add(added->bookbox->books[i]);
    }
    delete added;
}