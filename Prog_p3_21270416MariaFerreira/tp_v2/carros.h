/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#ifndef CARROS_H
#define CARROS_H

#include "structs.h"

int num_carros(char *nomeficheiro);

carros* inicializa_carros(char *nomeficheiro, int total_c);

void listar_carros(carros *p, int total_c);

void procura_carro(carros *p, int total_c);

carros* atualiza_carros_fim_corrida(pequipas eq, carros *c, int total_c);

void gravar_vetorC(carros *c, char *nomefich, int total);

#endif /* CARROS_H */

