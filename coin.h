#ifndef COIN_H
#define COIN_H

#include <QString>

/**
 * @brief Coin class holds the ID, name, symbol and coin's price in USD, EUR and GBP
 */
class Coin
{
    public:

    /**
     * @brief           Constructor for coin class
     * @param id        id of coin
     * @param symbol    symbol of coin
     * @param name      name of coin
     */
    Coin(QString id, QString symbol, QString name);

    /**
     * @brief   Gets USD value of coin
     * @return  USD value of coin as a string
     */
    QString getUSD();

    /**
     * @brief   Gets EUR price of coin
     * @return  EUR value of coin as a string
     */
    QString getEUR();

    /**
     * @brief   Gets GBP price of coin
     * @return  GBP value of coin as a string
     */
    QString getGBP();


    /**
     * @brief   Gets the name of coin
     * @return  name of coin
     */
    QString getName();

    /**
     * @brief   Gets the ID of coin
     * @return  ID of coin
     */
    QString getID();

    /**
     * @brief       Sets prices for EUR, USD and GBP
     * @param usd   USD value
     * @param eur   EUR value
     * @param gbp   GBP value
     */
    void setPrices(double usd, double eur, double gbp);

private:
    QString id, symbol, name;
    double EUR, USD, GBP;

};

#endif // COIN_H
