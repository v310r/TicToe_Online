#ifndef SHAPES_H
#define SHAPES_H

#include <QPainter>

class Shape{
public:
    virtual void drawShape(QPainter& qp) const = 0;
    virtual std::string getShape() const = 0;

    virtual ~Shape(){};
};

struct CrossLayout{
  int beginX1,beginY1,endX1,endY1,  // line 1
      beginX2,beginY2,endX2,endY2;  // line 2
};


class Cross:public Shape
{
private:
    CrossLayout layout;
public:
    ~Cross(){};
    Cross(int beginX1,int beginY1,int endX1,int endY1,
          int beginX2,int beginY2,int endX2,int endY2);

    void drawShape(QPainter& qp)const override ;
    std::string getShape() const override;
};

struct CircleLayout{
    int centerX,centerY,radiusX,radiusY;
};

class Circle:public Shape
{
private:
    CircleLayout layout;
public:
    ~Circle(){};
    Circle(int centerX,int centerY,int radiusX,int radiusY);
    void drawShape(QPainter& qp)const override;
    std::string getShape() const override;
};

struct WinnerLineLayout{
    int beginX,beginY,endX,endY;
};

class WinnerLine: public Shape
{
private:
    WinnerLineLayout layout;
public:
    ~WinnerLine(){};
    WinnerLine(int beginX,int beginY,int endX,int endY);
    void drawShape(QPainter& qp) const override;
    std::string getShape() const override;
};

#endif // SHAPES_H
