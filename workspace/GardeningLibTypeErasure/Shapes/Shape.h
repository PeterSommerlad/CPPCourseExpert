#ifndef SHAPE_H_
#define SHAPE_H_

#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
namespace Gardening {
struct Shape;
unsigned Pegs(Shape const &s);
double Ropes(Shape const &s);
double Seeds(Shape const &s);
void Print(std::ostream &out,Shape const &s);
std::ostream &operator<<(std::ostream &out,Shape const &s);

struct Shape{
  template<typename aShape>
  // deliberately implicit!
  Shape(aShape s): self_{std::make_unique<model<aShape>>(std::move(s))}{}
  Shape(Shape const &other): self_{other.self_->clone()}{}
  Shape(Shape &&) noexcept = default;
  Shape& operator=(Shape const &other) & {
    return *this = Shape(other); // copy-move
  }
  Shape & operator=(Shape &&) & noexcept = default;


  friend unsigned Pegs(Shape const &s) { return s.self_->pegs_(); }
  friend double Ropes(Shape const &s) { return s.self_->ropes_(); }
  friend double Seeds(Shape const &s) { return s.self_->area_()* seedPerSquareMeter; }
  friend
  void Print(std::ostream &out,Shape const &s){
    s.self_->print_(out);
  }
  friend
  std::ostream &operator<<(std::ostream &out,Shape const &s){
    Print(out,s); return out;
  }

private:
  constexpr static double seedPerSquareMeter { 0.1 };

  struct shape_concept{
    virtual ~shape_concept()=default;
    virtual std::unique_ptr<shape_concept> clone() const = 0;
    virtual std::string name() const = 0;
    virtual unsigned pegs_() const = 0;
    virtual double ropes_()const = 0;
    virtual double area_() const = 0;
    virtual void print_(std::ostream &out) const = 0;
  };
  template<typename aShape>
  struct model : shape_concept {
    explicit model(aShape s) : theShape{std::move(s)}{}
    std::unique_ptr<shape_concept> clone() const {
      return std::make_unique<model>(this->theShape);
    }
    std::string name() const {
      return aShape::name; // implies class type, might be bad design decision
    }
    unsigned pegs_() const {
      return pegs(this->theShape);
    }
    double ropes_()const {
      return ropes(this->theShape);
    }
    double area_() const {
      return area(this->theShape);
    }
    void print_(std::ostream &out) const {
      out << aShape::name << " " << this->pegs_() << " " << this->ropes_() << " " << this->area_()*seedPerSquareMeter;
    }
    aShape theShape;
  };
  std::unique_ptr<shape_concept> self_;
};



}

#endif /* SHAPE_H_ */
