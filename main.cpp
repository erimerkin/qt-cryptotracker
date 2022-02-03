#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "mytablewidget.h"
#include "fileops.h"
#include "updatelabel.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Creates widgets and layouts
    QWidget *window = new QWidget;
    QGridLayout *layout = new QGridLayout(window);
    QPushButton *button = new QPushButton("Reset Input");
    MyTableWidget *table = new MyTableWidget();
    UpdateLabel *lastUpdated = new UpdateLabel();

    //Connects signals with slots
    QWidget::connect(button, SIGNAL(clicked()), table, SLOT(resetInput()));
    QWidget::connect(table, SIGNAL(updated()), lastUpdated, SLOT(updateTime()));

    //Sets button size
    button->setFixedSize(150,30);

    //Adds widgets to layout
    layout->addWidget(lastUpdated, 0, 0);
    layout->addWidget(button, 0, 1);
    layout->addWidget(table, 1, 0, 1, 2);

    //Sets window size
    window->resize(table->width(), 500);
    window->show();

    return app.exec();
}


