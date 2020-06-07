/*        
    TRABALHO PRÁTICO PROGRAMAÇÃO 2018/2019
    NOME: MARIA FONSECA FERREIRA
    ID ALUNO: 21270416
 */

#include "structs.h"
#include "carros.h"
#include "pilotos.h"
#include "corrida.h"
#include "campeonato.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


pcampeonato exportarInfoCampeonato(char *nomeficheiro){
    pcampeonato lista=NULL, novo,ant;
    int j, i;
    int nrnos;
    
    FILE *f= fopen(nomeficheiro, "rb");
       
    if(f==NULL){
        fprintf(f, "Erro na abertura do ficheiro: %s\n", nomeficheiro);
        return 0;
    }
    
    if(fread(&nrnos, sizeof(int),1,f) !=1 ){ //todos os fread devem ser verificados
        fprintf(stderr,"Erro a ler informacao do ficheiro %s [1]\n", nomeficheiro);
        fclose(f);
        return lista;
    }  
    
    
    for (i=0;i < nrnos;i++){
        novo = malloc(sizeof(campeonato));
        if(!novo){
             fprintf(stderr,"Erro a reservar memoria do ficheiro [2.%d]\n", i);
             fclose(f);
            return lista;
        }
        
        if(fread(&novo->pontuacoes, sizeof(int),1,f) !=1|| fread(&novo->id_piloto, sizeof(int),1,f) !=1 ){ //todos os fread devem ser verificados
            fprintf(stderr,"Erro a ler informacao do ficheiro %s [3.%d]\n", nomeficheiro,i);
            fclose(f);
            free(novo);
            return lista;
        }
        
        if(!lista){
            lista=novo;
        }else{
            ant->prox=novo;
        }
        ant = novo;
        
    }
    
    fclose(f);
    return lista;   
    
}
    
void importarInfoCampeonato( pcampeonato camp, char *nomeficheiro){
    pcampeonato aux;
    FILE *f= fopen(nomeficheiro, "wb");
    int contap=0;
    
    if(f==NULL){
        fprintf(f, "Erro na abertura do ficheiro: %s\n", nomeficheiro);
        return;
    }
    
    fwrite(&contap, sizeof(int), 1, f);
    
    for(aux=camp;aux;aux=aux->prox){
        fwrite(&aux->pontuacoes, sizeof (int), 1, f);
        fwrite(&aux->id_piloto, sizeof (int), 1, f);
    }
    
    
    fseek(f,0,SEEK_SET);
    if(fwrite(&contap, sizeof(int), 1, f) != 1){
        fprintf(stderr,"Erro a escrever informacao no ficheiro %s\n", nomeficheiro);
        
    }
    
    
    
    fclose(f);
}
    
    
void listar_campeonato(pcampeonato camp,  pilotos *p, int total_p){

    while(camp){
        for(int i=0; i<total_p; i++){
            if(camp->id_piloto==(p+i)->id_piloto){
                printf("\n\nCampeonato:  \n\tNome: %s \tID Piloto: %d\tPontuacao: %d\n\n",
                (p+i)->nome_piloto,camp->id_piloto,camp->pontuacoes);
            }    
        }
        camp=camp->prox;
    }
}

void libertaCampeonato(pcampeonato camp){
    pcampeonato aux;
    while(camp){
        aux = camp; 
        camp=camp->prox;
        free(aux);
    }
}


pcampeonato adicionaNoCampeonato(pcampeonato camp, int idP){
    pcampeonato novo, aux;
    int i;
    novo= malloc(sizeof(campeonato));
    
        
    
    if(!novo){
        fprintf(stderr, "Erro a reservar memoria para o novo no de campeonato.\n");
        return camp;
    }
    
    novo->pontuacoes=0;
    novo->id_piloto=idP;
    novo->prox=NULL;
            
    
    if(camp==NULL ){
        novo->prox= camp;
        camp=novo;
    }else{
        aux=camp;
        
        while(aux->prox){
            aux=aux->prox;
        }
        
        novo->prox=aux->prox;
        aux->prox=novo;
    }
    
    
    return camp;
}

pcampeonato iniciaCampeonato(pcampeonato camp, pilotos *p, int total_p){
    int i, idP;
    for(i=0;i<total_p; i++){
        idP=(p+i)->id_piloto;
        camp=adicionaNoCampeonato(camp,idP);
    }
    
    return camp;
}


pequipas calculaTempo(pequipas eq,pcorridas corrida){
    int somaTempos;
    pcorridas aux_c;
    pequipas aux_e;
    aux_e=eq;
    aux_c=corrida;
    
    while(aux_e){
        somaTempos=0;
        aux_c=corrida;
        while(aux_c){
            if(aux_e->id_piloto == aux_c->id_piloto){
                somaTempos += aux_c->tempo;
            }
            aux_e->tempo=somaTempos;
            aux_c=aux_c->prox;
        }
        aux_e=aux_e->prox;
    }
    return eq;
    
}




pcampeonato atualizaPontuacao(pcampeonato camp, pequipas eq, int total_p){
    pcampeonato auxc;
    pequipas auxe;
    int soma;
    int tempos[total_p];
    int i=0;
    
    
    for(auxc=camp; auxc; auxc=auxc->prox){
        for(auxe=eq; auxe; auxe=auxe->prox){
            if(auxe->id_piloto==auxc->id_piloto){
                
                if(auxe->classificacao==1){
                    auxc->pontuacoes=auxc->pontuacoes+5;
                }
            
                if(auxe->classificacao==2){
                    auxc->pontuacoes=auxc->pontuacoes+4;
                }

                if(auxe->classificacao==3){
                    auxc->pontuacoes=auxc->pontuacoes+3;
                }
            
           
                if(auxe->classificacao==4){
                    auxc->pontuacoes=auxc->pontuacoes+2;
                }
            
                if(auxe->classificacao==5){
                    auxc->pontuacoes=auxc->pontuacoes+1;
                }
            
            }
        }

    }
    
    return camp;
    
}




pequipas inicializa_campeonato( int nrcorrida, int total_corridas, carros *c, int total_c, pilotos *p, int total_p){
    pcorridas corrida=NULL;
    pequipas infoequipa;
    pequipas eq = NULL;
    pcampeonato camp;
    int total_e;
    int num_voltas, comprimento, nr_carros;
    int c_corredores=0, c_voltas=1;
    int i, j;
    int flag_acidente;
    int op;
    
    
    printf("\n\n\n\n\nDEFINIR CORRIDA: \n\n");
    do{
        printf("\n\tNumero de Voltas [5-10]: ");
        scanf(" %d", &num_voltas);
    }while(num_voltas<5 || num_voltas>10);
    
    do{
    printf("\n\tComprimento da pista em metros [500-1000]: ");
        scanf(" %d", &comprimento);
    }while(comprimento<500 || comprimento>1000);
    
    
    printf("\n\tNumero maximo de carros que podem participar: ");
    scanf(" %d", &nr_carros);
    
    
    total_e=num_equipas(nr_carros,c, total_c, p, total_p);
    
    //printf("Numero equipas: %d\n", total_e);
    
    for(i=0; i<total_e;i++){
        eq=criaEquipa(eq, total_e, c, total_c, p, total_p);
    }
    
   
    
    listar_equipas(eq);
    
    
    for(i=0; i<(total_e*num_voltas); i++){
        infoequipa=getinfo(eq,c_corredores);
        if(infoequipa->ocorreu_acidente == SEM_ACIDENTE){
            flag_acidente=SEM_ACIDENTE;
            corrida=adicionaNo(&flag_acidente,c_voltas,num_voltas, comprimento, nr_carros,infoequipa, total_e, corrida, c, total_c, p, total_p);
            if(flag_acidente==COM_ACIDENTE){
                eq=colocaAcidente(eq,c_corredores);
            }
        }
     
    c_corredores++; 
        
    if(c_corredores == total_e){ 
        corrida=atribuiClassificao(c_voltas, corrida);
        c_corredores=0;
        mostraResultadosVolta(c_voltas,corrida, p, total_p);
        espera(5);
        c_voltas++;
     }
    }
    
    eq=calculaTempoFinal(eq,corrida);
    eq=calculaTempo(eq,corrida);
    eq=classificacaoFinal(eq,corrida,total_e);
    //listar_equipas(eq);
    eq=contaPrimeirosLugares(num_voltas, eq, total_e, corrida);
    mostraClassificaoFinal(num_voltas, eq, total_e, corrida,p, total_p);
    
    do{
        menuFinaldeCorrida();
        scanf(" %d", &op);
        switch(op){
            
            case 1:
                mostraCorridaCompleta(num_voltas, corrida, p, total_p);
                break;
            case 2:
                mostraVoltaEspecifica(corrida, p, total_p);
                break;   
        }            
    }while(op!=3);
    
    libertaCorrida(corrida);
    
    
    
    return eq;
}

