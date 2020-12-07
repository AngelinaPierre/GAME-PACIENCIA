#ifndef DECK
#define DECK

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

// OBS: Os naipes estão separados por paridade de números e pela cor, assim, os naipes de mesma cor possuem mesma paridade de número.

#define	COPAS 1
#define ESPADAS 2
#define OUROS 3
#define PAUS 4

#define REI 13
#define DAMA 12
#define VALETE 11
#define ACE 1


//...............................................................................................

// ESTRUTURAS

// Carta.
typedef struct card_aux{
	int valor;
	int naipe;
	int visible;
	card_aux *prev;
	card_aux *next;
} tp_card;

// Deck.
typedef struct{
	tp_card *start;
	tp_card *end;
} tp_deck;
//...............................................................................................

// FUNÇÕES

// INIT DECK():
// Inicializa o deck.
tp_deck *init_deck(){
   tp_deck *deck = (tp_deck*) malloc(sizeof(tp_deck));   
   deck->start = NULL;   
   deck->end = NULL; 
   return deck;
}

// ALLOC CARD():
// Aloca o espaço da carta.
tp_card *alloc_card(){
	tp_card* card;
	card = (tp_card*) malloc(sizeof(tp_card));
	return card;
}

// INIT CARD(NAIPE, VALOR):
// Inicia a carta (FUNÇÃO TESTE).
tp_card *init_card(int naipe, int valor){
	tp_card *new_card;
	new_card = alloc_card();
	new_card->naipe = naipe;
	new_card->valor = valor;
	
	return new_card;
}

// GO TO XY(COLUMN, LINE)
// Posiciona o cursor na coordenada indicada.
void gotoxy( int column, int line ){
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

// APPEND DECK(DECK, NAIPE, VALOR):
// Adiciona a carta ao fim do deck
int append_deck(tp_deck *deck, int naipe, int valor){
	tp_card *new_card;
	new_card = alloc_card();
	if (!new_card) return 0;
	new_card->naipe = naipe;
	new_card->valor = valor;
	
	// Verifica se o deck de compra está vazio.
	if((deck->start == NULL) && (deck->end == NULL)){
		new_card->next = NULL;
		new_card->prev = NULL;
		deck->start = deck->end = new_card;
	} else{
		new_card->next = NULL;
		new_card->prev = deck->end;
		deck->end->next = new_card;
		deck->end = new_card;
	}
	deck->end->visible = 1;
	return 1;
}

// SEARCH CARD(DECK, NAIPE, VALOR):
// Procura a carta no deck com determinado valor.
tp_card* search_card(tp_deck *deck, int naipe, int valor){   
  tp_card *current_card;
  current_card = deck->start;
  while((current_card != NULL) && ((current_card->valor != valor) || (current_card->naipe != naipe))){ 
        current_card = current_card->next;}
  return current_card;
}

// POP DECK(DECK, NAIPE, VALOR)
// Retira/Exclui uma carta do deck.
int pop_deck(tp_deck *deck, int naipe, int valor){
	tp_card *current_card;
	current_card = deck->start;
	while((current_card != NULL) && !((current_card->naipe == naipe) && (current_card->valor == valor))){
		current_card = current_card->next;
	}
	if(current_card == NULL) return 0;
	if(deck->start == deck->end){
		deck->start = deck->end = NULL;
	} else if(deck->start == current_card){
		deck->start = deck->start->next;
		current_card->next->prev = NULL;
	} else if(deck->end == current_card){
		deck->end = deck->end->prev;
		current_card->prev->next = NULL;
	} else{
		current_card->next->prev = current_card->prev;
		current_card->prev->next = current_card->next;
	}
	free(current_card);
	return 1;
}

// DESTROY DECK(DECK):
// Destrói o deck.
tp_deck* destroy_deck (tp_deck *deck){   
	tp_card *current_card;
	current_card = deck->start;
	while(current_card != NULL){ 
        deck->start = current_card->next;
        free(current_card);
        current_card = deck->start;
		}
	free(deck);
	return NULL;
}

// TRANSFER DECK(DECK REMETENTE, DECK DESTINATÁRIO, NAIPE, VALOR):
// Transfere determinada fração do deck ou o deck completo para outro local.
int transfer_deck(tp_deck *deck_remetente, tp_deck *deck_destinatario, int naipe, int valor){
	
	return 1;
}

// REFRESH(DECK)
// Cicla as cartas disponíveis para compra.
int refresh(tp_deck *buying_deck){
	if(buying_deck->start->next->next == NULL){return 0;}
	
	int i;
	for(i = 0; i < 3; i++){
		tp_card *current_card;
		current_card = buying_deck->start;
		buying_deck->start = buying_deck->start->next;
		buying_deck->start->prev = NULL;
		append_deck(buying_deck, current_card->naipe, current_card->valor);
		free(current_card);
	}
	return 1;
}

// PRINT CARD(NAIPE, VALOR)
// Imprime a carta.
void print_card(int naipe, int valor, int visible){
	if(!visible){
		printf("[@][@]");
	} else{		
		switch(valor){
			case 1:
				printf("[ACE]");
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				printf("[%d]", valor);
				break;
			case 11:
				printf("[VALETE]");
				break;
			case 12:
				printf("[DAMA]");
				break;
			case 13:
				printf("[REI]");
				break;
			default:
    	        printf("[ERRO]\n");
    	        break;
		}
		switch(naipe){
			case 1:
    	        printf("[COPAS]\n");
    	        break;
    	    case 2:
    	        printf("[ESPADAS]\n");
    	        break;
    	    case 3:
    	        printf("[OUROS]\n");
    	        break;
    	    case 4:
    	        printf("[PAUS]\n");
    	        break;
    	    default:
    	        printf("[ERRO]\n");
    	        break;
		}
	}
}

// PRINT DECK(DECK, COLUMN, LINE, ORDER)
// Imprime o deck em determinada ordem e coordenada.
void print_deck(tp_deck *deck, int column, int line, int order) {
     tp_card *current_card;
     int cont = 0;
     
     switch(order){
        case 1: 
			current_card = deck->start;
            while (current_card != NULL) {
            	gotoxy(column, line+cont);
                print_card(current_card->naipe, current_card->valor, current_card->visible);
                current_card = current_card->next;
                cont++;
            }
            break;   
        case 2: 
			current_card = deck->end;
            while (current_card != NULL) {
            	gotoxy(column, line+cont);
                print_card(current_card->naipe, current_card->valor, current_card->visible);
                current_card = current_card->prev;
				cont++;  
            }
            break;   
        default: printf("codigo invalido");        
     }
     printf("\n");
}

#endif
