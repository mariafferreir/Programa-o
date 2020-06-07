/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "utils.h"


pcampeonato exportarInfoCampeonato(char *nomeficheiro);

void importarInfoCampeonato(pcampeonato camp, char *nomeficheiro);

void listar_campeonato(pcampeonato camp,  pilotos *p, int total_p);

pcampeonato adicionaNoCampeonato(pcampeonato camp, int idP);

pequipas inicializa_campeonato(  int nrcorrida, int total_corridas, carros *c, int total_c, pilotos *p, int total_p);

pequipas calculaTempo(pequipas eq,pcorridas corrida);

pcampeonato atualizaPontuacao(pcampeonato camp, pequipas eq, int total_p);

pcampeonato iniciaCampeonato(pcampeonato camp, pilotos *p, int total_p);

void libertaCampeonato(pcampeonato camp);

#endif /* CAMPEONATO_H */

