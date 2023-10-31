#include <bits/stdc++.h>

using namespace std;

/*
 * Given a set of transactions between users, each transaction denotes the payer -> payee relation. The amount paid
 * is in terms of percentage. A->B 20%
 * This means A paid 20% of whatever he had to B.
 * Input: A has $100
 * List of transactions: A->B 20%, A->C 40%, B->D 30%, C->D 50%, C->F 20%, B->E 50%, D->E 25%, F->G 10%, E->C 50%
 *
 * Part 1) Print final balances of all users.
 * Part 2) Introduce an ability to delete a transaction given the user and transaction’s number wrt user.
 * User Y wants to delete their nth transaction. What is the balance of user X?
 * Eg: User B wants to delete their 2nd transaction (B->D 30%). What is the balance of C?
 * Ask the candidate to discuss/code some other solution. Possibly optimised.
 */

class Triplet {
public:
    char src;
    char dest;
    double pct;
    Triplet(char source, char destination, double percentage) {
        src = source;
        dest = destination;
        pct = percentage;
    }
};

class Account {
public:
    double balance;
    vector<int> own_transactions;
    Account (int b) {
        balance = b;
    }
};

int main() {
    unordered_map<char, Account> m = {
        {'A', Account(100)}, {'B', Account(0)}, {'C', Account(0)},
        {'D', Account(0)}, {'E', Account(0)}, {'F', Account(0)},
        {'G', Account(0)}};

    vector<Triplet> transactions = { Triplet('A', 'B', 0.20),
         Triplet('A', 'C', 0.40), Triplet('B', 'D', 0.30),
         Triplet('C', 'D', 0.50), Triplet('C', 'F', 0.20),
         Triplet('B', 'E', 0.50), Triplet('D', 'E', 0.25),
         Triplet('F', 'G', 0.10), Triplet('E', 'C', 0.50)};

    for (int i = 0; i < transactions.size(); i++) {
        char src = transactions[i].src;
        Account a(m.at(src));
        a.own_transactions.push_back(i);
    }

    vector<pair<char, int>> deletions = {{'B', 1}};
    // cout << m['B'].own_transactions.size() << '\n';
    vector<bool> isDeletedArray(transactions.size());
    for (auto& p : deletions) {
        char person = p.first;
        Account a(m.at(person));

        int transaction_number = p.second;
        int transaction_index = a.own_transactions[transaction_number - 1];
        isDeletedArray[transaction_index] = true;
    }

    for (int i = 0; i < isDeletedArray.size(); i++) {
        if (isDeletedArray[i]) cout << i << '\n';
    }

    for (int i = 0; i < transactions.size(); i++) {
        if (isDeletedArray[i]) continue;
        double pct = transactions[i].pct;
        char src = transactions[i].src;
        char dest = transactions[i].dest;
        double original = m.at(src).balance;
        m.at(src).balance = (1 - pct) * m.at(src).balance;
        m.at(dest).balance = m.at(dest).balance + pct * original;
    }

    double sum = 0;
    for (auto& p : m) {
        cout << p.first << ' ' << p.second.balance << '\n';
        sum += p.second.balance;
    }
    cout << sum;

    return 0;
}
