#ifndef ZONEDESSIN_H
#define ZONEDESSIN_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <list>
#include <QStateMachine>
#include <QEvent>
#include "Transitions.h"
#include <QFinalState>
#include <QDebug>

//enumeration represents the differents options
enum Shape {LINE, RECTANGLE, ELLIPSE, POLYLINE, SELECT, MOVE};

class ZoneDessin: public QWidget
{
    Q_OBJECT

public:
    explicit ZoneDessin(QWidget *parent = 0);
    ~ZoneDessin();

    void paintEvent(QPaintEvent * e);

    //set attributes of pen
    void setPenColor(QColor c) {curPen.setColor(c); updateSelect(); update();}
    void setPenWidth(int w) {curPen.setWidth(w); updateSelect(); update();}

    //initiate the shape
    void setShape(int shape);

    //functions for erase
    void cancelLast();
    void cancelAll();

    //serialization and deserealization
    void readDisplayList(QDataStream &in);
    void writeDisplayList(QDataStream *out);

private:
    //curent pen, selection of pen and pen selected
    QPen curPen, selectPen, selectedPen;

    QPoint lastPoint, endPoint; // clic=firstPoint --> clic=endPoint

    QPainterPath curPath, bufPath;
    QPainterPath select; // QPainterPath allows the selection of a path

    QPainter painter; //painter


    struct QPathPen {
        QPainterPath path;
        QPen pen;
        QPathPen(QPainterPath p, QPen pp) : path(p), pen(pp) {}
    };

    //list de QPathPen
    typedef std::list<QPathPen> DisplayList;
    DisplayList displayList;

    //pointers of current selection
    typedef std::list<QPathPen*> Selected;
    Selected selected;

    QStateMachine * addShape; //add the last shape to the list for futere editions
    void addShapeMachine(); //func for initialice the state

public slots:
    /*****************************************************************************
     * slots for creation of shape
     *****************************************************************************/
    // 1->2
    void setLastPoint();

    // 2->2
    void setEndPointLine();
    void setEndPointRect();
    void setEndPointEll();
    void setEndPointPolyLine();
    void setEndPointSelect();
    void setEndPointMove();

    // 2->2 bis
    void addLinePolyLine();

    // 2->1
    void saveLine();
    void saveRect();
    void saveEll();
    void savePolyLine();
    void saveSelect();

    /*****************************************************************************
     * slots for selection
     *****************************************************************************/
    void updateSelect();
    void clearSelect();
};

#endif // ZONEDESSIN_H
