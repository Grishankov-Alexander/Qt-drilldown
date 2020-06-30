#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

#include <QtWidgets>
#include <QtSql>

class InformationWindow : public QDialog
{
    Q_OBJECT

public:
    InformationWindow(int id, QSqlRelationalTableModel *items,
                      QWidget *parent = nullptr);
    int id() const;

signals:
    void imageChanged(int id, const QString &fileName);

private slots:
    void revert();
    void submit();
    void enableButtons(bool enable = true);

private:
    void createButtons();

    int itemId;
    QString displayedImage;
    QComboBox *imageFileEditor = nullptr;
    QLabel *itemText = nullptr;
    QTextEdit *descriptionEditor = nullptr;
    QPushButton *closeButton = nullptr, *submitButton = nullptr,
    *revertButton = nullptr;
    QDialogButtonBox *buttonBox = nullptr;
    QDataWidgetMapper *mapper = nullptr;
};

#endif // INFORMATIONWINDOW_H
