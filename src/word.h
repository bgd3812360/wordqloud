#ifndef WORD_H_
#define WORD_H_

#include <QColor>
#include <QFont>
#include <QRegion>
#include <QGraphicsSimpleTextItem>

#include <string>
#include "iareacomparable.h"

class Word : public QGraphicsSimpleTextItem, public IAreaComparable
{
public:
  Word(QString w, float b = 1);
  ~Word();

  virtual QRectF boundingBox() const;
  void cacheCollision(Word *w);
  bool collidesWith(Word *w);
  bool collidesWithCashed();
  bool getPinned();
  float height();
  void prepareCollisionDetection();
  void setPinned(bool p);
  void setFontName(QString fontname);
  void setFontSize(float s);
  void togglePinned();
  void updateCollisionDetection(QPointF delta);
  float width();
  void writeImage();

protected:

private:
    
  void initBitmap();

  QVector<QRect> regionRects;
  QRegion region;
  QImage *bitmap;
  Word *cachedCollision;
  bool pinned;
  bool showBounding;
};

inline QRectF Word::boundingBox() const
{
  QRectF b = ((QGraphicsSimpleTextItem*)this)->boundingRect();
  return ((QGraphicsSimpleTextItem*)this)->mapRectToScene(b);
}

inline bool Word::getPinned() { return pinned; }

inline void Word::setPinned(bool p)
{
  pinned = p;
}

inline void Word::togglePinned()
{
  pinned = !pinned;
}


#endif
