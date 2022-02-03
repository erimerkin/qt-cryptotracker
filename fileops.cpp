#include "fileops.h"


FileOps::FileOps(QObject *parent) : QObject(parent)
{
    //Sets up Network manager
    this->manager = new QNetworkAccessManager();

    this->inputs = new QStringList();

    //Connect network request and reply to replyFinished() method
    connect(this->manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    //Function call to read input and handle coins
    refreshInput();
}


void FileOps::readFile(){

    //Gets file location/name from environment variable
    QString fileName = qgetenv("MYCRYPTOCONVERT");

    //Sets file with given name/location
    QFile inputFile(fileName);

    //Prints env var data
    qDebug() << "File from ENV VAR=" << fileName;

    //Opens the input file
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       // Reads file line by line and appends lines to Vector
       while (!in.atEnd())
       {
           inputs->append(in.readLine());
       }
       inputFile.close();
    }

}


void FileOps::replyFinished(QNetworkReply *reply){

    //Checks if there is an error in the get call
    if (reply->error() == QNetworkReply::NoError){
        QByteArray result = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
        QJsonArray jsonArray = jsonResponse.array();

        //Iterates over JSON objects and checks keys and values. 
        foreach (const QJsonValue &item, jsonArray){
            QJsonObject object = item.toObject();   //Converts items in array to JSON object
            QString id = object["id"].toString();   //Reads id of coin
            QString symbol = object["symbol"].toString();   //Reads symbol of coin
            QString name = object["name"].toString();   //Reads name of coin

            //Checks if coin is in given inputs
            if (inputs->contains(symbol, Qt::CaseInsensitive) || inputs->contains(name, Qt::CaseInsensitive) || inputs->contains(id, Qt::CaseInsensitive)){
                coins.append(new Coin(id, symbol, name));
            }

        }
        emit classified(); //SIGNALS for table update
    }
    else{
        //Server reply is an error message
        qDebug() << "ERROR";
    }
    reply->deleteLater();
}


void FileOps::refreshInput(){
    readFile();             //Reads from file
    this->coins.clear();    //Clears current list of coins

    //Send request to get list of all coins
    this->manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/coins/list?include_platform=false")));
}


QVector<Coin*> FileOps::getCoins(){
    return this->coins;
}
