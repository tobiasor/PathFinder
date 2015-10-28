#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QDebug>
#include <QObject>

class MyGraphicsScene : public QGraphicsScene
{
public:
  MyGraphicsScene(QObject* parent);

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
};

#endif // MYGRAPHICSSCENE_H
