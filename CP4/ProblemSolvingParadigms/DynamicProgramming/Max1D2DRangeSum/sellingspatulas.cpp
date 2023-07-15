//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    int n, time;
//    double sales;
//    cin >> n;
//    while (n != 0) {
//        int prev_time = -1;
//        int best_prev_time = -1, best_curr_time = -1, best_duration = 0;
//        double curr, maxi = 0;
//        for (int i = 0; i < n; i++) {
//            cin >> time >> sales;
//            curr += sales - (time - prev_time) * 0.08;
//            prev_time = time;
//            double temp2 = sales - 0.08;
//
//            if (curr < 0) {
//                curr = 0;
//            }
//
//            // better to continue running sum
//            if (curr > temp2) {
//                if (curr > maxi || (curr == maxi && (time - best_prev_time) <= best_duration)) {
//                    best_duration = time - best_prev_time;
//                    maxi = curr;
//                    best_curr_time = time;
//                }
//            } else { // better to start from here
//                if (temp2 < 0) {
//                    continue;
//                }
//                if (temp2 >= maxi) {
//                    best_duration = 0;
//                    maxi = curr = temp2;
//                    best_prev_time = time;
//                    best_curr_time = time;
//                }
//            }
//        }
//        if (maxi < 0.00000001) {
//            cout << "no profit" << endl;
//        } else {
//            cout << maxi << ' ' << best_prev_time << ' ' << best_curr_time << endl;
//        }
//        cin >> n;
//    }
//}