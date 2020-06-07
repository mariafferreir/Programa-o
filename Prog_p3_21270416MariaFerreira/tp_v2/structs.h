/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

//ESTRUTURAS: Pilotos, carros, corridas individuais/ treinos, 

#ifndef STRUCTS_H
#define STRUCTS_H

#define NUMERO_EQUIPAS 5
#define LIVRE 0
#define OCUPADO 1
#define PROB_ACIDENTE 0.05
#define SEM_ACIDENTE 0
#define COM_ACIDENTE 1
//----------------------------------------
//ESTRUTURA PILOTO


typedef struct pilot pilotos;



struct pilot{
    char nome_piloto[100];                //Nome do piloto
    int id_piloto;                        //Identificação do piloto
    int dia;                              //Dia de nascimento
    int mes;                              //Mes de nascimento 
    int ano;                              //Ano de nascimento
    int peso_piloto;                      //Peso do piloto
    float experiencia_piloto;             //Experiencia do piloto
    int disponibilidade_piloto;           //Disponibilidade piloto
    int impedimento_piloto;               //Penalização == nr de corridas sem correr (varia entre 1 e 3)
};

//----------------------------------------
//ESTRUTURA CARRO


typedef struct car carros;

struct car{
    int id_carro;                           //Identificação do carro
    int potencia_carro;                     //Potencia do carro
    int avariado;                           //Penalização == nr de corridas sem correr 
    int disponibilidade_carro;              //Disponibilidade carro
};


//----------------------------------------
//ESTRUTURA EQUIPA


typedef struct grupo equipas, *pequipas;

struct grupo{
    int id_carro;                               //ID carro          
    int id_piloto;                              //ID piloto
    int ocorreu_acidente;                       //Indica se a equipa sofreu algum acidente
    int classificacao;                          //Classificacao na corrida
    int contador_plugar;                        //Conta quantas vezes a equipa ficou em primeiro lugar
    int tempo;                                  //Calcula tempos das equipas
    pequipas prox;                              //Ponteiro para o proximo equipas
}; 


//----------------------------------------
//ESTRUTURA INDIVIDUAIS /TREINO


typedef struct training corridas, *pcorridas;


struct training{
    int volta;                                 //Numero de volta em que vai
    int tempo;                                 //Tempo em segundos
    int acidente;                              //Se ocorre 
    int volta_acidente;                        //Numero da volta em que ocorre o acidente
    int lugar;                                 //Lugar da equipa nesta volta
    int nr_voltas;                             //Numero de voltas da corrida
    int com_pista;                             //Comprimento da pista em metros
    int max_carros;                            //Numero maximo de carros que podem participar na corrida
    int id_carro;                              //ID carro
    int id_piloto;                             //ID piloto
    pcorridas prox;                            //Ponteiro para a proxima volta de uma equipa
};


//----------------------------------------

typedef struct championship campeonato, *pcampeonato;


struct championship{
    int id_piloto;
    int pontuacoes;
    pcampeonato prox;
};

#endif /* STRUCTS_H */

