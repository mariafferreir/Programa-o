/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

void espera(unsigned int seg){
    unsigned int goal = seg + clock()/CLOCKS_PER_SEC;
    while (goal > clock()/CLOCKS_PER_SEC)
        ;
}

void obtemData(int *dia, int *mes, int *ano){
    time_t a;
    struct tm* b;

    time(&a);
    b = localtime(&a);
    *dia = b->tm_mday;
    *mes = b->tm_mon;
    *ano = b->tm_year + 1900;
}



int retornaIdade(int dia, int mes, int ano){
    int idade=0, atual, nascimento; //em dias
    int  dia_a,  mes_a,  ano_a;
    

    obtemData(&dia_a,&mes_a,&ano_a);
    
    atual=dia_a+(mes_a*30)+(ano_a*365);
    nascimento=dia+(mes*30)+(ano*365);
    
    idade=atual-nascimento;
    
    return idade;
    
}

int calculaSegundos(int idadeP, int pesoP, float expP, int PotC, int metros){
    return metros/20 + min(3, max(1, 20-expP))*intUniformRnd(1,3)
            + (float)pesoP/idadeP*intUniformRnd(1,2) + 500.0*(intUniformRnd(1,2))/PotC;
}


// Função com alguns exemplos simples de utilizacao das funcoes
void testes(){
    int i, dia, mes, ano;

    initRandom();

    obtemData(&dia, &mes, &ano);
    printf("%2.2d/%2.2d/%d: \n", dia, mes, ano);

    espera(3);

    obtemData(&dia, &mes, &ano);
    printf("%2.2d/%2.2d/%d: \n", dia, mes, ano);

    printf("10 valores aleatorios uniformes entre [4, 10]:\n");
    for(i=0; i<10; i++)
        printf("%d\n", intUniformRnd(4, 10));

    printf(" Probabilidade 0.25 de suceder: \n");
    for(i=0; i<10; i++)
        printf("%d\n", probEvento(0.25));

    printf("Calculo de 10 tempos por volta: \n");
    for(i=0; i<10; i++)
        printf("%d\n", calculaSegundos(30, 80, 20.0, 160, 1000));
}

//isec@karts
void base(){
    printf("______________________________________________________________________________________________________________________________________________________\n");
    printf("______________________________________________________________________________________________________________________________________________________\n\n");
    printf("\t\t\t _|_|_|    _|_|_|  _|_|_|_|    _|_|_|      _|_|_|_|_|    _|    _|    _|_|    _|_|_|    _|_|_|_|_|    _|_|_|  \n");
    printf("\t\t\t   _|    _|        _|        _|          _|          _|  _|  _|    _|    _|  _|    _|      _|      _|        \n");
    printf("\t\t\t   _|      _|_|    _|_|_|    _|        _|    _|_|_|  _|  _|_|      _|_|_|_|  _|_|_|        _|        _|_|    \n");
    printf("\t\t\t   _|          _|  _|        _|        _|  _|    _|  _|  _|  _|    _|    _|  _|    _|      _|            _|  \n");
    printf("\t\t\t _|_|_|  _|_|_|    _|_|_|_|    _|_|_|  _|    _|_|_|_|    _|    _|  _|    _|  _|    _|      _|      _|_|_|    \n");
    printf("\t\t\t                                         _|                                                                  \n");
    printf("\t\t\t                                          _|_|_|_|_|_|                                                      \n\n");
    printf("______________________________________________________________________________________________________________________________________________________\n");
    printf("______________________________________________________________________________________________________________________________________________________\n\n");
}



void menu(){
    printf("\t\t\t\t\t\t\t\t      --MENU--\n\n\n");
    printf("\t\t\t\t\t\t\t\t 1. Pilotos\n");
    printf("\t\t\t\t\t\t\t\t 2. Carros\n");
    printf("\t\t\t\t\t\t\t\t 3. Equipas\n");
    printf("\t\t\t\t\t\t\t\t 4. Corridas Individuais / Treino \n");
    printf("\t\t\t\t\t\t\t\t 5. Campeonato\n");
    printf("\t\t\t\t\t\t\t\t 6. Sair\n");
    printf("\n\t\t\t\t\t\t\t\t Opcao: ");
    
}


void submenu1(){
    printf("\n\n\t\t\t\t\t\t\t\t      --PILOTOS--\n\n\n");
    printf("\t\t\t\t\t\t\t\t 1. Listar Pilotos\n");
    printf("\t\t\t\t\t\t\t\t 2. Procurar Piloto\n");
    printf("\t\t\t\t\t\t\t\t 3. Adiciona Penalizacao a Piloto\n");
    printf("\t\t\t\t\t\t\t\t 4. Sair\n");
    printf("\n\t\t\t\t\t\t\t\t Opcao: ");
    
}

void submenu2(){
    printf("\n\n\t\t\t\t\t\t\t\t      --CARROS--\n\n\n");
    printf("\t\t\t\t\t\t\t\t 1. Listar Carros\n");
    printf("\t\t\t\t\t\t\t\t 2. Procurar Carro\n");
    printf("\t\t\t\t\t\t\t\t 3. Sair\n");
    printf("\n\t\t\t\t\t\t\t\t Opcao: ");

}

void submenu3(){
    printf("\n\n\t\t\t\t\t\t\t\t      --EQUIPAS--\n\n\n");
    printf("\t\t\t\t\t\t\t\t 1. Listar Equipas\n");
    printf("\t\t\t\t\t\t\t\t 2. Novas Equipas\n");
    printf("\t\t\t\t\t\t\t\t 3. Sair\n");
    printf("\n\t\t\t\t\t\t\t\t Opcao: ");
    
}



void submenu4(){
    printf("\n\n\t\t\t\t\t\t\t\t      --CORRIDAS INDIVIDUAIS / TREINO--\n\n\n");
    printf("\t\t\t\t\t\t\t\t 1. Iniciar treino\n");
    printf("\t\t\t\t\t\t\t\t 2. Sair\n");
    printf("\n\t\t\t\t\t\t\t\t Opcao: ");
}

void submenu5(){
     printf("\n\n\t\t\t\t\t\t\t\t      --CAMPEONATO--\n\n\n");
}


void  menuFinaldeCorrida(){
    printf("\n\n\t\t\t\t\t\t\t\t      --CLASSIFICACOES DA CORRIDA--\n\n\n");
    printf("\t\t\t\t\t\t\t\t 1. Listar Corrida Completa\n");
    printf("\t\t\t\t\t\t\t\t 2. Procurar Volta Especifica\n");
    printf("\t\t\t\t\t\t\t\t 3. Sair\n");
    printf("\n\t\t\t\t\t\t\t\t Opcao: ");
}

void libertaEquipas(pequipas equipas){
    pequipas aux;
    while(equipas){
        aux = equipas; 
        equipas=equipas->prox;
        free(aux);
    }
}