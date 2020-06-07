/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#ifndef CORRIDA_H
#define CORRIDA_H


int num_equipas(int num_max, carros *c, int total_c, pilotos *p, int total_p);

pequipas criaEquipa(pequipas eq, int total_e, carros *c, int total_c, pilotos *p, int total_p);

void listar_equipas(pequipas eq);

pequipas getinfo(pequipas aux, int index);

pcorridas adicionaNo(int *flag, int v,int num_voltas, int comprimento, int nr_carros, pequipas infoequipa, int total_e, pcorridas corrida, carros *c, int total_c, pilotos *p, int total_p);

void mostraCorridaCompleta(int num_voltas, pcorridas corrida, pilotos *p, int total_p);

pequipas colocaAcidente(pequipas eq, int corredor);

pcorridas atribuiClassificao(int num_voltas,pcorridas corrida);

void mostraResultadosVolta(int v, pcorridas corrida,  pilotos *p, int total_p);

pequipas calculaTempoFinal( pequipas eq, pcorridas corrida);

pequipas classificacaoFinal( pequipas eq, pcorridas corrida, int total_e);

pequipas contaPrimeirosLugares(int num_voltas, pequipas eq,int total_e, pcorridas corrida);

void  mostraClassificaoFinal(int num_voltas, pequipas eq,int total_e, pcorridas corrida, pilotos *p, int total_p);

void mostraVoltaEspecifica(pcorridas corrida, pilotos *p, int total_p);

void liberta(pcorridas corrida);

pequipas inicializa_corrida( carros *c, int total_c, pilotos *p, int total_p);

#endif /* TREINO_H */

