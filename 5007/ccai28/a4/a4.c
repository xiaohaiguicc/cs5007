// chenxi cai 2019-2-17
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "a4.h"

#define PRINT_DEBUG 1

// Implement the Hand and other functions in here

// Creates a Hand struct and initializes any necessary fields.
// Returns a pointer to the new Hand, which has been allocated on the heap.
Hand* createHand() {
    Hand* newHand = (Hand*)malloc(sizeof(Hand));
    newHand->num_cards_in_hand = 0;
    newHand->firstCard = NULL;
    return newHand;
}

// Adds a card to the hand.
void addCardToHand(Card *card, Hand *hand) {
    hand->num_cards_in_hand++;
    CardNode* newCardNode = malloc(sizeof(CardNode));
    newCardNode->thisCard = card;
    newCardNode->prevCard = NULL;
    newCardNode->nextCard = NULL;
    if (hand->firstCard != NULL) {
        newCardNode->nextCard = hand->firstCard;
        hand->firstCard->prevCard = newCardNode;
    }
    hand->firstCard = newCardNode;
}

// Removes a card from the hand.
Card* removeCardFromHand(Card *card, Hand *hand) {
    if (hand->num_cards_in_hand == 0) {
        return NULL;
    }
    hand->num_cards_in_hand--;
    Card* removedCard;
    CardNode* dummy = hand->firstCard;
    if (hand->firstCard->thisCard == card) {
        removedCard = hand->firstCard->thisCard;
        hand->firstCard = hand->firstCard->nextCard;
        if (hand->firstCard != NULL) {
             hand->firstCard->prevCard = NULL;
        }
        free(dummy);
        return removedCard;
    }
    while (dummy->thisCard != card && dummy != NULL) {
        dummy = dummy->nextCard;
    }
    if (dummy == NULL) {
        return NULL;
    }
    removedCard = dummy->thisCard;
    if (dummy->nextCard != NULL) {
        dummy->nextCard->prevCard = dummy->prevCard;
    }
    dummy->prevCard->nextCard = dummy->nextCard;
    free(dummy);
    return removedCard;
}

// Determines if there are any cards in the hand.
// Return 0 if the hand is empty; 1 otherwise.
int isHandEmpty(Hand* hand) {
    if (hand->num_cards_in_hand != 0) {
        return 1;
    }
    return 0;
}

// Destroys the hand, freeing any memory allocated for it.
void destroyHand(Hand* hand) {
    CardNode* current = hand->firstCard;
    while (current != NULL) {
        hand->firstCard = hand->firstCard->nextCard;
        free(current->thisCard);
        free(current);
        current = hand->firstCard;
    }
    free(hand);
}

// Given a players hand, a suit,
// If the player have a card of the same suit?
int handHasSuit(Hand *hand, Suit newSuit) {
    CardNode *dummy = hand->firstCard;
    while (dummy != NULL) {
        if (dummy->thisCard->suit == newSuit) {
            return 1;
        }
        dummy = dummy->nextCard;
    }
    return 0;
}

// Given a lead card, a players hand, and the card the player wants
// to play, is it legal?
// If the player has a card of the same suit as the ledCard, they
// must play a card of the same suit.
// If the player does not have a card of the same suit, they can
// play any card.
int isLegalMove(Hand *hand, Card *leadCard, Card *playedCard) {
    if (leadCard->suit == playedCard->suit) {
        return 1;
    }
    if (handHasSuit(hand, leadCard->suit) == 0) {
        return 1;
    }
    return 0;
}


// Given two cards that are played in a hand, which one wins?
// If the suits are the same, the higher card value wins.
// If the suits are not the same, player 1 wins, unless player 2 played trump.
// Returns 1 if the person who led won, 0 if the person who followed won.
int whoWon(Card *leadCard, Card *followedCard, Suit trump) {
    if (leadCard->suit == followedCard->suit) {
        if (leadCard->name > followedCard->name) {
            return 1;
        } else {
              return 0;
          }
     } else {
        if (followedCard->suit ==trump) {
           return 0;
         } else {
               return 1;
           }
    }
}
