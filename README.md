# qt-cryptotracker
This project is done as a part of CMPE230 class. It implements a QT UI application that checks current crypto prices from a web API and displays it. 
### Dependencies
- QT 5.15

### Build
To build QT version 5.15 is needed. For configuration environment variable `MYCRYPTOCONVERT` should be set to a path of configuration file(wanted cryptocurrencies seperated by line).

``` 
qmake Cointracker.pro
qmake make
```
