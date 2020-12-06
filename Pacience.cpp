#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"deck.h"
#include"control_deck.h"

int main(){
	int response;
	
	setlocale(LC_ALL, "Portuguese");
	printf("Ponha em tela cheia antes\n");
	system("pause");
	
	tp_deck *buying_deck;
	tp_deck *table_deck[7];
	tp_deck *conclusion_deck[4];
	
	buying_deck = init_deck();
	for(int i = 0; i<7; i++){
		if(i<4){conclusion_deck[i] = init_deck();}
		table_deck[i] = init_deck();
	}
	
	start_game(buying_deck, table_deck);
	
	while(true){
		while(true){
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			choose_options(&response);
			if(response > 0 && response <= 5){break;}
			else{printf("Escolha inválida!\n"); system("pause");}
		}
		if(response == 5){break;}
		controller(buying_deck, table_deck, conclusion_deck, response);
	}
	
	
	destroy_deck(buying_deck);
	for(int i = 0; i<7; i++){
		if(i<4){destroy_deck(conclusion_deck[i]);}
		destroy_deck(table_deck[i]);
	}
	return 0;
}
