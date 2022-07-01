#include<iostream>
#include<string>
#include<vector> 
#include<algorithm> // sort
#include<climits> // INT_MAX

#define UNFIND -1

// using alias
using std::cin;     using std::cout;
using std::endl;    
using std::string;  using std::cerr;
using std::vector;  using std::sort;

// get minimum of two nums
int min(int a,int b){
    return a < b ? a : b;
}

// dp
int getLeastNum(const vector<int>& coins,const int& amount){
    vector<int> minValue; // the array of F(n)
    minValue.push_back(0); // F(0) = 0

    for (int i = 1;i <= amount;i++){
        int temp = INT_MAX;
        for (const int& j : coins){
            if (i - j < 0) // if the value to find is smaller than 0 ..
                break;
            if (minValue[i - j] == UNFIND) // if the F(n - Ci) can't be found ..
                continue;
            
            temp = min(temp,minValue[i - j]); // find the min(F(n - Ci)), 0 <= i <= size - 1
        }

        if (temp == INT_MAX) // don't find
            minValue.push_back(UNFIND);
        else
            minValue.push_back(temp + 1); // F[n] = min(F(n - Ci)) + 1
    }

    return minValue[minValue.size() - 1]; // return F[n]
}

int main(){
    vector<int> coins;
    cout << "input possible coin values in a line(e.g. 1 2 3): \n";
    int num;
    while(cin >> num){
        coins.push_back(num);
        if (cin.get() == '\n')
            break;
    }

    cout << "input the total amount: \n";
    int amount;
    cin >> amount;

    sort(coins.begin(),coins.end()); // sort first

    cout << getLeastNum(coins,amount); // print the result

    return 0;
}