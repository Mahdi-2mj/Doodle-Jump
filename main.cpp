#include <QtWidgets>
#include <QTimer>
#include "doodler.h"
#include "platform.h"
#include "random.h"
#include <QApplication>
#include <QStringConverter>
#include <QTime>
#include <QSplashScreen>
#include "doodleview.h"

int main(int argc, char* argv[]) {
    QApplication  app(argc, argv);
    QPixmap pix(":/image/scr.jpg");
    QSplashScreen *splash = new QSplashScreen;
    splash->setGeometry(0,0,800,1000);
    splash->setPixmap(pix);
    splash->show();
    DoodleView view;
    view.show();
    splash->finish(&view);
    return app.exec();
}
