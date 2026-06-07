#include "../include/mystack.h"
#include "../include/Items.h"
#include <string>

// Create Empty Stack
ASCstack* createEmptyStack() {
  ASCstack* s = new ASCstack;

  s->size = 0;
  s->top = nullptr;

  return s;
}

// Check Empty
bool isEmpty(ASCstack* s) { return s->top == nullptr; }

// Push
void push(ASCstack* s, Item item) {

  ASC* newNode = new ASC;

  newNode->item = item;
  newNode->next = s->top;

  s->top = newNode;

  s->size++;
}

void push(ASCstack* s, Item item, unsigned int qty, unsigned Amount) {

  ASC* newNode = new ASC;

  newNode->item = item;
  newNode->item.qty = qty;
  newNode->item.Amount = Amount;

  newNode->next = s->top;

  s->top = newNode;

  s->size++;
}
void push(ASCstack* s, std::string name, std::string size, unsigned int ID,
          unsigned int price, unsigned int qty, unsigned Amount) {

  ASC* newNode = new ASC;

  newNode->item.name = name;
  newNode->item.size = size;
  newNode->item.ID = ID;
  newNode->item.price = price;
  newNode->item.qty = qty;
  newNode->item.Amount = Amount;

  newNode->next = s->top;

  s->top = newNode;

  s->size++;
}
bool checkExist(ASCstack* s, int ID) {
  if (isEmpty(s)) {
    return false;
  }
  ASC* temp = s->top;
  while (temp != nullptr) {
    if (temp->item.ID == ID) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
// Pop
Item* pop(ASCstack* s) {

  Item tempItem;

  if (isEmpty(s)) {
    return nullptr;
  }

  ASC* temp = s->top;
  tempItem = temp->item;
  s->top = temp->next;

  s->size--;

  return &temp->item;
}

Item* getItemAt(ASCstack* s, const int ID) {

  if (isEmpty(s) || ID < 0 || ID >= s->size) {
    return nullptr;
  }
  ASC* temp = s->top;

  int i = 0;
  while (temp != nullptr && i < ID) {

    temp = temp->next;
    i++;
  }

  return &temp->item;
}
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
Item* searchProduct(ASCstack* s, int searchID) {

  if (isEmpty(s)) {
    return nullptr;
  }

  ASC* temp = s->top;

  while (temp != nullptr) {
    if (temp->item.ID == searchID) {
      return &temp->item;
    }

    temp = temp->next;
  }
  return nullptr;
}

// UPDATE
bool updateProduct(ASCstack* s, unsigned int updateID, std::string name,
                   std::string size, unsigned int price, unsigned int qty) {

  if (isEmpty(s)) {
    return false;
  }

  ASC* temp = s->top;

  while (temp != nullptr) {

    if (temp->item.ID == updateID) {

      // name
      temp->item.name = name;
      temp->item.ID = updateID;
      temp->item.price = price;
      temp->item.qty++;
      temp->item.size = size;
      temp->item.Amount = temp->item.price * temp->item.qty;

      return true;
    }

    temp = temp->next;
  }
  return false;
}

// DELETE
bool deleteProduct(ASCstack* s, int deleteID) {

  if (isEmpty(s)) {
    return false;
  }

  ASC* current = s->top;
  ASC* previous = nullptr;

  while (current != nullptr) {

    if (current->item.ID == deleteID) {

      if (current->item.qty != 1) {
        current->item.qty--;
        current->item.Amount = current->item.price * current->item.qty;
      } else {
        if (previous == nullptr) {
          s->top = current->next;
        } else {
          previous->next = current->next;
        }
        delete current;

        s->size--;
        return true;
      }
    }

    previous = current;
    current = current->next;
  }
  return false;
}
int Summation(ASCstack* c) {
  int total = 0;
  ASC* temp = c->top;
  while (temp != nullptr) {
    total += temp->item.qty * temp->item.price;
    temp = temp->next;
  }
  return total;
}
float tax(float total) {
  // expected rate is 10%
  return total * 0.1;
}
