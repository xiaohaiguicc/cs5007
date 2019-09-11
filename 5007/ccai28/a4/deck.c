// chenxi cai 2019-2-17
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include "a4.h"

#define PRINT_DEBUG 1

// Put your deck functions in here

//----------------------------------------
// Card functions
//----------------------------------------

// Creates a card, initializing the suit and name to that specified.
// Returns a pointer to the new card, which has beel allocated on the heap.
// It is the responsibility of the caller to call destroyCard()
// when it is done with the Card.
Card* createCard(Suit newSuit, Name newName) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard->name = newName;
    newCard->suit = newSuit;
    newCard->value = newName;
}

// Destroys the card, freeing any memory allocated for the card.
void destroyCard(Card* card) {
    free(card);
}

// Creates the deck, initializing any fields necessary.
// Returns a pointer to the deck, which has been allocated on the heap.
Deck* createDeck() {
    Deck* newDeck = malloc(sizeof(Deck));
    newDeck->topCard = -1;
    return newDeck;
}

// Adds a card to the top of the deck.
// Returns a pointer to the deck.
Deck* pushCardToDeck(Card* newCard, Deck* stackOfDeck) {
    if (stackOfDeck->topCard == NUM_CARDS_IN_DECK - 1) {
        return stackOfDeck;
    }
    stackOfDeck->topCard++;
    stackOfDeck->cards[stackOfDeck->topCard] = newCard;
    return stackOfDeck;
}

// Shows the top card, but does not remove it from the stack.
// Returns a pointer to the top card.
Card* peekAtTopCard(Deck* stackOfDeck) {
    if (stackOfDeck->topCard == -1) {
        return NULL;
    }
    return stackOfDeck->cards[stackOfDeck->topCard];
}

// Removes the top card from the deck and returns it.
// Returns a pointer to the top card in the deck.
Card* popCardFromDeck(Deck* stackOfDeck) {
    if (stackOfDeck->topCard == -1) {
        return NULL;
    }
    return stackOfDeck->cards[stackOfDeck->topCard--];
}

// Determines if the deck is empty.
// Returns 0 if the Deck has any cards; 1 otherwise.
int isDeckEmpty(Deck* stackOfDeck) {
    if (stackOfDeck->topCard == -1) {
        return -1;
    } else {
         return 0;
    }
}

// Destroys the deck, freeing any memory allocated
// for this deck (the cards and the deck).
void destroyDeck(Deck* stackOfDeck) {
    for (int i = 0; i <= stackOfDeck->topCard; i++) {
        destroyCard(stackOfDeck->cards[i]);
    }
    free(stackOfDeck);
}

// Create a Deck for this game, and add any
// needed cards to the deck.
// Return a pointer to the deck to be used for the game
Deck* populateDeck() {
    Deck* deck = createDeck();
    Suit s;
    Name n;
    for (s = HEARTS; s <= DIAMONDS; s++) {
        for (n = NINE; n<= ACE; n++) {
            Card* card = createCard(s, n);
            deck = pushCardToDeck(card, deck);
        }
    }
    return deck;
}

// Shuffle the deck.
// Put them in a random order.
void shuffle(Deck *aDeck) {
    srand(time(NULL));
    for (int i = 0; i < NUM_CARDS_IN_DECK; i++) {
        int j = rand() % NUM_CARDS_IN_DECK;
        Card* temp = aDeck->cards[i];
        aDeck->cards[i] = aDeck->cards[j];
        aDeck->cards[j] = temp;
    }
}

// Given a deck (assume that it is already shuffled),
// take the top card from the deck and alternately give
// it to player 1 and player 2, until they both have
// NUM_DECKS_IN_HAND.
void deal(Deck *aDeck, Hand *p1hand, Hand *p2hand) {
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        Card* cardOne = popCardFromDeck(aDeck);
        Card* cardTwo = popCardFromDeck(aDeck);
        addCardToHand(cardOne, p1hand);
        addCardToHand(cardTwo, p2hand);
    }
}
