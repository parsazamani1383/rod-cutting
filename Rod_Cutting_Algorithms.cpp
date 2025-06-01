/*
* Rod Cutting Problem - Implemented in 3 Ways:
 * 1. Recursive (No memoization)
 * 2. Top-Down Dynamic Programming (with memoization)
 * 3. Bottom-Up Dynamic Programming
 *
 * Author: parsa zamain
 * GitHub: https://github.com/parsazamani1383
 * Date: 2025-06-01
 *
 * This program generates a random price list for rod lengths and calculates
 * the maximum revenue obtainable by cutting the rod in different ways.
 */

#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_N = 100;

// Recursive (no memoization)
int rodCuttingRecursive(int price[], int n) {
    if (n == 0) return 0;
    int maxVal = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int temp = price[i] + rodCuttingRecursive(price, n - i);
        if (temp > maxVal)
            maxVal = temp;
    }
    return maxVal;
}

// Top-Down DP with memoization
int rodCuttingTopDown(int price[], int n, int memo[]) {
    if (n == 0) return 0;
    if (memo[n] > -1) return memo[n];
    int maxVal = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int temp = price[i] + rodCuttingTopDown(price, n - i, memo);
        if (temp > maxVal)
            maxVal = temp;
    }
    memo[n] = maxVal;
    return maxVal;
}

// Bottom-Up DP
int rodCuttingBottomUp(int price[], int n) {
    int dp[MAX_N];
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int maxVal = INT_MIN;
        for (int j = 1; j <= i; j++) {
            int temp = price[j] + dp[i - j];
            if (temp > maxVal)
                maxVal = temp;
        }
        dp[i] = maxVal;
    }

    return dp[n];
}

// Generate random prices (lengths 1 to n)
void generateRandomPrices(int price[], int n, int minVal = 1, int maxVal = 20) {
    price[0] = 0; // unused
    for (int i = 1; i <= n; i++) {
        price[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

// Main
int main() {
    srand(time(0)); // Random seed

    int n = 8; // rod length
    int price[MAX_N];
    int memo[MAX_N];

    // Generate random prices
    generateRandomPrices(price, n);

    // Show prices
    cout << "Generated price list: ";
    for (int i = 1; i <= n; i++) {
        cout << price[i] << " ";
    }
    cout << endl;

    // Run Recursive
    int resultRecursive = rodCuttingRecursive(price, n);

    // Run Top-Down with memoization
    for (int i = 0; i <= n; i++) memo[i] = -1;
    int resultTopDown = rodCuttingTopDown(price, n, memo);

    // Run Bottom-Up
    int resultBottomUp = rodCuttingBottomUp(price, n);

    // Print results
    cout << "Result (Recursive):   " << resultRecursive << endl;
    cout << "Result (Top-Down DP): " << resultTopDown << endl;
    cout << "Result (Bottom-Up):   " << resultBottomUp << endl;

    if (resultRecursive == resultTopDown && resultTopDown == resultBottomUp)
        cout << "✅ All methods produced the same result." << endl;
    else
        cout << "❌ Results are different between methods!" << endl;

    return 0;
}

