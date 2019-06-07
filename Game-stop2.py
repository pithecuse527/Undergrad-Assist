
"""
README

1. Class & Method naming rules
    - The name of the method can be read by sentence.
      For example, if the giveCard() method gives the card to a player,
      you can use giveCard(to_player) and similar with this sentence -> "Give card to player"
      This might come in handy when you want to know the exact role of the method.
      This is only applied to regular methods. Not to constructor, getter and setter.
      
    - As you know and learned, the name of the class is set to suit their roles.
    
    - Classes are defined from little one to larger one.
      (Card -> Deck -> Player -> CardManager)
    
    - The role of objects must be clear. For example a card object is just a single card.
      It can show its suit or rank, but it cannot compare with another card itself.
    
2. Role of Classes (+ checker() func.)
    ## Pay attention to encapsulation. I think you might already know about this.
    ## All the classes have an encapsulation attribute.
    
    - Card : Simply just a card. It can represent its attributes.
             Attributes can be set by using setter.
             
    - Deck : The deck is a set of cards. The set of cards is implemented by using stack and it will
             be the deck's attribute. Also, the deck object can print it's all cards.
    
    - Player : Player object can recieve cards from the card manager. And player will not
               do anything about checking cards. Checking whether two ranks are equal or not
               is not adequate for this object.
    
    - CardManager : The CardManager only cares about card management.
                    (giving cards, shuffling deck, removing & adding cards to deck)
                    Judging the winner will be done by checker() function. Not this method.
    
    - checker : Given the rules, the checker will find the winner.
    
3. checker() function will operate according to the contents of PPT. However it will work in a slightly 
   modified order. If you look at the rules of the game as I mentioned below, it will help you to understand.
   
   page4 second rule -> page4 first rule -> page4 third rule -> page2 first rule -> 
   page2 second rule -> page3 first rule -> page3 seond rule
   
   
4. Stack
    - A deck can be implemented by using stack since the manager will give the player top cards.
    - Player's cards also can be done by stack.
    
5. This only deals with two players. If you want to make players more than two, 
   add them and try to use checking() several times. I guess you can implement the game 
   in tournament mode.

It seems complicated and different from yours. So try using the code that might helps you.
There are many comments on why I made like this. Encapsulation, Making more definite classes, 
Overriding and Inheriting proper class are very crucial things in programming.
I hope this helps you. Good luck.

07/June/2019
JHG

"""

import random

## All the indices have each value.
suits = [("Clubs", 1), ("Diamonds", 4), ("Hearts", 9), ("Spades", 16)]
ranks = [("Ace", 1), ("2", 2), ("3", 3), ("4", 4), ("5", 5), ("6", 6), ("7", 7),
         ("8", 8), ("9", 9), ("10", 10), ("Jack", 11), ("Queen", 12), ("King", 13)]


## Todo1 : encapsulation (Done)
## Todo4 : encapsulation naming (Done)
class Card:
    
    def __init__(self):
        self.__suit = None
        self.__rank = None
        
    def getSuit(self):
        return self.__suit
        
    def getRank(self):
        return self.__rank
    
    def setSuitRank(self, suit, rank):
        self.__suit = suit
        self.__rank = rank


class Deck:
    ## Pay attention to the difference between Deck and Cards
    
    def __init__(self):
        self.__cards = []
        
    def getCards(self):
        return self.__cards
        
    def setCards(self):             # suits & ranks are defined as global
        for suit in suits:
            for rank in ranks:       
                tmp_card = Card()
                tmp_card.setSuitRank(suit, rank)
                self.getCards().append(tmp_card)
                
    def showCards(self):
        for card in self.getCards():
            print(card.getSuit()[0] + ' ' + card.getRank()[0])


class Player:
    
    def __init__(self, index):
        self.__index = index
        self.__cards = []
        
    def takeThis(self, card):
        # Take this card (work as setter)
        self.__cards.append(card)
    
    def getCards(self):
        return self.__cards
        
    def showMyCards(self):
        for card in self.__cards:
            print("player" + str(self.getMyIndex()) + ' : ' + card.getSuit()[0] + ' ' + card.getRank()[0])
    
    def getMyIndex(self):
        return self.__index
        


# Todo2 : inherit the class Deck (Done)
class CardManager(Deck):
    
    def __init__(self, given_deck = None):
        self.__deck = given_deck
        
        if self.thereIsNoDeckToHandle():        # If there is no deck to handle, notify it.
            print("There is no deck to handle!")
        
    def getDeck(self):
        return self.__deck
        
    def setDeck(self, given_deck):
        if self.__deck:
            print("The previous deck is removed. Using a new deck.")
        self.__deck = given_deck
        print("Deck is set")
        
    ## Todo3 : super? -> yes (Done)
    ## overriding
    def getCards(self):
        ## Works same with Deck's getCards() method
        ## To use shuffleTheDeck() properly, override the method
        return self.getDeck().getCards()    ## In this case, getCards() is a method of super
    
    def shuffleTheDeck(self):
        ## Shuffle the deck
        random.shuffle(self.getCards())
    
    def giveCard(self, to_player):
        ## Give card to player
        tmp_card = self.getCards().pop()
        to_player.takeThis(tmp_card)
        
    def thereIsNoDeckToHandle(self):
        if not self.getDeck():
            return True
        return False
        
    def add(self, thisCard):
        ## Add this card
        self.getCards().append(thisCard)
        self.shuffleTheDeck()   # Since appending will only add a card to the top, shuffle it.

    def remove(self, thisCard):
        ## Remove this card
        self.getCards().remove(thisCard)


def checker(p1, p2):
    
    p1_c1 = p1.getCards()[0]        # player1-firstCard
    p1_c2 = p1.getCards()[1]        # player1-secondCard
    p2_c1 = p2.getCards()[0]        # player2-firstCard
    p2_c2 = p2.getCards()[1]        # player2-secondCard
    
    
    ## All of these are tuple
    ## Indexing int from tuple is required before calculating
    ## Indexing 0th stands for String
    ## Indexing 1st stands for Int
    p1_c1_rank = p1_c1.getRank()        # player1-firstCard-rank
    p1_c2_rank = p1_c2.getRank()        # player1-secondCard-rank
    p2_c1_rank = p2_c1.getRank()        # player2-firstCard-rank
    p2_c2_rank = p2_c2.getRank()        # player2-secondCard-rank
    
    p1_c1_suit = p1_c1.getSuit()        # player1-firstCard-suit
    p1_c2_suit = p1_c2.getSuit()        # player1-secondCard-suit
    p2_c1_suit = p2_c1.getSuit()        # player2-firstCard-suit
    p2_c2_suit = p2_c2.getSuit()        # player2-secondCard-suit
    
    p1_rm_rs = (p1_c1_rank[1] + p1_c2_rank[1]) % 10       # player1-rightMostOf-rankSum
    p2_rm_rs = (p2_c1_rank[1] + p2_c2_rank[1]) % 10       # player2-rightMostOf-rankSum
    
    p1_sS = p1_c1_suit[1] + p1_c2_suit[1]         # player1-suitSum
    p2_sS = p2_c1_suit[1] + p2_c2_suit[1]         # player2-suitSum
    
    
    ## 1. Players have same ranks of 2 cards (PPT p.4)
    if p1_c1_rank == p1_c2_rank or p2_c1_rank == p2_c2_rank:
        if p1_c1_rank == p1_c2_rank and p2_c1_rank != p2_c2_rank:
            return p1
        elif p1_c1_rank != p1_c2_rank and p2_c1_rank == p2_c2_rank:
            return p2
        else:
            if p1_c1_rank == ("Ace", 1):    # Aces are exceptionally strong
                return p1
            elif p2_c1_rank == ("Ace", 1):
                return p2
            
            if p1_c1_rank < p2_c1_rank:     # It does not matter whether using c1 or c2
                return p2
            elif p1_c1_rank == p2_c1_rank:
                if p1_sS < p2_sS:
                    return p2
        return p1
    
    ## 2. Compare rightmost digit of the sum of 2 cards (PPT p.2)
    ## The rules of PPT p.2 and p.3 have several common things
    if p1_rm_rs < p2_rm_rs:
        return p2
    elif p1_rm_rs == p2_rm_rs:
        if p1_sS < p2_sS:
            return p2
            
        ## 3. Players have same rightmost digit & sum of suits (PPT p.3)
        elif p1_sS == p2_sS:
            ## Setting largest rank card
            p1_lr_card = p1_c1      # player1-largestRank-card
            if p1_c1_rank[1] < p1_c2_rank[1]:
                p1_lr_card = p1_c2
            
            p2_lr_card = p2_c1       # player2-largestRank-card
            if p2_c1_rank[1] < p2_c2_rank[1]:
                p2_lr_card = p2_c2
            
                
            ## Comparing card's rank and suit
            p1_lr_card_rank = p1_lr_card.getRank()      # player1-largestRank-card's-rank
            p1_lr_card_suit = p1_lr_card.getSuit()      # player1-largestRank-card's-suit
            p2_lr_card_rank = p2_lr_card.getRank()      # player2-largestRank-card's-rank
            p2_lr_card_suit = p2_lr_card.getSuit()      # player2-largestRank-card's-suit
            
            if p1_lr_card_rank[1] < p2_lr_card_rank[1]:
                return p2
                
            ## 4. Players have same rightmost digit & sum of suits & largest rank (PPT p.3)
            elif p1_lr_card_rank == p2_lr_card_rank:
                if p1_lr_card_suit[1] < p2_lr_card_suit[1]:
                    return p2
    return p1
    

dec1 = Deck()
dec1.setCards()
# dec1.showCards()

# print()
# print()

card_manager1 = CardManager()
card_manager1.setDeck(dec1)
card_manager1.shuffleTheDeck()
# dec1.showCards()

p1 = Player(1)
p2 = Player(2)

card_manager1.giveCard(p1)
card_manager1.giveCard(p1)
card_manager1.giveCard(p2)
card_manager1.giveCard(p2)

print()
print()

p1.showMyCards()
p2.showMyCards()

print()
print()

res = checker(p1, p2)
print("Winner -> Player" + str(res.getMyIndex()))
