#include <iostream>
namespace topit
{
  struct p_t
  {
    int x, y;
  };

  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);

  struct f_t
  {
    p_t aa, bb;
  };
  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0; 
    virtual ~IDraw();
  };

  struct Dot: IDraw
  {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t d;
  };
  struct VertLine: IDraw
  {
    VertLine(int x, int y1, int y2);
    explicit VertLine(p_t aa, p_t bb);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a, b;
  };
  size_t getpoints(const IDraw& d, p_t** pts, size_t s);
  f_t frame(const p_t* pts, size_t s);
  char* canvas(f_t fr, char fill);
  void paint(char* cnv, f_t fr, p_t pts, char fill);
  void flush(std::ostream& os, const char* cnv, f_t fr);
}

int main()
{
  int err = 0;
  using topit::IDraw;
  using topit::f_t;
  using topit::p_t;
  using topit::Dot;
  IDraw* shps[3] = {};
  p_t* pts = nullptr;
  size_t s = 0;
  for (size_t i = 0; i < 3; ++i) {
    s += topit::getpoints(*(shps[0]), &pts, s);
  }
  f_t fr = topit::frame(pts, s);
  char* cnv = topit::canvas(fr, '.');
  for (size_t i = 0; i < s; ++i) {
    topit::paint(cnv, fr, pts[i], '#');
  }
  topit::flush(std::cout, cnv, fr);
  try {
  shps[0] = new Dot(0, 0);
  shps[1] = new Dot(5, 7);
  shps[2] = new Dot(-5, -2);
  } catch (...) {
    err = 2;
    std::cerr << "Bad Drawing\n";
  }
  delete[] pts;
  delete[] cnv;
  delete shps[0];
  delete shps[1];
  delete shps[2];
  return err;
}

topit::Dot::Dot(int x, int y):
  IDraw(),
  d{x, y}
{}

topit::Dot::Dot(p_t dd):
  IDraw(),
  d{dd}
{}

bool topit::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool topit::operator!=(p_t a, p_t b)
{
  return !(a == b);
}

topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::p_t topit::Dot::next(p_t prev) const 
{
  if (prev != begin()) {
    throw std::logic_error("bad impl");
  }
  return d;
}
