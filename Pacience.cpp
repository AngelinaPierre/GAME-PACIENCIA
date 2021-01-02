/*
* ALGORÍTMO E ESTRUTURA DE DADOS 1
* PACIÊNCIA
* ALUNO: Alec Santos.
* CURSO: Engenharia de Computação.
* TURMA: 
*/
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"deck.h"
#include"control_deck.h"

int main(){
	int response;
	
	// Ativa os caracteres da lingua portuguesa.
	setlocale(LC_ALL, "Portuguese");
	// Recomendação de inicialização.
	printf("Ponha em tela cheia antes\n");
	system("pause");
	
	// Declaração de decks.
	tp_deck *buying_deck;
	tp_deck *table_deck[7];
	tp_deck *conclusion_deck[4];
	
	// Inicialização de decks.
	buying_deck = init_deck();
	for(int i = 0; i<7; i++){
		if(i<4){conclusion_deck[i] = init_deck();}
		table_deck[i] = init_deck();
	}
	
	// Atribuição de valores dos decks.
	start_game(buying_deck, table_deck);
	
	// Execução do jogo.
	while(true){
		while(true){
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			choose_options(&response);
			if(response > 0 && response <= 5){break;}
			else{printf("Escolha inválida!\n"); system("pause");}
		}
		if(response == 5){break;}
		if(finalize(conclusion_deck)){break;}
		controller(buying_deck, table_deck, conclusion_deck, response);
	}
	
	system("cls");
	show_table(buying_deck, table_deck, conclusion_deck);
	gotoxy((MAX_COLUMN/2)-8, MAX_LINE+2);
	printf("JOGO FINALIZADO!\n");
	
	// Finalização do jogo.
	destroy_deck(buying_deck);
	for(int i = 0; i<7; i++){
		if(i<4){destroy_deck(conclusion_deck[i]);}
		destroy_deck(table_deck[i]);
	}
	return 0;
	
	// testando github.
}
