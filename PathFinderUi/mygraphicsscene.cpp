#include "mygraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <map>
#include <QKeyEvent>
#include <QVector2D>
#include "../findpath.h"
class RectsKey {
public:
  int x;
  int y;
  RectsKey(int xx, int yy)
    :x(xx)
    ,y(yy) {}

  bool operator < (const RectsKey& other) const {
    if(x != other.x) return x < other.x;
    return y < other.y;
  }
};

std::map<RectsKey, QGraphicsRectItem*> rects;
unsigned char   pMap[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1,
  1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1,
  1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
int mapWidth = 20;
int mapHeight = 20;
int tileWidth = 20;
int tileHeight = 20;

bool startDown = false;
bool endDown = false;

int startX = -1;
int startY = -1;
int endX= -1;
int endY = -1;


MyGraphicsScene::MyGraphicsScene(QObject* parent)
  : QGraphicsScene(parent)
{


  for(int i = 0; i < mapHeight; ++i) {
    for(int j = 0; j < mapWidth; ++j) {
      QGraphicsRectItem* rect;
      if(pMap[i*mapWidth+j] == 0)
        rect = addRect(QRectF(j*tileWidth,i*tileHeight,tileWidth,tileHeight), QPen(), QBrush(Qt::blue));
      if(pMap[i*mapWidth+j] == 1)
        rect = addRect(QRectF(j*tileWidth,i*tileHeight,tileWidth,tileHeight), QPen(), QBrush(Qt::red));
      RectsKey k(j, i);
      rects[k] = rect;

    }
  }

}

void updateMap() {  
  for(int i = 0; i < mapWidth; ++i) {
    for(int j = 0; j < mapHeight; ++j) {
      QGraphicsRectItem* rect = rects[RectsKey(j, i)];
      if(pMap[i*mapWidth+j] == 0)
        rect->setBrush(QBrush(Qt::blue));
      if(pMap[i*mapWidth+j] == 1)
        rect->setBrush(QBrush(Qt::red));

    }
  }

  int pOutBuffer[128];
  int nNumSteps = FindPath(startX, startY, endX, endY, pMap, mapWidth, mapHeight, pOutBuffer, 128);
  for(int i = 0; i < nNumSteps; i++) {
    int y = pOutBuffer[i]/mapWidth;
    int x = pOutBuffer[i] - y*mapWidth;

    QGraphicsRectItem* rect = rects[RectsKey(x, y)];
    rect->setBrush(QBrush(Qt::green));
  }

  if(startX != -1 && startY != -1)
  {
    QGraphicsRectItem* rect = rects[RectsKey(startX, startY)];
    rect->setBrush(QBrush(Qt::green));
  }
  if(endX != -1 && endY != -1)
  {
    QGraphicsRectItem* rect = rects[RectsKey(endX, endY)];
    rect->setBrush(QBrush(Qt::gray));
  }


}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  int x = int(event->scenePos().x()/tileWidth);
  int y = int(event->scenePos().y()/tileHeight);

  if(startDown)
  {
    startX = x;
    startY = y;
  }
  else if(endDown)
  {
    endX = x;
    endY = y;
  }
  else{


    if(pMap[y*mapWidth+x] == 0) {
      pMap[y*mapWidth+x] = 1;
    }
    else if(pMap[y*mapWidth+x] == 1) {
      pMap[y*mapWidth+x] = 0;
    }
  }
  updateMap();
  //qDebug() << int(event->scenePos().x()/20) << " " << int(event->scenePos().y()/20);
}

void MyGraphicsScene::keyPressEvent(QKeyEvent *event) {
  if(event->key() == 65)
    startDown = true;
  if(event->key() == 83)
    endDown = true;
}

void MyGraphicsScene::keyReleaseEvent(QKeyEvent *event){
  if(event->key() == 65)
    startDown = false;
  if(event->key() == 83)
    endDown = false;
}

