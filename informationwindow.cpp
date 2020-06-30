#include "informationwindow.h"

InformationWindow::InformationWindow(int id, QSqlRelationalTableModel *items,
                                     QWidget *parent)
    : QDialog(parent)
{
    QLabel *itemLabel = new QLabel(tr("Item: "));
    QLabel *descriptionLabel = new QLabel(tr("Description: "));
    QLabel *imageFileLabel = new QLabel(tr("Image file: "));
    createButtons();
    itemText = new QLabel;
    descriptionEditor = new QTextEdit;
    imageFileEditor = new QComboBox;
    imageFileEditor->setModel(items->relationModel(1));
    imageFileEditor->setModelColumn(items->relationModel(1)->fieldIndex("file"));
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(items);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate(mapper));
    mapper->addMapping(imageFileEditor, 1);
    mapper->addMapping(itemText, 2, "text");
    mapper->addMapping(descriptionEditor, 3);
    mapper->setCurrentIndex(id);
    connect(descriptionEditor, &QTextEdit::textChanged, [=]() {
        enableButtons();
    });
    connect(imageFileEditor, QOverload<int>::of(&QComboBox::currentIndexChanged), [=]() {
        enableButtons();
    });
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(itemLabel, itemText);
    formLayout->addRow(imageFileLabel, imageFileEditor);
    formLayout->addRow(descriptionLabel, descriptionEditor);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);
    setLayout(layout);
    itemId = id;
    displayedImage = imageFileEditor->currentText();
    setWindowFlags(Qt::Window);
    enableButtons(false);
    setWindowTitle(itemText->text());
}

int InformationWindow::id() const
{
     return itemId;
}

void InformationWindow::revert()
{
    mapper->revert();
    enableButtons(false);
}

void InformationWindow::submit()
{
    QString newImage(imageFileEditor->currentText());
    if (displayedImage != newImage) {
        displayedImage = newImage;
        emit imageChanged(itemId, newImage);
    }
    mapper->submit();
    mapper->setCurrentIndex(itemId);
    enableButtons(false);
}

void InformationWindow::createButtons()
{
    closeButton = new QPushButton(tr("&Close"));
    revertButton = new QPushButton(tr("&Revert"));
    submitButton = new QPushButton(tr("&Submit"));

    closeButton->setDefault(true);

    connect(closeButton, &QPushButton::clicked, this, &InformationWindow::close);
    connect(revertButton, &QPushButton::clicked, this, &InformationWindow::revert);
    connect(submitButton, &QPushButton::clicked, this, &InformationWindow::submit);
//! [8]

//! [9]
    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(submitButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);
}

void InformationWindow::enableButtons(bool enable)
{
    revertButton->setEnabled(enable);
    submitButton->setEnabled(enable);
}
