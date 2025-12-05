#include <iostream>

struct p_t
{
  int x, y;
};

struct IDraw
{
  virtual p_t begin() const = 0;
  virtual p_t next(p_t) const = 0; 
  virtual ~IDraw();
};

int main()
{

}