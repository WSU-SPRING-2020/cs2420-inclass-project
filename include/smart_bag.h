#ifndef _SMART_BAG_H_
#define _SMART_BAG_H_

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <memory>

template <typename Item>
class SmartBag
{
private:
  int sz;
  int capacity;
  std::unique_ptr<Item[]> items;

public:
  SmartBag() : sz(0), capacity(4), items(std::make_unique<Item[]>(4)) {}
  SmartBag(int c) : sz(0), capacity(c), items(std::make_unique<Item[]>(c)) {}
  SmartBag(const SmartBag<Item> &b) : sz(b.sz), capacity(b.capacity),
                                      items(std::make_unique<Item[]>(b.capacity))
  {
    for (int i = 0; i < sz; i++)
    {
      items[i] = b.items[i];
    }
  }

  SmartBag<Item> &operator=(const SmartBag<Item> &b)
  {
    sz = b.sz;
    capacity = b.capacity;
    auto newItems = std::make_unique<Item[]>(capacity);
    items = std::move(newItems);
    for (int i = 0; i < sz; i++)
    {
      items[i] = b.items[i];
    }

    return *this;
  }

  SmartBag(std::initializer_list<Item> lst) : sz(0), capacity(lst.size()),
                                              items(std::make_unique<Item[]>(lst.size()))
  {
    for (Item i : lst)
    {
      items[sz++] = i;
    }
  }
  
  SmartBag<Item> &add(Item i)
  {
    if (sz == capacity)
    {
      auto newItems = std::make_unique<Item[]>(2 * capacity);
      for (int j = 0; j < sz; j++)
      {
        newItems[j] = items[j];
      }
      capacity = 2 * capacity;
      items = std::move(newItems);
    }

    items[sz++] = i;

    return *this;
  }

  SmartBag<Item> &removeLast()
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

  friend std::ostream &operator<<(std::ostream &out, SmartBag<Item> &bag)
  {
    for (int i = 0; i < bag.sz; i++)
    {
      out << bag.items[i] << " ";
    }

    return out;
  }

  ~SmartBag() {}
};

#endif