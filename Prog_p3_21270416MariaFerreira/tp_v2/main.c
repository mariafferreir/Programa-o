/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "campeonato.h"
#include "carros.h"
#include "pilotos.h"
#include "structs.h"
#include "corrida.h"

#define ficheiro_pilotos "pilotos.txt"
#define ficheiro_carros "carros.txt"
#define ficheiro_campeonatos "campeonatos.dat"

int main(int argc, char** argv) {
    int op1,op2;
    int i, total_corridas;
    int tot_pilotos, tot_carros;
    initRandom();
    pcampeonato camp;
    carros *vetor_carros;
    
    tot_carros=num_carros(ficheiro_carros);

    vetor_carros=inicializa_carros(ficheiro_carros, tot_carros);  
    
    pilotos *vetor_pilotos;
    
    tot_pilotos=num_pilotos(ficheiro_pilotos);

    vetor_pilotos=inicializa_pilotos(ficheiro_pilotos, tot_pilotos); 
   

    pequipas equipas = NULL;
    
  

    
    do{
        
        system("@cls||clear");
        base();
        menu();    
        scanf(" %d", &op1);
        
        
        switch(op1){
            
            case 1:  
                do{
                submenu1();
                scanf(" %d", &op2);
                   switch(op2){
                        case 1:
                           listar_pilotos(vetor_pilotos, tot_pilotos); 
                           break;
                        case 2:
                           procura_piloto(vetor_pilotos, tot_pilotos);
                           break;
                        case 3:
                           vetor_pilotos = adiciona_penalizacao(vetor_pilotos, tot_pilotos);
                           break;
                   } 
                }while(op2!=4);
                break;
                
            case 2:
                do{
                   submenu2();
                   scanf(" %d", &op2);
                   switch(op2){
                        case 1:
                            printf("nr: %d", tot_carros);
                           listar_carros(vetor_carros, tot_carros);
                           break;
                        case 2:
                           procura_carro(vetor_carros, tot_carros);
                           break;
                   } 
                }while(op2!=3);
                break;
            case 3:
                do{
                submenu3();
                   scanf(" %d", &op2);
                    switch(op2){
                        case 1:
                            break;
                        case 2:
                          
                            break;      
                    } 
                }while(op2!=3);
                break;  
            case 4:
                do{
                   submenu4();
                   scanf(" %d", &op2);
                    switch(op2){
                         case 1:
                            equipas = NULL;
                            equipas = inicializa_corrida( vetor_carros,tot_carros, vetor_pilotos, tot_pilotos);
                            
 
                            vetor_pilotos = atualiza_pilotos_fim_corrida(equipas, vetor_pilotos, tot_pilotos);
                            vetor_carros = atualiza_carros_fim_corrida(equipas, vetor_carros, tot_carros);
                            
                            
                            libertaEquipas(equipas);
                            
                            break;
                    } 
                }while(op2!=2);
                break;
            case 5:
                submenu5();
               i=0;
                
              
                printf("\n\n\n\n\nDEFINIR CAMPEONATO: \n\n");
                do{
                    printf("\n\tTotal de corridas no campeonato [3-8]: ");
                    scanf(" %d", &total_corridas);
                }while(total_corridas<3 || total_corridas>8);
                
                camp=NULL;
                
                camp=iniciaCampeonato(camp, vetor_pilotos,tot_pilotos);
    
                for(i=1;i<(total_corridas+1);i++){
                    
                    equipas = NULL;
                    equipas = inicializa_campeonato( i, total_corridas, vetor_carros,tot_carros, vetor_pilotos, tot_pilotos);
                            
                    vetor_pilotos = atualiza_pilotos_fim_corrida(equipas, vetor_pilotos, tot_pilotos);
                    vetor_carros = atualiza_carros_fim_corrida(equipas, vetor_carros, tot_carros);
                    
                    camp=atualizaPontuacao(camp, equipas, tot_pilotos);
                    
                    libertaEquipas(equipas);
                }
               
                listar_campeonato(camp, vetor_pilotos, tot_pilotos);
               
                vetor_pilotos = atualiza_experiencia_campeonato(camp, vetor_pilotos, tot_pilotos);
                espera(30);
                libertaCampeonato(camp);
                break;       
        }
        
    }while(op1!=6);
    
    
    gravar_vetorP(vetor_pilotos, ficheiro_pilotos, tot_pilotos);
   // gravar_vetorC(vetor_carros, ficheiro_carros, tot_carros);
    return (EXIT_SUCCESS);

}

