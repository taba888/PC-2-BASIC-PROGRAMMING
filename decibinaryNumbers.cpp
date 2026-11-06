
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

const int MAX_POS = 20;
const ull INF = 10000000000000000ULL;

vector<array<ull, MAX_POS>> dp;
vector<ull> prefixSum;

int pw[MAX_POS];


ull ways(int value, int pos) {
    if (value < 0)
        return 0;

    if (pos < 0)
        return (value == 0);

    return dp[value][pos];
}


void precompute(ull maxX) {

    pw[0] = 1;

    for (int i = 1; i < MAX_POS; i++)
        pw[i] = pw[i - 1] * 2;

    ull total = 0;

    for (int v = 0; ; v++) {

        array<ull, MAX_POS> row{};

        
        row[0] = (v <= 9) ? 1 : 0;

        
        for (int p = 1; p < MAX_POS; p++) {

            ull count = 0;

            for (int digit = 0; digit <= 9; digit++) {

                int remaining = v - digit * pw[p];

                if (remaining < 0)
                    break;

                ull add;

                if (digit == 0)
                    add = row[p - 1];
                else
                    add = dp[remaining][p - 1];

                count += add;

                if (count > INF) {
                    count = INF;
                    break;
                }
            }

            row[p] = count;
        }

        dp.push_back(row);

        total += row[MAX_POS - 1];

        if (total > INF)
            total = INF;

        prefixSum.push_back(total);

        
        if (total >= maxX)
            break;
    }
}


ll decibinaryNumbers(ll x) {

    
    int value = lower_bound(
        prefixSum.begin(),
        prefixSum.end(),
        (ull)x
    ) - prefixSum.begin();
    if (value ==0)
    return 0;
    ull rank = x;

    if (value > 0)
        rank -= prefixSum[value - 1];

    
    int highest = 0;

    for (int p = 0; p < MAX_POS; p++) {

        ull count = 0;

        for (int digit = 1; digit <= 9; digit++) {

            int remaining = value - digit * pw[p];

            if (remaining < 0)
                break;

            count += ways(remaining, p - 1);
        }

        if (rank > count) {
            rank -= count;
        }
        else {
            highest = p;
            break;
        }
    }

    
    string answer = "";

    int remaining = value;

   
    for (int digit = 1; digit <= 9; digit++) {

        int rem = remaining - digit * pw[highest];

        if (rem < 0)
            break;

        ull count = ways(rem, highest - 1);

        if (rank > count) {
            rank -= count;
        }
        else {
            answer += char('0' + digit);
            remaining = rem;
            break;
        }
    }

    
    for (int p = highest - 1; p >= 0; p--) {

        for (int digit = 0; digit <= 9; digit++) {

            int rem = remaining - digit * pw[p];

            if (rem < 0)
                break;

            ull count = ways(rem, p - 1);

            if (rank > count) {
                rank -= count;
            }
            else {
                answer += char('0' + digit);
                remaining = rem;
                break;
            }
        }
    }

    return stoll(answer);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    vector<ll> queries(q);

    ll maxX = 0;

    for (int i = 0; i < q; i++) {
        cin >> queries[i];
        maxX = max(maxX, queries[i]);
    }

    precompute(maxX);

    for (int i = 0; i < q; i++) {
        cout << decibinaryNumbers(queries[i]) << '\n';
    }

    return 0;
}
