/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#ifndef UTILS_H
#define UTILS_H

#define min(A,B)    ((A)<(B)?(A):(B))
#define max(A,B)    ((A)>(B)?(A):(B))

#include "structs.h"

// Inicializa o gerador de numeros aleatorios. 
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

// Demora aproximadamente seg segundos a executar
void espera(unsigned int seg);

// Obtem e devolve o dia e hora atuais, por defeito todos os meses vao ter 30 dias e todos os anos 365
void obtemData(int *dia, int *mes, int *ano);

// Obtem a idade de um piloto em dias
int retornaIdade(int dia, int mes, int ano);


// Calcula e devolve o numero de segundos por volta 
// de acordo com as informacoes recebidas por parametro
int calculaSegundos(int idadeP, int pesoP, float expP, int PotC, int metros);


//isec@karts
void base();

//menu
void menu();


//submenu 1
void submenu1();

//submenu 2
void submenu2();

//submenu 3
void submenu3();

//submenu 4
void submenu4();

//submenu 5
void submenu5();

void libertaEquipas(pequipas equipas);

#endif /* UTILS_H */
