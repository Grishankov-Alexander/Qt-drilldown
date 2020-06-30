#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets>
#include <QtSql>

class ImageItem;
class InformationWindow;

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(const QString &items, const QString &images, QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateImage(int id, const QString &fileName);

private:
    void addItems();
    InformationWindow *findWindow(int id) const;
    void showInformation(ImageItem *image);

    QGraphicsScene *scene;
    QList<InformationWindow *> informationWindows;
    QSqlRelationalTableModel *itemTable;
};

#endif // VIEW_H
