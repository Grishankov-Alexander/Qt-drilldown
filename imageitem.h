#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QtCore>
#include <QtWidgets/QGraphicsPixmapItem>

class ImageItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ImageItem(int id, const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    void adjust();
    int id() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private slots:
    void setFrame(int frame);
    void updateItemPosition();

private:
    QTimeLine timeLine;
    int recordId;
    double z;
};

#endif // IMAGEITEM_H
