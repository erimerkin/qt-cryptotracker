#ifndef UPDATELABEL_H
#define UPDATELABEL_H

#include <QLabel>
#include <QDateTime>



/**
 * @brief This class is a subclass of QLabel with ability to get and display time
 *
 * Extending QLabel this class has been tuned to get and display time data
 */
class UpdateLabel : public QLabel
{
    Q_OBJECT
public:
    explicit UpdateLabel(QLabel *parent = nullptr);
    QDateTime *clock;

public slots:
    /**
     * @brief Updates time shown in label to current time
     */
    void updateTime();

};

#endif // UPDATELABEL_H
