#ifndef FILEOPS_H
#define FILEOPS_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "coin.h"

/**
 * @brief FileOps class
 */
class FileOps : public QObject
{
    Q_OBJECT
public:
    explicit FileOps(QObject *parent = nullptr);

    QStringList *inputs;
    QNetworkAccessManager *manager;
    QVector<Coin*> coins;

    /**
     * @brief Reads new inputs and classifies the new inputs
     */
    void refreshInput();

    /**
     * @brief Reads file
     *
     * Reads file thats location is read from MYCRYPTOCONVERT environment variable,
     * appends the lines of file to a QStringList to classify them later
     */
    void readFile();

    /**
     * @brief   Gets list of coins
     * @return  A QVector consisting of coins
     */
    QVector<Coin*> getCoins();

signals:

    /**
     * @brief SIGNAL to show that coin classification is finished
     */
    void classified();

public slots:

    /**
     * @brief This function parses the reply from request
     * @param reply: Server reply
     *
     * This function activates when QNetworkAccessManager signals that request has been completed
     */
    void replyFinished(QNetworkReply * reply) ;
};

#endif // FILEOPS_H
