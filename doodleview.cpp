#include "doodleview.h"
#include "doodler.h"
#include "platform.h"
#include "random.h"

#include <QIcon>
#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QTimer>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QLabel>
#include <QFileInfo>

DoodleView::DoodleView(QWidget *parent) :
    QGraphicsView(parent)
{
    init_view();
}

void DoodleView::init_view() {
    setWindowTitle("Doodle Jump");
    setWindowIcon(QIcon(":/image/doo.ico"));
    resize(360,640);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 360, 640);
    scene->setBackgroundBrush(bg);
    setScene(scene);

    game_score = new QGraphicsTextItem();
    scene->addItem(game_score);
    game_score->setFont(QFont("Times", 20, QFont::Bold));
    game_score->setPos(10, 3);
    game_score->hide();


    QWidget *shade = new QWidget;
    shade->setAutoFillBackground(true);
    shade->setPalette(QPalette(QColor(0, 0, 0, 50)));
    shade->resize(360, 640);

    shade_widget = scene->addWidget(shade);
    shade_widget->setPos(0, 0);
    shade_widget->setZValue(1);
    shade_widget->hide();


    QWidget *option = new QWidget;
    option->resize(200, 300);
    QPalette optionbg;
    QPixmap option_bg = QPixmap(":/image/option.jpg");
    optionbg.setBrush(QPalette::Window,QBrush(option_bg));
    option->setPalette(optionbg);
    option->setAutoFillBackground(true);

    QPushButton *option_close = new QPushButton(tr("Close"),option);
    option_close->setGeometry(80,260,40,20);
    connect(option_close, SIGNAL(clicked()), option, SLOT(hide()));

    QPushButton *mode1 = new QPushButton(tr("Chrismas"),option);
    mode1->setGeometry(65,220,70,20);
    connect(mode1, SIGNAL(clicked()), this, SLOT(setMode1()));

    QPushButton *mode2 = new QPushButton(tr("Jungle"),option);
    mode2->setGeometry(140,220,50,20);
    connect(mode2, SIGNAL(clicked()), this, SLOT(setMode2()));

    QPushButton *mode3 = new QPushButton(tr("Space"),option);
    mode3->setGeometry(10,220,50,20);
    connect(mode3, SIGNAL(clicked()), this, SLOT(setMode3()));

    QGraphicsWidget *option_widget = scene->addWidget(option);
    option_widget->setPos(80, 150);
    option_widget->setZValue(3);
    option_widget->hide();


    QWidget *help = new QWidget;
    QPalette helpbg;
    QPixmap help_bg = QPixmap(":/image/help.jpg");
    helpbg.setBrush(QPalette::Window,QBrush(help_bg));
    help->setPalette(helpbg);
    help->setAutoFillBackground(true);
    help->resize(200, 300);

    QPushButton *help_close = new QPushButton(tr("Close"), help);
    help_close->setGeometry(75,260,50,25);
    connect(help_close, SIGNAL(clicked()), help, SLOT(hide()));

    QGraphicsWidget *help_widget = scene->addWidget(help);
    help_widget->setPos(80, 150);
    help_widget->setZValue(3);
    help_widget->hide();

    welcome_text = new QGraphicsTextItem();
    scene->addItem(welcome_text);
    welcome_text->setHtml("<font color=black>Doodle Jump</font>");
    welcome_text->setFont(QFont("Times", 40, QFont::Bold));
    welcome_text->setPos(60, 100);
    welcome_text->setZValue(2);

    pause_text = new QGraphicsTextItem();
    scene->addItem(pause_text);
    pause_text->setHtml("<font color=black>Paused</font>");
    pause_text->setFont(QFont("Times", 40, QFont::Bold));
    pause_text->setPos(120, 100);
    pause_text->setZValue(2);
    pause_text->hide();

    game_over_text = new QGraphicsTextItem();
    scene->addItem(game_over_text);
    game_over_text->setHtml("<font color=black>Life Sucks！</font>");
    game_over_text->setFont(QFont("Times", 40, QFont::Bold));
    game_over_text->setPos(80, 100);
    game_over_text->setZValue(2);
    game_over_text->hide();


    QPushButton *button1 = new QPushButton("Start");
    connect(button1, SIGNAL(clicked()), this, SLOT(start_game()));
    start_button = scene->addWidget(button1);
    start_button->setPos(150, 200);
    start_button->setZValue(2);

    QPushButton *button2 = new QPushButton("Option");
    connect(button2, SIGNAL(clicked()), option, SLOT(show()));
    option_button = scene->addWidget(button2);
    option_button->setPos(145, 300);
    option_button->setZValue(2);


    QPushButton *button3 = new QPushButton("Help");
    connect(button3, SIGNAL(clicked()), help, SLOT(show()));
    help_button = scene->addWidget(button3);
    help_button->setPos(150, 400);
    help_button->setZValue(2);

    QPushButton *button4 = new QPushButton("Quit");
    connect(button4, SIGNAL(clicked()), qApp, SLOT(quit()));
    exit_button = scene->addWidget(button4);
    exit_button->setPos(150, 500);
    exit_button->setZValue(2);

    QPushButton *button5 = new QPushButton("Restart");
    connect(button5, SIGNAL(clicked()), this, SLOT(restart_game()));
    restart_button = scene->addWidget(button5);
    restart_button->setPos(130, 0);
    restart_button->setZValue(2);

    QPushButton *button6 = new QPushButton("Pause");
    connect(button6, SIGNAL(clicked()), this, SLOT(pause_game()));
    pause_button = scene->addWidget(button6);
    pause_button->setPos(280, 0);
    pause_button->setZValue(2);

    QPushButton *button7 = new QPushButton("Return");
    connect(button7, SIGNAL(clicked()), this, SLOT(return_game()));
    return_button = scene->addWidget(button7);
    return_button->setPos(145, 200);
    return_button->setZValue(2);

    QPushButton *button8 = new QPushButton("Menu");
    connect(button8, SIGNAL(clicked()), this, SLOT(back_to_menu()));
    backmenu_button = scene->addWidget(button8);
    backmenu_button->setPos(210, 0);

    restart_button->hide();
    pause_button->hide();
    backmenu_button->hide();
    return_button->hide();
}

void DoodleView::start_game() {
    welcome_text->hide();
    start_button->hide();
    option_button->hide();
    help_button->hide();
    exit_button->hide();
    init_game();
}

void DoodleView::init_game() {
    doodoo = new Doodler(mode);
    doodoo->mode = mode;
    scene()->setBackgroundBrush(bg);
    scene()->addItem(doodoo);
    connect(doodoo, SIGNAL(view_down(double)), doodoo, SLOT(fall(double)));
    doodoo->startTimer(25);
    doodoo->setFocus();
    doodoo->show();

    for (int i=0; i<9; i++){
        int a = randomInteger(0,290);
        Platform *platform = new Platform(a,initbottom);
        int b = randomInteger(11,15);
        initbottom -= b*5;
        connect(doodoo, SIGNAL(view_down(double)), platform, SLOT(fall(double)));
        scene()->addItem(platform);
        platform->show();
    }
    initbottom=625;

    game_score->setHtml("<font color = red >Score: 0</font>");
    restart_button->show();
    pause_button->show();
    backmenu_button->show();
    game_score->show();

    connect(doodoo, SIGNAL(view_down(double)), this, SLOT(addNew()));
    connect(doodoo,SIGNAL(ggwp()),this,SLOT(game_over()));

    timer2 = new QTimer;
    QObject::connect(timer2,SIGNAL(timeout()),this,SLOT(update_score()));
    timer2->start(5);
}

void DoodleView::update_score() {
    game_score->setHtml(tr("<font color = red>%1</font>").arg(doodoo->score));
    game_score->show();
}


void DoodleView::game_over() {
    doodoo->stop_timer();
    pause_button->hide();
    backmenu_button->hide();
    game_over_text->show();
    restart_button->setPos(120, 200);
    exit_button->show();
    shade_widget->show();
}

void DoodleView::pause_game()
{
    timer2->stop();
    doodoo->stop_timer();
    restart_button->hide();
    pause_button->hide();
    backmenu_button->hide();
    shade_widget->show();
    pause_text->show();
    return_button->show();
}

void DoodleView::return_game()
{
    timer2->start(5);
    doodoo->startTimer(25);
    doodoo->setFocus();
    return_button->hide();
    pause_text->hide();
    shade_widget->hide();
    restart_button->show();
    pause_button->show();
    backmenu_button->show();
}

void DoodleView::restart_game()
{
    shade_widget->hide();
    game_over_text->hide();
    exit_button->hide();
    restart_button->setPos(130, 0);
    doodoo->stop_timer();
    QList<QGraphicsItem *> itemList = scene()->items(-200,25,600,800,Qt::ContainsItemShape,Qt::AscendingOrder);
    foreach (QGraphicsItem *item, itemList) {
        scene()->removeItem(item);
    }
    init_game();
}

void DoodleView::back_to_menu()
{
    game_over_text->hide();
    doodoo->stop_timer();
    timer2->stop();
    game_score->hide();
    QList<QGraphicsItem *> itemList = scene()->items(-200,25,600,800,Qt::ContainsItemShape,Qt::AscendingOrder);
    foreach (QGraphicsItem *item, itemList) {
        scene()->removeItem(item);
    }
    init_view();
}



void DoodleView::setMode1(){
    mode=1;
    bg=QPixmap(":/image/chrisbg.jpg");
}
void DoodleView::setMode2(){
    mode=2;
    bg=QPixmap(":/image/junglebg.jpg");
}
void DoodleView::setMode3(){
    mode=3;
    bg=QPixmap(":/image/spacebg.jpg");
}

void DoodleView::addNew() {
    for (int i =0;i<5;i++){
        int a = randomInteger(0,290);
        int b = randomInteger(14,17);
        Platform *platform = new Platform(a,inittop);
        inittop += 5*b;
        connect(doodoo, SIGNAL(view_down(double)), platform, SLOT(fall(double)));
        scene()->addItem(platform);
        platform->show();
    }
    inittop=50;
}




