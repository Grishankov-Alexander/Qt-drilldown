#include "imageitem.h"

ImageItem::ImageItem(int id, const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    recordId = id;
    setAcceptHoverEvents(true);
    timeLine.setDuration(150);
    timeLine.setFrameRange(0, 150);
    connect(&timeLine, &QTimeLine::frameChanged, this, &ImageItem::setFrame);
    connect(&timeLine, &QTimeLine::finished, this, &ImageItem::updateItemPosition);
    adjust();
}

void ImageItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    timeLine.setDirection(QTimeLine::Forward);
    if (z != 1.0) {
        z = 1.0;
        updateItemPosition();
    }
    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ImageItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    timeLine.setDirection(QTimeLine::Backward);
    if (z != 0.0)
        z = 0.0;
    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ImageItem::setFrame(int frame)
{
    adjust();
    QPointF center = boundingRect().center();
    setTransform(QTransform::fromTranslate(center.x(), center.y()), true);
    setTransform(QTransform::fromScale(1 + frame / 330.0, 1 + frame / 330.0), true);
    setTransform(QTransform::fromTranslate(-center.x(), -center.y()), true);
}

void ImageItem::adjust()
{
    QMatrix matrix;
    matrix.scale(120 / boundingRect().width(), 120 / boundingRect().height());
    setMatrix(matrix);
}

int ImageItem::id() const { return recordId; }

void ImageItem::updateItemPosition() { setZValue(z); }
