#ifndef _BAG_H_
#define _BAG_H_
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename Item>
class Bag
{
private:
  int sz;
  int capacity;
  Item *items;

public:
  Bag() : sz(0), capacity(4), items(new Item[4]) {}
  Bag(int c) : sz(0), capacity(c), items(new Item[c]) {}
  Bag(const Bag<Item> &b) : sz(b.sz), capacity(b.capacity),
                            items(new Item[b.capacity])
  {
    for (int i = 0; i < sz; i++)
    {
      items[i] = b.items[i];
    }
  }

  Bag<Item> &operator=(const Bag<Item> &b)
  {
    delete[] items;
    sz = b.sz;
    capacity = b.capacity;
    items = new Item[capacity];
    for (int i = 0; i < sz; i++)
    {
      items[i] = b.items[i];
    }

    return *this;
  }

  Bag(std::initializer_list<Item> lst) : sz(0),
                                         capacity(lst.size()),
                                         items(new Item[lst.size()])
  {
    for (Item i : lst)
    {
      items[sz++] = i;
    }
  }

  Bag<Item> &add(Item i)
  {
    if (sz == capacity)
    {
      Item *newItems = new Item[2 * capacity];
      for (int j = 0; j < sz; j++)
      {
        newItems[j] = items[j];
      }
      capacity = 2 * capacity;
      delete[] items;
      items = newItems;
    }

    items[sz++] = i;

    return *this;
  }

  Bag<Item> &removeLast()
  {
    sz--;

    return *this;
  }

  Item *begin() { return items; }
  Item *end() { return items + sz; }

  Item operator[](int i) const
  {
    if (i < 0 || i >= sz)
    {
      throw std::runtime_error("Out of bounds");
    }

    return items[i];
  }

  Item &operator[](int i)
  {
    if (i < 0 || i >= sz)
    {
      throw std::runtime_error("Out of bounds");
    }

    return items[i];
  }

  int getSize() const
  {
    return sz;
  }

  int getCapacity() const
  {
  }

  friend std::ostream &operator<<(std::ostream &out, Bag<Item> &bag)
  {
    for (int i = 0; i < bag.sz; i++)
    {
      out << bag.items[i] << " ";
    }

    return out;
  }

  ~Bag()
  {
    delete[] items;
    items = nullptr;
  }
};

#endif