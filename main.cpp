#include "view.h"
#include "connection.h"

#include <QApplication>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(drilldown);
    QApplication app(argc, argv);
    if (!createConnection())
        return EXIT_FAILURE;
    View view("items", "images");
    view.show();
#ifdef QT_KEYPAD_NAVIGATION
    QApplication::setNavigationMode(Qt::NavigationModeCursorAuto);
#endif
    return app.exec();
}
