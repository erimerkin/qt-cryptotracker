#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>

#include <QTimer>
#include <QVector>
#include <QStringList>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "fileops.h"
#include "coin.h"

/**
 * @brief MyTableWidget is a subclass of QTableWidget, with a timer and network access manager to handle coins and requests
 */
class MyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    MyTableWidget();
    QNetworkAccessManager *manager;
    QTimer *timer;
    FileOps *ioTool;

    QVector<Coin*> currentCoins;
    bool isFirstRun; //bool to check if it is inputs first insert

    /**
     * @brief Updates the table with current coins' prices and names
     */
    void updateTable();

    /**
     * @brief Sets table's header names, size and number of rows
     * @param rows: number of rows
     */
    void setTable(int rows);

signals:
    /**
     * @brief SIGNAL to show that table content is updated
     */
    void updated();

public slots:
    /**
     * @brief Parses the reply of server to HTTPS request sent
     * @param reply: Network reply
     */
    void replyFinished(QNetworkReply *reply);

    /**
     * @brief Refreshes price data of coins, sends a server request
     */
    void refresh();

    /**
     * @brief Send request to server to get data
     *
     * This function reads id of coins inputted to file, and sends request to server
     * to get their prices in USD, EUR, GBP
     */
    void getData();

    /**
     * @brief Resets the input, gets new coins and their data
     *
     * This function resets the current input and reads from new input/inputfile, setting new coins.
     * Then the new coins are classified and price data is gathered, thus updating the table
     */
    void resetInput();



};

#endif // MYTABLEWIDGET_H
