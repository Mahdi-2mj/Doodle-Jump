#ifndef DOODLEVIEW_H
#define DOODLEVIEW_H
#include <QGraphicsView>
#include <QTimer>
#include "doodler.h"

class DoodleView : public QGraphicsView
{
Q_OBJECT
public:
    explicit DoodleView(QWidget *parent = 0);

public slots:
    void start_game();
    void game_over();
    void restart_game();
    void back_to_menu();
    void pause_game();
    void return_game();
    void addNew();
    void update_score();    
    void setMode1();
    void setMode2();
    void setMode3();

private:
    Doodler *doodoo;
    QPixmap bg=QPixmap(":/image/bg.jpg");
    int mode=0;
    int initbottom=625;
    int inittop = 50;
    bool over=false;

    QGraphicsTextItem *game_score;
    QGraphicsTextItem *welcome_text;
    QGraphicsTextItem *pause_text;
    QGraphicsTextItem *game_over_text;

    QGraphicsWidget *start_button;
    QGraphicsWidget *option_button;
    QGraphicsWidget *help_button;
    QGraphicsWidget *exit_button;
    QGraphicsWidget *restart_button;
    QGraphicsWidget *pause_button;   
    QGraphicsWidget *return_button;    
    QGraphicsWidget *backmenu_button;

    QGraphicsWidget *shade_widget;


    void init_view();
    void init_game();

private:
    QTimer *timer2;


signals:




};


#endif // DOODLEVIEW_H
