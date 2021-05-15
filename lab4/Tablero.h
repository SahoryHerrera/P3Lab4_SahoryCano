
#ifndef TABLERO_H
#define TABLERO_H

#include <string>

using std::string;

class Tablero {
public:
    Tablero();
    Tablero(const Tablero& orig);
    virtual ~Tablero();

    //void tablero();

public:
    string* tablero;
};

#endif /* TABLERO_H */

