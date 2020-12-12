#ifndef CONTROL_DECK
#define CONTROL_DECK

#include<stdio.h>
#include<stdlib.h>
#include"deck.h"

#define MAX_LINE 40
#define MAX_COLUMN 150

// VALORES DAS CARTAS
// Os naipes e valores est�o divididos em duas matrizes, possuindo a mesma coordenada.
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

// START GAME(DECK DE COMPRA, DECK DE MESA)
// Inicializa o jogo, adicionando cartas no deck de compra e nos decks de mesa.
int start_game(tp_deck *buying_deck, tp_deck *table_deck[]){
	int i, j, choose;
	int rand_size = 52;
	int aux;
	
	// Tornando os valores aleat�rios e adicionando todas as cartas ao deck de compra.
	for(i = 0; i < 52; i++){
		choose =  rand()%rand_size;
		append_deck(buying_deck, card_naipes[choose], card_valores[choose]);
		buying_deck->end->visible = 0;
		
		aux = card_naipes[choose];
		card_naipes[choose] = card_naipes[51-i];
		card_naipes[51-i] = aux;
		
		aux = card_valores[choose];
		card_valores[choose] = card_valores[51-i];
		card_valores[51-i] = aux;
		
		rand_size--;
	}	
	// Transferindo e distribuindo cartas sobressalentes do deck de compra para os decks de mesa.
	for(i = 0; i < 7; i++){
		for(j = 0; j <= i; j++){
			append_deck(table_deck[i], buying_deck->end->naipe, buying_deck->end->valor);
			pop_deck(buying_deck, buying_deck->end->naipe, buying_deck->end->valor);
			table_deck[i]->end->visible = 0;
		}
	}
	
	return 0;
}

// PRINT BORDERS()
// Imprime as bordas da mesa.
void print_borders(){
	// Imprimindo as bordas superior e inferior.
	for(int i = 0; i < MAX_COLUMN; i++){
		printf("#");
		gotoxy(i, MAX_LINE-1);
		printf("#");
		gotoxy(i+1, 0);
	}
	// Imprimindo as bordas laterais.
	for(int i = 1; i < MAX_LINE; i++){
		gotoxy(0, i);
		printf("#");
		gotoxy(MAX_COLUMN-1, i);
		printf("#");
	}
	// Posicionando o cursor do prompt na �ltima casa;
	gotoxy(0, MAX_LINE);
}

// PRINT BUYING DECK(DECK DE COMPRA)
// Imprime o deck de compras.
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

// PRINT TABLE DECK(DECK DE MESA)
// Imprime os decks de mesa.
void print_table_deck(tp_deck *table_deck[]){
	// Imprimindo o deck em casa posi��o.
	for(int i = 0; i < 7; i++){
		print_deck(table_deck[i], 2+(20*i), 11, 1);
	}
	gotoxy(0, MAX_LINE);
}

// PRINT CONCLUSION DECK(DECK DE CONCLUS�O)
// Imprime o deck de conclus�o (superior).
void print_conclusion_deck(tp_deck *conclusion_deck[]){
	// Imprimindo o deck em cada posi��o.
	for(int i = 0; i < 4; i++){
		gotoxy(62+(20*i), 2);
		if(!conclusion_deck[i]->end){printf("[VAZIO]");} 
		else{print_card(conclusion_deck[i]->end->naipe, conclusion_deck[i]->end->valor, conclusion_deck[i]->end->visible);}
	}
	gotoxy(0, MAX_LINE);
}

// TURN END VISIBLE(DECK DE MESA)
// Transforma a �ltima carta de cada deck de mesa vis�vel.
void turn_end_visible(tp_deck *table_deck[]){
	for(int i = 0; i < 7; i++){
		table_deck[i]->end->visible = 1;
	}
}

// SHOW TABLE(DECK DE COMPRA, DECK DE MESA, DECK DE CONCLUS�O)
// Imprime o jogo com todos os decks inclusos.
void show_table(tp_deck *buying_deck, tp_deck *table_deck[], tp_deck *conclusion_deck[]){
	turn_end_visible(table_deck);
	print_borders();
	print_buying_deck(buying_deck);
	print_table_deck(table_deck);
	print_conclusion_deck(conclusion_deck);
}

// CHOOSE OPTIONS(RESPOSTA)
// Apresenta um menu e espera por uma resposta.
void choose_options(int *response){

	gotoxy(0, MAX_LINE + 1);
	printf("ESCOLHA UMA OP��O:\n\n");
	printf("1 - Atualizar deck de compra;\n");
	printf("2 - Comprar\n");
	printf("3 - Transferir deck/carta da mesa\n");
	printf("4 - Retirar carta do deck de conclus�o\n");
	printf("5 - Sair\n");
	scanf("%d", response);
}

// BUY(DECK DE COMPRA, DECK DE MESA, DECK DE CONCLUS�O, OP��O, DECK DESTINAT�RIO)
// Compra uma carta do deck de compras.
void buy(tp_deck *buying_deck, tp_deck *table_deck[], tp_deck *conclusion_deck[], int option, int dest_deck){
	// Verifica se o deck destinat�rio � um deck de conclus�o v�lido.
	if(option == 1 && dest_deck >= 0 && dest_deck < 4){
		// Verifica se o deck est� vazio.
		if(conclusion_deck[dest_deck]->start == NULL || conclusion_deck[dest_deck]->end == NULL){
			// Verifica se a carta de compra � ACE(�S).
			if(buying_deck->start->valor == ACE){
				// Transfere a carta.
				append_deck(conclusion_deck[dest_deck], buying_deck->start->naipe, buying_deck->start->valor);
				pop_deck(buying_deck, buying_deck->start->naipe, buying_deck->start->valor);
				printf("Conclu�do!\n");
				system("pause");
			} else{
				printf("\nA��o inv�lida!!\n");
				system("pause");
			}
		// Verifica se a carta de compra � a sucessora na sequ�ncia.
		} else if(conclusion_deck[dest_deck]->end->naipe == buying_deck->start->naipe && conclusion_deck[dest_deck]->end->valor == buying_deck->start->valor-1){
			// Transfere a carta.
			append_deck(conclusion_deck[dest_deck], buying_deck->start->naipe, buying_deck->start->valor);
			pop_deck(buying_deck, buying_deck->start->naipe, buying_deck->start->valor);
			printf("Conclu�do!\n");
			system("pause");
		} else{
			// Retorna a��o inv�lida.
			printf("\nA��o inv�lida!!\n");
			system("pause");
		}
	}
	// Verifica se o deck destinat�rio � um deck de mesa v�lido.
	else if(option == 2 && dest_deck >= 0 && dest_deck < 7){
		// Verifica se o deck est� vazio.
		if(table_deck[dest_deck]->start == NULL || table_deck[dest_deck]->end == NULL){
			// Verifica se a carta de compra � REI.
			if(buying_deck->start->valor == REI){
				// Transfere a carta.
				append_deck(table_deck[dest_deck], buying_deck->start->naipe, buying_deck->start->valor);
				pop_deck(buying_deck, buying_deck->start->naipe, buying_deck->start->valor);
				printf("Conclu�do!\n");
				system("pause");
			} else{
				printf("\nA��o inv�lida!!\n");
				system("pause");
			}
		// Verifica se a carta de compra � a sucessora na sequ�ncia.
		} else if(table_deck[dest_deck]->end->naipe%2 != buying_deck->start->naipe%2 && table_deck[dest_deck]->end->valor == buying_deck->start->valor+1){
			// Transfere a carta.
			append_deck(table_deck[dest_deck], buying_deck->start->naipe, buying_deck->start->valor);
			pop_deck(buying_deck, buying_deck->start->naipe, buying_deck->start->valor);
			printf("Conclu�do!\n");
			system("pause");
		} else{
			// Retorna a��o inv�lida.
			printf("\nA��o inv�lida!!\n");
			system("pause");
		}
	}
	// Condi��o quando o deck n�o � v�lido.
	else{
		// Retorna op��o inv�lida.
		printf("\nOp��o inv�lida!!\n");
		system("pause");
	}
}

// TRANSFERENCE(DECK DE COMPRA, DECK DE MESA, DECK DE CONCLUS�O, OP��O, DECK REMETENTE, DECK DESTINAT�RIO)
// Transfere uma carta ou parti��o do deck de mesa.
void transference(tp_deck *buying_deck, tp_deck *table_deck[], tp_deck *conclusion_deck[], int option, int orig_deck, int dest_deck){
	tp_deck *trade_deck;
	trade_deck = init_deck();
	
	// Verifica se o deck destinat�rio � um deck de conclus�o.
	if(option == 1){
		// Verifica se os decks escolhidos s�o v�lidos.
		if(orig_deck >= 0 && orig_deck < 7 && dest_deck >= 0 && dest_deck < 4){
			// Verifica se o deck de conclus�o est� vazio e se a carta a ser transferida � ACE.
			if(conclusion_deck[dest_deck]->start == NULL && table_deck[orig_deck]->end->valor == ACE){
				// Transfere a carta.
				append_deck(conclusion_deck[dest_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				pop_deck(table_deck[orig_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				printf("Conclu�do!\n");
				system("pause");
			}
			// Verifica se a carta da transfer�ncia � a sucessora na sequ�ncia do deck de conclus�o.
			else if(conclusion_deck[dest_deck]->end->naipe == table_deck[orig_deck]->end->naipe && conclusion_deck[dest_deck]->end->valor == table_deck[orig_deck]->end->valor-1){
				// Transfere a carta.
				append_deck(conclusion_deck[dest_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				pop_deck(table_deck[orig_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				printf("Conclu�do!\n");
				system("pause");
			} else{
				// Retorna a��o inv�lida.
				printf("\nA��o inv�lida!!\n");
				system("pause");
			}
		}
		// Condi��o quando os decks n�o s�o v�lidos.
		else{
			printf("\nA��o inv�lida!!\n");
			system("pause");
		}
	}
	// Verifica se o deck destinat�rio � um deck de mesa.
	else if(option == 2){
		int partition_naipe, partition_valor;
		
		// Solicita o naipe da carta do topo da parti��o.
		system("cls");
		show_table(buying_deck, table_deck, conclusion_deck);
		printf("Escolha o naipe da carta para parti��o:\n1 = [COPAS] || 2 = [ESPADAS] || 3 = [OUROS] || 4 = [PAUS]\n\n");
		scanf("%d", &partition_naipe);
		
		// Solicita o valor da carta do topo da parti��o.
		system("cls");
		show_table(buying_deck, table_deck, conclusion_deck);
		printf("Escolha o valor da carta para parti��o:\n1 = [ACE] || 11 = [VALETE] || 12 = [DAMA] || 13 = [REI]\n\n");
		scanf("%d", &partition_valor);
		
		// Verifica se os decks escolhidos s�o v�lidos.
		if(orig_deck >= 0 && orig_deck < 7 && dest_deck >= 0 && dest_deck < 7){
			// Verifica se a parti��o est� dispon�vel para transfer�ncia.
			if(!available_transfer(table_deck[orig_deck], partition_naipe, partition_valor)){
				// Retorna a��o inv�lida.
				printf("\nA��o inv�lida!!\n");
				system("pause");
			}
			// Verifica se o deck destinat�rio est� vazio e se o a carta do topo da parti��o � REI.
			else if(table_deck[dest_deck]->start == NULL && partition_valor == REI){
				// Transfere as cartas para um deck auxiliar de troca (trade deck).
				while(table_deck[orig_deck]->end->naipe != partition_naipe || table_deck[orig_deck]->end->valor != partition_valor){
					append_deck(trade_deck, table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
					pop_deck(table_deck[orig_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				}
				// Transfere a �ltima carta para o deck auxiliar de troca.
				append_deck(trade_deck, table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				pop_deck(table_deck[orig_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				// Transfere as cartas do deck auxiliar de troca para o deck destinat�rio.
				while(trade_deck->start != NULL){
					append_deck(table_deck[dest_deck], trade_deck->end->naipe, trade_deck->end->valor);
					pop_deck(trade_deck, trade_deck->end->naipe, trade_deck->end->valor);
				}
				printf("Conclu�do!\n");
				system("pause");
			}
			// Verifica se a carta do topo da parti��o � sucessora na sequ�ncia do deck destinat�rio.
			else if(table_deck[dest_deck]->end->naipe%2 != partition_naipe%2 && table_deck[dest_deck]->end->valor == partition_valor+1){
				// Transfere as cartas para um deck auxiliar de troca.
				while(table_deck[orig_deck]->end->naipe != partition_naipe || table_deck[orig_deck]->end->valor != partition_valor){
					append_deck(trade_deck, table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
					pop_deck(table_deck[orig_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				}
				// Transfere a �ltima carta para o deck auxiliar de troca.
				append_deck(trade_deck, table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				pop_deck(table_deck[orig_deck], table_deck[orig_deck]->end->naipe, table_deck[orig_deck]->end->valor);
				// Transfere as cartas do deck auxiliar de troca para o deck destinat�rio.
				while(trade_deck->start != NULL){
					append_deck(table_deck[dest_deck], trade_deck->end->naipe, trade_deck->end->valor);
					pop_deck(trade_deck, trade_deck->end->naipe, trade_deck->end->valor);
				}
				printf("Conclu�do!\n");
				system("pause");
			}
			// Condi��o quando a transfer�ncia da parti��o n�o � v�lida.
			else{
				printf("\nA��o inv�lida!!\n");
				system("pause");
			}
		}
		// Condi��o quando os decks n�o s�o v�lidos.
		else{
			printf("\nA��o inv�lida!!\n");
			system("pause");
		}
	}
	// Condi��o quando a op��o n�o � v�lida.
	else{
		printf("\nA��o inv�lida!!\n");
		system("pause");
	}
	// Destr�i o deck auxiliar.
	destroy_deck(trade_deck);
}

// POP CONCLUSION DECK(DECK DE MESA, DECK DE CONCLUS�O, DECK REMETENTE, DECK DESTINAT�RIO)
// Retira uma carta do deck de conclus�o, transferindo-a para um deck de mesa.
void pop_conclusion_deck(tp_deck *table_deck[], tp_deck *conclusion_deck[], int orig_deck, int dest_deck){
	// Verifica se os decks escolhidos s�o v�lidos.
	if(orig_deck >= 0 && orig_deck < 4 && dest_deck >= 0 && dest_deck < 7){
		// Verifica se o deck destinat�rio est� vazio e se a carta a ser transferida � REI.
		if(table_deck[dest_deck]->end == NULL && conclusion_deck[orig_deck]->end->valor == REI){
			// Transfere a carta.
			append_deck(table_deck[dest_deck], conclusion_deck[orig_deck]->end->naipe, conclusion_deck[orig_deck]->end->valor);
			pop_deck(conclusion_deck[orig_deck], conclusion_deck[orig_deck]->end->naipe, conclusion_deck[orig_deck]->end->valor);
			printf("Conclu�do!\n");
			system("pause");
		}
		// Verifica se a carta a ser transferida � a sucessiva na sequ�ncia do deck de conclus�o.
		else if(conclusion_deck[orig_deck]->end->naipe%2 != table_deck[dest_deck]->end->naipe%2 && conclusion_deck[orig_deck]->end->valor == table_deck[dest_deck]->end->valor-1){
			// Transfere a carta.
			append_deck(table_deck[dest_deck], conclusion_deck[orig_deck]->end->naipe, conclusion_deck[orig_deck]->end->valor);
			pop_deck(conclusion_deck[orig_deck], conclusion_deck[orig_deck]->end->naipe, conclusion_deck[orig_deck]->end->valor);
			printf("Conclu�do!\n");
			system("pause");
		}
		// Condi��o quando a transfer�ncia � inv�lida.
		else{
			printf("\nA��o inv�lida!!\n");
			system("pause");
		}
	}
	// Condi��o quando os decks n�o s�o v�lidos.
	else{
		printf("\nA��o inv�lida!!\n");
		system("pause");
	}
}

// CONTROLLER(DECK DE COMPRA, DECK DE MESA, DECK DE CONCLUS�O, OP��O)
// Controla a pr�xima a��o de acordo com a op��o do usu�rio.
void controller(tp_deck *buying_deck, tp_deck *table_deck[], tp_deck *conclusion_deck[], int option){
	int option_deck, orig_deck, dest_deck;
	
	// Verifica a escolha.
	switch(option){
		case 1:
			// Atualiza o deck de compras.
			refresh(buying_deck);
			break;
		case 2:
			// Solicita o tipo de compra.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o tipo do deck destinat�rio:\n1 - Deck de conclus�o\n2 - Deck de mesa\n\n");
			scanf("%d", &option_deck);
			
			// Solicita o deck destinat�rio.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o deck destinat�rio:\n\n");
			scanf("%d", &dest_deck);
			dest_deck--;
			
			// Executa a fun��o da compra.
			buy(buying_deck, table_deck, conclusion_deck, option_deck, dest_deck);
			break;
		case 3:
			
			// Solicita o tipo de transfer�ncia.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o tipo do deck destinat�rio:\n1 - Deck de conclus�o\n2 - Deck de mesa\n\n");
			scanf("%d", &option_deck);
			
			// Solicita o deck remetente.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o deck remetente:\n\n");
			scanf("%d", &orig_deck);
			orig_deck--;
			
			// Solicita o deck destinat�rio.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o deck destinat�rio:\n\n");
			scanf("%d", &dest_deck);
			dest_deck--;
			
			// Executa a fun��o de transfer�ncia.
			transference(buying_deck, table_deck, conclusion_deck, option_deck, orig_deck, dest_deck);
			
			break;
		case 4:
			
			// Solicita o deck remetente.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o deck remetente:\n\n");
			scanf("%d", &orig_deck);
			orig_deck--;
			
			// Solicitando o deck destinat�rio.
			system("cls");
			show_table(buying_deck, table_deck, conclusion_deck);
			printf("Escolha o deck destinat�rio:\n\n");
			scanf("%d", &dest_deck);
			dest_deck--;
			
			// Executa a fun��o de retirada do deck de conclus�o.
			pop_conclusion_deck(table_deck, conclusion_deck, orig_deck, dest_deck);
			break;
		default:
			// Condi��o quando a op��o � inv�lida.
			printf("ERRO\n");
	}
}

int finalize(tp_deck *conclusion_deck[]){
	if(conclusion_deck[0]->end->valor == REI && conclusion_deck[1]->end->valor == REI && conclusion_deck[2]->end->valor == REI && conclusion_deck[3]->end->valor == REI)
	{
		return 1;
	}
	return 0;
}

#endif
