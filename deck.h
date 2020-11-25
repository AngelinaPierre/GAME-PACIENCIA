#ifndef DECK
#define DECK

#include<stdio.h>
#include<stdlib.h>

// OBS: Os naipes estão separados por paridade de números e pela cor, assim, os naipes de mesma cor possuem mesma paridade de número.

#define	COPAS 1;
#define ESPADAS 2;
#define OUROS 3;
#define PAUS 4;

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

// APPEND DECK(DECK, NAIPE, VALOR):
// Adiciona a carta ao fim do deck
int append_deck(tp_deck *deck, int naipe, int valor){
	tp_card *new_card;
	new_card = alloc_card();
	if (!new_card) return 0;
	new_card->naipe = naipe;
	new_card->valor = valor;
	
	// Verifica se o deck está vazio e se o valor da carta é o Rei.
	if((deck->start == NULL) && (deck->end == NULL) && (new_card->valor == REI)){
		new_card->next = NULL;
		new_card->prev = NULL;
		deck->start = deck->end = new_card;
	} 
	// Verifica se a carta possui naipe de cor invertida e valor antecessor à última carta do deck.
	else if(new_card->naipe%2 != deck->end->naipe%2 && new_card->valor == deck->end->valor-1){
		new_card->next = NULL;
		new_card->prev = deck->end;
		deck->end->next = new_card;
		deck->end = new_card;
	} else{
		free(new_card);
		return 0;
	}
	
	return 1;
}

// APPEND SUPERIOR DECK(DECK, NAIPE, VALOR):
// Adiciona a carta ao fim do deck superior
int append_superior_deck(tp_deck *deck, int naipe, int valor){
	tp_card *new_card;
	new_card = alloc_card();
	if (!new_card) return 0;
	new_card->naipe = naipe;
	new_card->valor = valor;
	
	// Verifica se o deck está vazio e se o valor da carta é o Ás.
	if((deck->start == NULL) && (deck->end == NULL) && (new_card->valor == ACE)){
		new_card->next = NULL;
		new_card->prev = NULL;
		deck->start = deck->end = new_card;
	} 
	// Verifica se a carta possui mesmo naipe e valor sucessor à última carta do deck.
	else if(new_card->naipe == deck->end->naipe && new_card->valor == deck->end->valor+1){
		new_card->next = NULL;
		new_card->prev = deck->end;
		deck->end->next = new_card;
		deck->end = new_card;
	} else{
		free(new_card);
		return 0;
	}
	
	return 1;
}

// SEARCH CARD(DECK, NAIPE, VALOR):
// Procura a carta no deck com determinado valor.
tp_card* search_card(tp_deck *deck, int naipe, int valor){   
  tp_card *current_card;
  current_card = deck->start;
  while((current_card != NULL) && (current_card->valor != valor) && (current_card->naipe != naipe)){ 
        current_card = current_card->next;}
  return current_card;
}

// TRANSFER DECK(DECK REMETENTE, DECK DESTINATÁRIO, NAIPE, VALOR):
// Transfere determinada fração do deck ou o deck completo para outro local.
int transfer_deck(tp_deck *deck_remetente, tp_deck *deck_destinatario, int naipe, int valor){
	tp_card *current_card;
	tp_card *temp_card;
	
	current_card = search_card(deck_remetente, naipe, valor);
	if(!current_card){
		return 0;
	}
	// Verifica se a sequência é possível de ser transferida
	temp_card = current_card;
	// Procura por alguma irregularidade. Caso não haja, retorna a possibilidade.
	while(!temp_card->next){
		if(temp_card->naipe%2 == temp_card->next->naipe%2 && temp_card->valor != temp_card->next->valor+1){
			return 0;
		} else{
			temp_card = temp_card->next;
		}
	}
	// Verifica se a carta é Rei e se o deck destinatário é vazio.
	if(current_card->valor == REI && deck_destinatario->start == NULL){
		// Guarda a última carta do deck em uma variável temporária.
		temp_card = deck_remetente->end;
		deck_remetente->end = current_card->prev;
		// Transfere o fragmento para o deck destinatário.
		if(!current_card->prev){
			current_card->prev->next == NULL;
		}
		deck_destinatario->start = current_card;
		deck_destinatario->end = temp_card;
	}
	// Verifica se a carta possui naipe de cor invertida e valor antecessor à última carta do deck.
	else if(current_card->naipe%2 != deck_destinatario->end->naipe%2 && current_card->valor == deck_destinatario->end->valor-1){
		// Guarda a última carta do deck em uma variável temporária.
		temp_card = deck_remetente->end;
		deck_remetente->end = current_card->prev;
		// Transfere o fragmento para o deck destinatário.
		if(!current_card->prev){
			current_card->prev->next == NULL;
		}
		current_card->prev = deck_destinatario->end;
		deck_destinatario->end->next = current_card;
		deck_destinatario->end = temp_card;
	} else{
		return 0;
	}
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

#endif
