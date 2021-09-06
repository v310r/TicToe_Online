#include "TicToe.h"

#include <utility>

#include <QMouseEvent>
#include <QPushButton>
#include <QMessageBox>

TicToe::TicToe(QWidget* parent):QWidget(parent),msgBox(this)
{

    QPushButton* gameReset = new QPushButton("Reset game",this);
    gameReset->setGeometry(1000, 100, 100, 50);
    QObject::connect(gameReset,&QPushButton::clicked,this,&TicToe::resetGame);


    usedCells.resize(9,false);
    shapes.resize(10);
    winnerIndices.resize(3);
//    shapes[2] = std::make_unique<Circle>(cellMap[2].first + 145,cellMap[2].second + 145,140,140);
//    shapes[4] = std::make_unique<Circle>(cellMap[4].first + 145,cellMap[4].second + 145,140,140);
//    usedCells[2] = true;
//    usedCells[4] = true;

    connect(this,&TicToe::clicked,this,&TicToe::defineCell);

}

bool TicToe::wonConditionMet(int crossCounter,int circleCounter) const{
    return ((crossCounter == 3) || (circleCounter ==3));
}


QString TicToe::getResult(int crossCounter){
    int scalingStartX,scalingStartY,scalingEndX,scalingEndY;

    if(winnerLinePosition == HORIZONTAL)         { scalingStartX = 0;scalingStartY = 145;scalingEndX = 290;scalingEndY = 145; }
    else if(winnerLinePosition == VERTICAL)      { scalingStartX = 145;scalingStartY = 0;scalingEndX = 145;scalingEndY = 290; }
    else if(winnerLinePosition == MAIN_DIAGONAL) { scalingStartX = 0;scalingStartY = 0;scalingEndX = 290;scalingEndY = 290;   }
    else if(winnerLinePosition == DIAGONAL)      { scalingStartX = 290;scalingStartY = 0;scalingEndX = 0;scalingEndY = 290;   }

    shapes[winnerLineIndex] = std::make_unique<WinnerLine>(cellMap[winnerIndices[0]].first + scalingStartX,cellMap[winnerIndices[0]].second + scalingStartY,
                                                            cellMap[winnerIndices[2]].first + scalingEndX,cellMap[winnerIndices[2]].second +  scalingEndY);
    return (crossCounter == 3)?"CrossWon":"CircleWon";
}

bool TicToe::pseudoMatrixHandled(int outerIndexStride,int innerIndexStride,int& crossCounter,int& circleCounter,int outerIterations,int startIndex){
    for(int beginningIndex = startIndex,iterationIndex = 0;iterationIndex < outerIterations;beginningIndex+=outerIndexStride,++iterationIndex){
        crossCounter = 0,circleCounter = 0;
        for(int currentIndex = beginningIndex,logicIndex = 0; logicIndex < 3;currentIndex += innerIndexStride,++logicIndex){
            if(!usedCells[currentIndex]) break;

            winnerIndices[logicIndex] = currentIndex;

            if(shapes[currentIndex]->getShape() == "Cross"){
                ++crossCounter;
            }
            else{
                ++circleCounter;
            }

        }
        if(wonConditionMet(crossCounter,circleCounter)) return true;

    }
    return false;

}

// 3,1,cross,circle      1,3,cross,circle                 0,4,cross,circle,1,0         2,2,cross,circle,1,0

QString TicToe::showWinner(){
    int crossCounter,circleCounter;
    if(pseudoMatrixHandled(3,1,crossCounter,circleCounter))      { winnerLinePosition = HORIZONTAL;    return getResult(crossCounter); }
    if(pseudoMatrixHandled(1,3,crossCounter,circleCounter))      { winnerLinePosition = VERTICAL;      return getResult(crossCounter); }
    if(pseudoMatrixHandled(0,4,crossCounter,circleCounter,1,0))  { winnerLinePosition = MAIN_DIAGONAL; return getResult(crossCounter); }
    if(pseudoMatrixHandled(2,2,crossCounter,circleCounter,1,2))  { winnerLinePosition = DIAGONAL;      return getResult(crossCounter); }


    return "";
}

void TicToe::resetGame(bool checked){
    for(size_t i = 0;i<usedCells.size();++i){
        usedCells[i] = false;
        shapes[i] = nullptr;
    }
    connect(this,&TicToe::clicked,this,&TicToe::defineCell);
    winnerLabel = "";
    shapes[winnerLineIndex] = nullptr;
    turn = PLAYER_ONE;
    repaint();
}

void TicToe::paintEvent(QPaintEvent* event) {

    Q_UNUSED(event);
    QPainter qp(this);

    drawField(qp);
    for(size_t index = 0;index < usedCells.size();++index){
        if(usedCells[index])
            shapes[index]->drawShape(qp);
    }
    if(!winnerLabel.isEmpty()) {
        shapes[winnerLineIndex]->drawShape(qp);
    }


}

void TicToe::mousePressEvent(QMouseEvent *event){
    if( (event->button() == Qt::LeftButton) && (turn == PLAYER_ONE) )           { mark = CROSS;    emit clicked(event->x(),event->y()); }
    else if( (event->button() == Qt::RightButton) && (turn == PLAYER_TWO) )     { mark = CIRCLE;   emit clicked(event->x(),event->y()); }


}

void TicToe::drawField(QPainter& qp){

    qp.drawLine(0,0,900,0);
    qp.drawLine(900,0,900,900);
    qp.drawLine(900,900,0,900);
    qp.drawLine(0,900,0,0);

    qp.drawLine(300,0,300,900);
    qp.drawLine(600,0,600,900);
    qp.drawLine(0,300,900,300);
    qp.drawLine(0,600,900,600);
}

void TicToe::fillShapeSequence(){
    if(mark == CROSS){
        shapes[cellIndex] = std::make_unique<Cross>(cellMap[cellIndex].first + 5,cellMap[cellIndex].second + 5,cellMap[cellIndex].first + 285,cellMap[cellIndex].second + 285,
                                                 cellMap[cellIndex].first + 285,cellMap[cellIndex].second + 5,cellMap[cellIndex].first + 5,cellMap[cellIndex].second + 285);

    }
    else if(mark == CIRCLE){
        shapes[cellIndex] = std::make_unique<Circle>(cellMap[cellIndex].first + 145,cellMap[cellIndex].second + 145,140,140);
    }

}

Queue TicToe::nextPlayer()const { return (turn == PLAYER_ONE)? PLAYER_TWO:PLAYER_ONE; }

void TicToe::announceGameRusults(const QString& message){
    disconnect(this,&TicToe::clicked,this,&TicToe::defineCell);
    msgBox.setText(message);
    msgBox.show();
}

bool TicToe::drawConditionMet()const{
    for(const auto&& cell: usedCells)
        if(!cell) return false;
    return true;
}

void TicToe::defineCell(int x, int y){
    for(int currentCellIndex = 0;currentCellIndex <9;++currentCellIndex){
        if( (((cellMap[currentCellIndex].first + 290 - x) > 0 ) && ((cellMap[currentCellIndex].second + 290 - y) > 0))           // back index edge
                && ((cellMap[currentCellIndex].first + 290 - x) < 290 ) && ((cellMap[currentCellIndex].second + 290 - y) < 290)  // front index edge
                && !usedCells[currentCellIndex] ) //check repeated elements
        {

            cellIndex = currentCellIndex;
            fillShapeSequence();
            usedCells[cellIndex] = true;
            turn = nextPlayer();
            break;
        }
    }
    winnerLabel = showWinner();

    repaint();

    if(!winnerLabel.isEmpty())  announceGameRusults(winnerLabel);

    else if(drawConditionMet() && winnerLabel.isEmpty()) announceGameRusults("It's a draw !!!");
}


