#include "updatelabel.h"

UpdateLabel::UpdateLabel(QLabel *parent) : QLabel(parent)
{
    //Initializes clock to get time later
    clock = new QDateTime;
}

void UpdateLabel::updateTime()
{
    //Gets operation time and stores in a string to set text of label
    QString data = "Last updated at " + clock->currentDateTime().toString("hh:mm:ss");
    this->setText(data);
}
