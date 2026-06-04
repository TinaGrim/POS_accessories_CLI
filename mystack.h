#ifndef MYSTACK_H
#define MYSTACK_H

#include "Items.h"
#include <iostream>
#include <string>
struct ASC {
  Item item;
  ASC* next;
};

struct ASCstack {
  int size;
  ASC* top;
};

// Create Empty Stack
ASCstack* createEmptyStack();

// Check Empty
bool isEmpty(ASCstack* s);

// Push
void push(ASCstack* s, Item item);

void push(ASCstack* s, Item item, unsigned int qty, unsigned Amount);
void push(ASCstack* s, std::string name, std::string size, unsigned int ID,
          unsigned int price, unsigned int qty, unsigned Amount);

bool checkExist(ASCstack* s, int ID);
// Pop
Item* pop(ASCstack* s);

// Get Item At
Item* getItemAt(ASCstack* s, const int n);

// READ
// void displayProducts(ASCstack* s) {
//
//   if (isEmpty(s)) {
//     return;
//   }
//
//   ASC* temp = s->top;
//
//
//   while (temp != nullptr) {
//
//
//     temp = temp->next;
//   }
// }

// SEARCH
Item* searchProduct(ASCstack* s, int searchID);

// UPDATE
bool updateProduct(ASCstack* s,unsigned int updateID, std::string name,std::string size, unsigned int price,unsigned int qty);

// DELETE
bool deleteProduct(ASCstack* s, int deleteID);
int Summation(ASCstack* c);
float tax(float total);
#endif // !MYSTACK_H
