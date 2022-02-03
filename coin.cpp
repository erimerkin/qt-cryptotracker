#include "coin.h"

Coin::Coin(QString id, QString symbol, QString name)
{
    this->id = id;
    this->symbol = symbol;
    this->name = name;
    this->EUR = 0;
    this->GBP = 0;
    this->USD = 0;

}

///////////////////////////////////////////
//: GETTERS
//////////////////////////////////////////

QString Coin::getEUR()
{
    if (this->EUR == 0)
        return "N\\A";

    return QString("%1").arg(this->EUR);

}

QString Coin::getUSD()
{
    if (this->USD == 0)
        return "N\\A";

    return QString("%1").arg(this->USD);

}

QString Coin::getGBP()
{
    if (this->GBP == 0)
        return "N\\A";

    return QString("%1").arg(this->GBP);

}

QString Coin::getID(){
    return this->id;
}

QString Coin::getName(){
    return this->name;
}

//////////////////////////////
//: SETTERS
/////////////////////////////

void Coin::setPrices(double usd, double eur, double gbp){
    this->USD = usd;
    this->EUR = eur;
    this->GBP = gbp;
}
