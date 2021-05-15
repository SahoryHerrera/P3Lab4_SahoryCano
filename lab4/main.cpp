
#include <cstdlib>

#include "Tablero.h"

#include <iostream>
#include <cstring>

using namespace std;

using std::cout;
using std::cin;
using std::endl;

/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}

void validar_movimiento_normal(int fila_inicial, int columna_inicial,
        int fila_destino, int columna_destino, Tablero*** matriz) {
    if (fila_inicial == fila_destino && columna_inicial == columna_destino) {//valido que la pieza enrealidad quiera moverse
        cout << "La pieza no se mueve. Vuelve a intentar";
    } else if ((fila_destino > 7 || fila_destino < 0) || (columna_destino < 0 || columna_destino > 7)) {
        cout << "Rango no valido";
    } else {
        /*if(){//llamar los métodos de las diagonales
            
        }//*/
    }
}

bool validar_diagonal_derecha(int fila_inicial, int columna_inicial, int fila_destino, int columna_destino) {
    bool flag = true, es_valido = false;
    int cont_fila = fila_inicial, cont_columna = columna_inicial; //cont_columna = columna_inicial
    while (flag) {//para abajo
        if (cont_columna == columna_destino && cont_fila == fila_destino) {
            es_valido = true;
            flag = false;
        } else {
            cont_fila++;
            cont_columna++;
        }//fin else
        if (cont_fila > 7 || cont_columna > 7) {
            flag = false;
        }
    }//fin while
    flag = true;
    while (flag) {//ahora para arriba
        if (cont_columna == columna_destino && cont_fila == fila_destino) {
            es_valido = true;
            flag = false;
        } else {
            cont_fila--;
            cont_columna--;
        }//fin else
        if (cont_fila <= 0 || cont_columna <= 0) {

            flag = false;
        }
    }//fin while
    return es_valido;
}//fin metodo

bool validar_diagonal_izquierda(int fila_inicial, int columna_inicial, int fila_destino, int columna_destino) {
    bool flag = true, es_valido = false;
    int cont_fila = fila_inicial, cont_columna = columna_inicial;
    while (flag) {//para abajo
        if (cont_columna == columna_destino && cont_fila == fila_destino) {
            es_valido = true;
            flag = false;
        } else {
            cont_fila++;
            cont_columna--;
        }//fin else
        if (cont_fila > 7 || cont_columna > 7) {
            flag = false;
        }
    }//fin while
    while (flag) {//otra vez para arriba
        if (cont_columna == columna_destino && cont_fila == fila_destino) {
            es_valido = true;
            flag = false;
        } else {
            cont_fila--;
            cont_columna++;
        }//fin else
        if (cont_fila <= 0 || cont_columna <= 0) {
            flag = false;
        }
    }//fin while
    return es_valido;
}

bool validar_movimiento_casilla_vacía(Tablero*** matriz, int fila_destino, int columna_destino) {
    if (matriz -> tablero[fila_destino][columna_destino] == ' ') {
        return true;
    } else {
        return false;
    }
}

bool validar_captura(bool pieza, bool turno_color_pieza, Tablero*** matriz,
        int fila_inicial, int columna_inicial, int fila_destino, int columna_destino) {
    string peon_enemigo = "", dama_enemiga = "";
    bool captura = false;
    if (turno_color_pieza == false) {
        peon_enemigo = "X";
        dama_enemiga = "RX";
    } else {
        peon_enemigo = "O";
        dama_enemiga = "RO";
    }
    //color pieza = false -> blanca
    if (pieza == false) {//no es dama
        if (turno_color_pieza == false) {//turno blancas
            //valido que el peon avanza a comer
            if (fila_destino - 2 == fila_inicial) {
                //valido para que lado se mueve la pieza
                if (columna_destino > columna_inicial) {
                    if ((matriz -> tablero[fila_inicial - 1][columna_inicial + 1] == peon_enemigo)
                            || (matriz -> tablero[fila_inicial - 1][columna_inicial + 1] ==
                            dama_enemiga)) {//busco la posicion siguiente a la inicial
                        captura = true;
                    }//fin if de pieza enemiga
                } else if (columna_destino < columna_inicial) {
                    if ((matriz->tablero[fila_inicial - 1][columna_inicial - 1] == peon_enemigo)
                            || (matriz ->tablero[fila_inicial - 1][columna_inicial - 1] ==
                            dama_enemiga)) {//busco la posicion siguiente a la inicial
                        captura = true;
                    }//fin if de pieza enemiga
                }//fin else
            }//fin if
        } else {//turno de negras
            //valido que el peon avanza a comer
            if (fila_destino + 2 == fila_inicial) {
                //valido para que lado se mueve la pieza
                if (columna_destino > columna_inicial) {
                    if ((matriz->tablero[fila_inicial + 1][columna_inicial + 1] == peon_enemigo)
                            || (matriz->tablero[fila_inicial + 1][columna_inicial + 1] ==
                            dama_enemiga)) {//busco la posicion siguiente a la inicial
                        captura = true;
                    }//fin if de pieza enemiga
                } else if (columna_destino < columna_inicial) {
                    if ((matriz->tablero[fila_inicial + 1][columna_inicial - 1] == peon_enemigo)
                            || matriz->tablero[fila_inicial + 1][columna_inicial - 1] ==
                            dama_enemiga) {//busco la posicion siguiente a la inicial
                        captura = true;
                    }//fin if de pieza enemiga
                }//fin else
            }//fin if
        }//fin else captura con peones
    } else {//es dama
        //valido para que lado se mueve la pieza
        if (columna_destino > columna_inicial) {
            if (fila_destino > fila_inicial) {
                int j = columna_inicial, primer_obstaculo_i = 0, primer_obstaculo_j = 0;
                for (int i = fila_inicial; i <= fila_destino; i++) {
                    if (matriz->tablero[i][j] == peon_enemigo || matriz->tablero[i][j] == dama_enemiga) {
                        primer_obstaculo_i = i;
                        primer_obstaculo_j = j;
                        i = fila_destino + 1;
                    }//fin if
                    j++;
                }//fin for i
                if (primer_obstaculo_i == fila_destino - 1 && primer_obstaculo_j == columna_destino - 1) {
                    captura = true;
                }//fin captura con dama
            } else if (fila_destino < fila_inicial) {
                int j = columna_inicial, primer_obstaculo_i = 0, primer_obstaculo_j = 0;
                for (int i = fila_inicial; i > fila_destino; i--) {
                    if (matriz->tablero[i][j] == peon_enemigo || matriz->tablero[i][j] == dama_enemiga) {
                        primer_obstaculo_i = i;
                        primer_obstaculo_j = j;
                        i = fila_destino - 1;
                    }//fin if
                    j++;
                }//fin for i
                if (primer_obstaculo_i == fila_destino + 1 && primer_obstaculo_j == columna_destino - 1) {
                    captura = true;
                }//fin captura con dama
            }//fin else
        } else if (columna_destino < columna_inicial) {
            if (fila_destino > fila_inicial) {
                int j = columna_inicial, primer_obstaculo_i = 0, primer_obstaculo_j = 0;
                for (int i = fila_inicial; i <= fila_destino; i++) {
                    if (matriz->tablero[i][j] == peon_enemigo || matriz->tablero[i][j] == dama_enemiga) {
                        primer_obstaculo_i = i;
                        primer_obstaculo_j = j;
                        i = fila_destino + 1;
                    }//fin if
                    j++;
                }//fin for i
                if (primer_obstaculo_i == fila_destino - 1 && primer_obstaculo_j == columna_destino - 1) {
                    captura = true;
                }//fin captura con dama
            } else if (fila_destino < fila_inicial) {
                int j = columna_inicial, primer_obstaculo_i = 0, primer_obstaculo_j = 0;
                for (int i = fila_inicial; i > fila_destino; i--) {
                    if (matriz->tablero[i][j] == peon_enemigo || matriz->tablero[i][j] == dama_enemiga) {
                        primer_obstaculo_i = i;
                        primer_obstaculo_j = j;
                        i = fila_destino - 2;
                    }//fin if
                    j++;
                }//fin for i
                if (primer_obstaculo_i == fila_destino + 1 && primer_obstaculo_j == columna_destino - 1) {
                    captura = true;
                }//fin captura con dama
            }//fin else
        }//fin else 
    }//fin else captura con dama
    return captura;
}//fin método

bool la_partida_acabo(Tablero*** matriz) {
    int contador_blancas = 0, contador_negras = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (matriz->tablero[i][j] == 'X') {
                contador_negras++;
            } else if (matriz->tablero[i][j] == 'O') {//le puse una O
                contador_blancas++;
            }//fin if
        }//fin for
    }//fin for
    if (contador_blancas == 0 || contador_negras == 0) {
        return true;
    } else {
        return false;
    }///fin else
}//fin metodo
