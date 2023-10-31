#include <bits/stdc++.h>
#define MAX 100

void tokenize(const std::string &input, std::vector<std::string> &tokens) {
  std::vector<std::string> temp;
  std::istringstream iss(input);
  std::string token;

  std::unordered_set<char> operators = {'+', '-', '*', '/', '%', '=', '<', '>', '{', '}', '(', ')', ';'};

  while (iss >> token) {
    int idx = 0;
    for (int i = 0; i < token.size(); i++) {
      if (operators.count(token[i])) {
        if (i - idx > 0) temp.push_back(token.substr(idx, i - idx));
        temp.push_back(token.substr(i, 1));
        idx = i + 1;
      }
    }
    if (idx < token.size()) temp.push_back(token.substr(idx));
  }

  // Join tokens with spaces to separate operators and operands
  for (const std::string &t : temp) {
    if (tokens.empty() || t == ";" || t == "(" || t == ")") {
      tokens.push_back(t);
    } else if (t == "=") {
      if (!tokens.empty() && tokens.back() == "=" || tokens.back() == "<" || tokens.back() == ">") {
        // Combine consecutive "=" into "=="
        tokens.back() += "=";
      } else {
        tokens.push_back(t);
      }
    } else {
      tokens.push_back(t);
    }
  }
}

class Deque {
 private:
  int arr[MAX];
  int front;
  int rear;
  int size;
 public:
  explicit Deque(int size) : front(-1), size(size) {}
  void push_front(int key) {
    if (is_full()) {
      std::cerr << "Deque Full!\n";
      return;
    }
    if (is_empty()) {
      front = 0;
      rear = 0;
    } else {
      front = (size + front - 1) % size;
    }
    arr[front] = key;
  }
  void push_back(int key) {
    if (is_full()) {
      std::cerr << "Deque Full!\n";
      return;
    }
    if (is_empty()) {
      front = 0;
      rear = 0;
    } else {
      rear = (rear + 1) % size;
    }
    arr[rear] = key;
  }
  void pop_front() {
    if (is_empty()) {
      std::cerr << "Deque Empty!\n";
      return;
    }
    if (front == rear) {
      front = -1;
    } else {
      front = (front + 1) % size;
    }
  }
  void pop_back() {
    if (is_empty()) {
      std::cerr << "Deque Empty!\n";
      return;
    }
    if (front == rear) {
      front = -1;
    } else {
      rear = (size + rear - 1) % size;
    }
  }
  int top() {
    return arr[front];
  }
  int back() {
    return arr[rear];
  }
  [[nodiscard]] bool is_full() const {
    return (front == 0 && rear == size - 1) || front == rear + 1;
  }
  [[nodiscard]] bool is_empty() const {
    return front == -1;
  }
};

int main() {
//  std::string sourceCode = "procedure main{print 0;if(x==0){x=1};";
//  std::vector<std::string> tokens;
//  tokenize(sourceCode, tokens);
//
//  for (const std::string &token : tokens) {
//    std::cout << "Token: " << token << std::endl;
//  }

  Deque dq(5);

  // Function calls
  std::cout << "Insert element at rear end: 5\n";
  dq.push_back(5);

  std::cout << "insert element at rear end: 10\n";
  dq.push_back(10);

  std::cout << "get rear element " << dq.back() << std::endl;

  dq.pop_back();
  std::cout << "After delete rear element new rear become " << dq.back() << std::endl;

  std::cout << "inserting element at front end: 15\n";
  dq.push_front(15);

  std::cout << "get front element " << dq.top() << std::endl;

  dq.pop_front();

  std::cout << "After delete front element new front become " << dq.top() << std::endl;

  return 0;
}
