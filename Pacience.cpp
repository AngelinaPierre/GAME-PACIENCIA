/*
* ALGOR�TMO E ESTRUTURA DE DADOS 1
* PACI�NCIA
* ALUNO: Alec Santos.
* CURSO: Engenharia de Computa��o.
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
	// Recomenda��o de inicializa��o.
	printf("Ponha em tela cheia antes\n");
	system("pause");
	
	// Declara��o de decks.
	tp_deck *buying_deck;
	tp_deck *table_deck[7];
	tp_deck *conclusion_deck[4];
	
	// Inicializa��o de decks.
	buying_deck = init_deck();
	for(int i = 0; i<7; i++){
		if(i<4){conclusion_deck[i] = init_deck();}
		table_deck[i] = init_deck();
	}
	
	// Atribui��o de valores dos decks.
	start_game(buying_deck, table_deck);
	
	// Execu��o do jogo.
	while(true){
		while(true){
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			choose_options(&response);
			if(response > 0 && response <= 5){break;}
			else{printf("Escolha inv�lida!\n"); system("pause");}
		}
		if(response == 5){break;}
		if(finalize(conclusion_deck)){break;}
		controller(buying_deck, table_deck, conclusion_deck, response);
	}
	
	system("cls");
	show_table(buying_deck, table_deck, conclusion_deck);
	gotoxy((MAX_COLUMN/2)-8, MAX_LINE+2);
	printf("JOGO FINALIZADO!\n");
	
	// Finaliza��o do jogo.
	destroy_deck(buying_deck);
	for(int i = 0; i<7; i++){
		if(i<4){destroy_deck(conclusion_deck[i]);}
		destroy_deck(table_deck[i]);
	}
	return 0;
	
	// testando github.
}
