/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#ifndef PILOTOS_H
#define PILOTOS_H

#include "structs.h"

int num_pilotos(char *nomeficheiro);

pilotos* inicializa_pilotos(char *nomeficheiro, int total);

void listar_pilotos(pilotos *p, int total);

void procura_piloto(pilotos *p, int total);

pilotos* atualiza_pilotos_fim_corrida(pequipas eq, pilotos *p, int total_p);

pilotos* adiciona_penalizacao(pilotos *p, int total);

void gravar_vetorP(pilotos *p, char *nomefich, int total) ;

pilotos* atualiza_experiencia_campeonato(pcampeonato camp,  pilotos *p, int total_p);

#endif /* PILOTOS_H */

