#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

typedef struct Login {
  std::string name;
  int id;
  char gender;
  int age;
  int phone;
  std::string email;
  Login* next;
} Login;
Login* createEmpty();
class LoginManager {
private:
  Login* login;
  Login* head;
  Login* tail;
  int size;

public:
  LoginManager();
  Login* getAccountFrom(std::string filename);
  void append(std::string name, int id, char gender, int age, int phone,
              std::string email);
  bool isEmpty();
  bool isExistsEmail(std::string email);
  bool saveLast(std::string filename);
};
