#include "mygraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <map>

class RectsKey {
public:
  int x;
  int y;
  RectsKey(int xx, int yy)
    :x(xx)
    ,y(yy) {}

  bool operator < (const RectsKey& other) {
    if(x != other.x) return x < other.x;
    return y < other.y;
  }
};

std::map<RectsKey, QGraphicsRectItem*> rects;

MyGraphicsScene::MyGraphicsScene(QObject* parent)
  : QGraphicsScene(parent)
{
  int mapWidth = 10;
  int mapHeight = 10;
  unsigned char pMap[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
    0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 1, 1, 1, 1, 0, 0,
    1, 1, 1, 0, 1, 1, 1, 0, 0, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  };

  for(int i = 0; i < 10; ++i) {
    for(int j = 0; j < 10; ++j) {
      QGraphicsRectItem* rect = addRect(QRectF(j*20,i*20,20,20), QPen(), QBrush(Qt::red));
      RectsKey k(j, i);
      RectsKey kk(j, i);
      k<kk;
      rects[k] = rect;
    }
  }

}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

  qDebug() << "mousePressEvent";
}

