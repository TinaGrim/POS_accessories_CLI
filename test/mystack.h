#include <string>
typedef struct Item {
  std::string name;
  std::string size;
  unsigned int ID;
  unsigned int price;
  unsigned int qty;
  unsigned int Amount;
} Item;
struct ASC {
  Item item;
  ASC* next;
};

struct ASCstack {
  int size;
  ASC* top;
};
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
// Pop
Item* pop(ASCstack* s) {

  Item tempItem;

  if (isEmpty(s)) {
    return nullptr;
  }

  ASC* temp = s->top;

  tempItem = temp->item;

  s->top = temp->next;

  delete temp;

  s->size--;

  return nullptr;
}

Item* getItemAt(ASCstack* s, const int n) {

  if (isEmpty(s)) {
    return nullptr;
  }
  ASC* temp = s->top;

  int i = 0;
  while (temp != nullptr && s->size - 1 >= n) {
    if (n == i) {
      return &temp->item;
    }
    temp = temp->next;
    i++;
  }

  return nullptr;
}

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
bool updateProduct(ASCstack* s, int updateID, std::string name, int price) {

  if (isEmpty(s)) {
    return false;
  }

  ASC* temp = s->top;

  while (temp != nullptr) {

    if (temp->item.ID == updateID) {

      // name
      temp->item.name = name;
      temp->item.price = price;

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

      if (previous == nullptr) {
        s->top = current->next;
      } else {
        previous->next = current->next;
      }

      delete current;

      s->size--;

      return true;
    }

    previous = current;
    current = current->next;
  }
  return false;
}
