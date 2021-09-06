#include "Shapes.h"

Cross::Cross(int beginX1,int beginY1,int endX1,int endY1,
             int beginX2,int beginY2,int endX2,int endY2)
{
    layout.beginX1 = beginX1;
    layout.beginY1 = beginY1;
    layout.endX1 = endX1;
    layout.endY1 = endY1;
    layout.beginX2 = beginX2;
    layout.beginY2 = beginY2;
    layout.endX2 = endX2;
    layout.endY2 = endY2;
}

Circle::Circle(int centerX,int centerY,int radiusX,int radiusY){
    layout.centerX = centerX;
    layout.centerY = centerY;
    layout.radiusX = radiusX;
    layout.radiusY = radiusY;
}

WinnerLine::WinnerLine(int beginX,int beginY,int endX,int endY){
    layout.beginX = beginX;
    layout.beginY = beginY;
    layout.endX = endX;
    layout.endY = endY;

}

void Cross::drawShape(QPainter& qp) const{
    qp.setPen(Qt::red);
    qp.drawLine(layout.beginX1,layout.beginY1,layout.endX1,layout.endY1);
    qp.drawLine(layout.beginX2,layout.beginY2,layout.endX2,layout.endY2);
}

std::string Cross::getShape() const{
    return "Cross";
}

void Circle::drawShape(QPainter& qp) const{
    qp.setPen(Qt::blue);
    qp.drawEllipse(QPoint(layout.centerX,layout.centerY),layout.radiusX,layout.radiusY);
}


std::string Circle::getShape() const{
    return "Circle";
}

void WinnerLine::drawShape(QPainter &qp) const{
    qp.setPen(Qt::green);
    qp.drawLine(layout.beginX,layout.beginY,layout.endX,layout.endY);
}

std::string WinnerLine::getShape() const{
    return "WinnerLine";
}
