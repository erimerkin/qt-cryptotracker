#include "mytablewidget.h"


MyTableWidget::MyTableWidget() : QTableWidget()
{
    //Setting up Network manager, I/O operation class, and timer 
    this->manager = new QNetworkAccessManager();
    this->ioTool = new FileOps();
    this->timer = new QTimer();

    //Connects SIGNALs to SLOTs
    connect(this->ioTool, SIGNAL(classified()), this, SLOT(refresh())); //
    connect(this->manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(getData()));

    // Header settings
    this->verticalHeader()->hide();

    //Sets column count
    this->setColumnCount(4);


    // Disable selecting and editing
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setFocusPolicy(Qt::NoFocus);
    this->setSelectionMode(QAbstractItemView::NoSelection);

}


void MyTableWidget::replyFinished(QNetworkReply *reply){

    //Checks if server replies with error message, and parses the reply JSON
    if(reply->error() == QNetworkReply::NoError){
        QByteArray result = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
        QJsonObject jsonObject = jsonResponse.object();

        // Iterates over coins and sets prices for coins
        for (auto item : this->currentCoins) {
            QJsonObject coinObject = jsonObject[item->getID()].toObject();
            item->setPrices(coinObject["usd"].toDouble(), coinObject["eur"].toDouble(), coinObject["gbp"].toDouble());
        }

        //Updates the table with read coins
        updateTable();

    }
    else
    {
        qDebug() << "ERROR";
    }
    reply->deleteLater();
}

void MyTableWidget::updateTable(){

    // Check if it is table's first setup
    if (isFirstRun){

        //Creates and sets table items with according information
        for (int i = 0; i < currentCoins.size(); i++){

          //Creates items ands sets content of item
          QTableWidgetItem *coinName = new QTableWidgetItem(currentCoins[i]->getName());
          QTableWidgetItem *usdPrice = new QTableWidgetItem(currentCoins[i]->getUSD());
          QTableWidgetItem *eurPrice = new QTableWidgetItem(currentCoins[i]->getEUR());
          QTableWidgetItem *gbpPrice = new QTableWidgetItem(currentCoins[i]->getGBP());

          //Inserts the items to Table
          this->setItem(i, 0, coinName);
          this->setItem(i, 1, usdPrice);
          this->setItem(i, 2, eurPrice);
          this->setItem(i, 3, gbpPrice);

        }

        //Sets first run to false
        isFirstRun = false;
    } else {

        //Modifies current WidgetItems
        for (int i = 0; i < currentCoins.size(); i++){
            this->item(i, 1)->setText(currentCoins[i]->getUSD());
            this->item(i, 2)->setText(currentCoins[i]->getEUR());
            this->item(i, 3)->setText(currentCoins[i]->getGBP());
        }

        //Sets first run to false
        isFirstRun = false;
    }

    //Adjusts table size
    this->adjustSize();
    this->updateGeometry();

    emit updated();
}


void MyTableWidget::setTable(int rows){
    this->setRowCount(rows);
//    this->resize(640,this->rowCount()*this->rowHeight(0)+30);
    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    this->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);


    //Set header names
    QStringList list;
    list.append("Currency");
    list.append("USD");
    list.append("EUR");
    list.append("GBP");
    this->setHorizontalHeaderLabels(list);
}


void MyTableWidget::refresh()
{
    if (timer->isActive()){
        timer->stop();
    }

    //This is the first run of this input file
    isFirstRun = true;

    this->currentCoins = this->ioTool->getCoins();

    //Sets the table size for current coins
    setTable(this->currentCoins.size());

    //Sends request to server for data
    getData();

    //Sets timer to get new data every 30 seconds
    timer->start(30000);

}


void MyTableWidget::resetInput()
{
    //Clears current coin list
    this->currentCoins.clear();

    //Clears table
    this->clearContents();

    //Reads new input
    this->ioTool->refreshInput();
}


void MyTableWidget::getData(){

    QString params = "";

    // Gets ids of coins
    for (auto item : currentCoins){
        params += item->getID() + ",";
    }

    //Sets the URL for API request
    QUrl destination = "https://api.coingecko.com/api/v3/simple/price?ids=" + params + "&vs_currencies=usd,eur,gbp";

    //Sends HTTPS request
    this->manager->get(QNetworkRequest(destination));
}

