#ifndef TICTOE_H
#define TICTOE_H

#include <QWidget>
#include <QApplication>
#include <vector>
#include <QPair>
#include <QMessageBox>

#include "Shapes.h"

enum Queue {PLAYER_ONE,PLAYER_TWO};
enum Positioning {HORIZONTAL,  VERTICAL, MAIN_DIAGONAL,DIAGONAL};
enum eventMark {CROSS,CIRCLE};

const unsigned int winnerLineIndex = 9;

class TicToe: public QWidget
{
    Q_OBJECT
public:
    TicToe(QWidget* parent = nullptr);

    virtual ~TicToe() {};


protected:
    void drawField(QPainter& qp);


private:
    std::vector<QPair<int,int>> cellMap
    {
        {5,5},  {305,5},   {605,5},
        {5,305},{305,305}, {605,305},
        {5,605},{305,605}, {605,605},
    };

    std::vector<bool>usedCells;

    bool wonConditionMet(int crossCounter,int circleCounter)const ;

    QString getResult(int crossCounter);

    int cellIndex{};

    eventMark mark;
    Positioning winnerLinePosition;
    Queue turn = PLAYER_ONE;

    QString winnerLabel="";

    std::vector<unsigned int> winnerIndices;

    bool drawConditionMet()const;

    std::vector<std::unique_ptr<Shape>> shapes;

    QMessageBox msgBox;

    Queue nextPlayer()const ;

    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent* event) override;

    void announceGameRusults(const QString& message);
    QString showWinner();


    void fillShapeSequence();
    bool pseudoMatrixHandled(int outerIndexStride,int innerIndexStride,int& crossCounter,int& circleCounter,int outerIterations = 3,int startIndex = 0);

signals:
    void clicked( int x, int y );

private slots:

    void resetGame(bool checked = false);
    void defineCell(int x, int y);
};










#endif // TICTOE_H
