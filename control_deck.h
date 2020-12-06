#ifndef CONTROL_DECK
#define CONTROL_DECK

#include<stdio.h>
#include<stdlib.h>
#include"deck.h"

#define MAX_LINE 40
#define MAX_COLUMN 150

int card_valores[52] = 
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

int card_naipes[52] = 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
 
// int table_border[70][100]; 

int start_game(tp_deck *buying_deck, tp_deck *table_deck[]){
	int i, j, choose;
	int rand_size = 52;
	int aux;
	
	for(i = 0; i < 52; i++){
		choose =  rand()%rand_size;
		append_buying_deck(buying_deck, card_naipes[choose], card_valores[choose]);
		buying_deck->end->visible = 1;
		
		aux = card_naipes[choose];
		card_naipes[choose] = card_naipes[51-i];
		card_naipes[51-i] = aux;
		
		aux = card_valores[choose];
		card_valores[choose] = card_valores[51-i];
		card_valores[51-i] = aux;
		
		rand_size--;
	}
	
	
	for(i = 0; i < 7; i++){
		for(j = 0; j <= i; j++){
			append_buying_deck(table_deck[i], buying_deck->end->naipe, buying_deck->end->valor);
			table_deck[i]->end->visible = 1;
			pop_deck(buying_deck, buying_deck->end->naipe, buying_deck->end->valor);
		}
	}
	
	return 0;
}

void print_borders(){
	for(int i = 0; i < MAX_COLUMN; i++){
		printf("#");
		gotoxy(i, MAX_LINE-1);
		printf("#");
		gotoxy(i+1, 0);
	}
	for(int i = 1; i < MAX_LINE; i++){
		gotoxy(0, i);
		printf("#");
		gotoxy(MAX_COLUMN-1, i);
		printf("#");
	}
	gotoxy(0, MAX_LINE);
}

int print_buying_deck(tp_deck *buying_deck){
	gotoxy(2,2);
	printf("COMPRA:");
	
	// Primeira carta.
	if(!buying_deck->start){return 0;}
	gotoxy(2, 4);
	print_card(buying_deck->start->naipe, buying_deck->start->valor, buying_deck->start->visible);
	// Segunda carta.
	if(!buying_deck->start->next){return 0;}
	gotoxy(2, 5);
	print_card(buying_deck->start->next->naipe, buying_deck->start->next->valor, buying_deck->start->next->visible);
		
	// Terceira carta.
	if(!buying_deck->start->next->next){return 0;}
	gotoxy(2, 6);
	print_card(buying_deck->start->next->next->naipe, buying_deck->start->next->next->valor, buying_deck->start->next->next->visible);
	
	gotoxy(0, MAX_LINE);
	return 1;
}

void print_table_deck(tp_deck *table_deck[]){
	for(int i = 0; i < 7; i++){
		print_deck(table_deck[i], 2+(20*i), 11, 1);
	}
	gotoxy(0, MAX_LINE);
}

void print_conclusion_deck(tp_deck *conclusion_deck[]){
	for(int i = 0; i < 4; i++){
		gotoxy(62+(20*i), 2);
		if(!conclusion_deck[i]->end){printf("[VAZIO]");} 
		else{print_card(conclusion_deck[i]->end->naipe, conclusion_deck[i]->end->valor, conclusion_deck[i]->end->visible);}
	}
	gotoxy(0, MAX_LINE);
}

void show_table(tp_deck *buying_deck, tp_deck *table_deck[], tp_deck *conclusion_deck[]){
	print_borders();
	print_buying_deck(buying_deck);
	print_table_deck(table_deck);
	print_conclusion_deck(conclusion_deck);
}

void choose_options(int *response){

	gotoxy(0, MAX_LINE + 1);
	printf("ESCOLHA UMA OPÇÃO:\n\n");
	printf("1 - Atualizar deck de compra;\n");
	printf("2 - Comprar\n");
	printf("3 - Transferir deck/carta da mesa\n");
	printf("4 - Retirar carta do deck de conclusão\n");
	printf("5 - Sair\n");
	scanf("%d", response);
}

void controller(tp_deck *buying_deck, tp_deck *table_deck[], tp_deck *conclusion_deck[], int option){
	switch(option){
		case 1:
			refresh(buying_deck);
			break;
		default:
			printf("ERRO\n");
	}
}

#endif
