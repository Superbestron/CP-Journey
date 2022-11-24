#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int solution(int cutoffScore, int scoresLength, const int scores[]) {
    int total = 0, sum = 0, i = 0, j = 0, diff = 0;
    while (j < scoresLength) {
        sum += scores[j++];
        diff++;
        if (sum < cutoffScore) {
            total += diff;
        } else {
            while (i < j) {
                sum -= scores[i++];
                diff--;
                if (sum < cutoffScore) {
                    total += diff;
                    break;
                }
            }
        }
    }
    return total;
}

int main(){

    ios_base::sync_with_stdio(false);
    int cutoffScore,scoresLength,data;
    cin>>cutoffScore>>scoresLength;
    string buffer;
    getline(cin, buffer);
    getline(cin, buffer);
    istringstream iss(buffer);

    int scores[scoresLength];
    int i = 0;
    while (iss >> data)
        scores[i++] = data;

    cout << solution(cutoffScore,scoresLength, scores);
}
