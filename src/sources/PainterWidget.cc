#include "MotionPlan.h"

PainterWidget::PainterWidget(QGraphicsScene* outscene){
  setScene(outscene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setResizeAnchor(AnchorViewCenter);
}

void PainterWidget::keyPressEvent(QKeyEvent* event){
  switch (event->key()) {
   case Qt::Key_Plus:
       scaleView(qreal(1.2));
       break;
   case Qt::Key_Minus:
       scaleView(1 / qreal(1.2));
       break;
   default:
       QGraphicsView::keyPressEvent(event);
   }
};

void PainterWidget::scaleView(qreal scaleFactor){
  qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
      return;

  scale(scaleFactor, scaleFactor);
};
