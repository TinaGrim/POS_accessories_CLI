#include "../include/login.h"
#include <ctime>
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif // _WIN32
#include <string>

Login* createEmpty() {

  Login* login = new Login();
  login->name = "";
  login->id = 0;
  login->gender = '\0';
  login->age = 0;
  login->email = "";
  login->next = nullptr;
  return login;
};
LoginManager::LoginManager() {
  login = createEmpty();
  head = nullptr;
  tail = nullptr;
  size = 0;
}
void LoginManager::append(std::string name, int id, char gender, int age,
                          int phone, std::string email) {
  Login* newLogin = new Login();
  newLogin->name = name;
  newLogin->id = id;
  newLogin->gender = gender;
  newLogin->age = age;
  newLogin->phone = phone;
  newLogin->email = email;
  if (head == nullptr) {
    head = newLogin;
    tail = newLogin;
    size++;
  } else {
    tail->next = newLogin;
    tail = newLogin;
    size++;
  }
}
bool LoginManager::isEmpty() { return head == nullptr; }
bool LoginManager::isExistsEmail(std::string email) {
  Login* tem = head;
  while (tem != nullptr) {
    if (tem->email == email) {
      return true;
    }
    tem = tem->next;
  }
  return false;
}

Login* LoginManager::getAccountFrom(std::string filename) {
  std::ifstream infile;
  std::string buffer;
  std::string line;
  int count = 0;
  infile.open(filename);
  Login* login = createEmpty();

  /*
    extract by each line
  */
  while (getline(infile, line)) {
    if (line.empty())
      continue;

    std::stringstream ss(line);

    getline(ss, buffer, ',');
    login->name = buffer;

    getline(ss, buffer, ',');
    login->id = std::stoi(buffer);

    getline(ss, buffer, ',');
    login->gender = buffer[0];

    getline(ss, buffer, ',');
    login->age = std::stoi(buffer);

    getline(ss, buffer, ',');
    login->phone = std::stoi(buffer);

    getline(ss, buffer, ',');
    login->email = buffer;

    append(login->name, login->id, login->gender, login->age, login->phone,
           login->email);
  }
  infile.close();

  return head;
}
bool LoginManager::saveLast(std::string filename) {

  std::ofstream file(filename, std::ios::app);
  if (file.is_open()) {
    char c = ',';
    time_t now;
    std::time(&now);
    file << tail->name << c << tail->id << c << tail->gender << c << tail->age
         << c << tail->phone << c << tail->email << c << ctime(&now);
    file.close();
    return true;
  }
  return false;
}
