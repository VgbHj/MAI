/*
Максим очень любит совершать покупки, и вот настал тот день, когда у него скопилось много разных купюр. Максим долго любовался каждой из них, но всё же решил потратить их на какие-то полезные вещи. Он хочет совершить несколько покупок и при этом продолжить наслаждаться видом купюр в своей копилке, поэтому он хочет оплатить каждую покупку минимальным числом купюр. Он не очень силён в математике, поэтому попросил Вас помочь ему.

У Максима есть купюры номиналами 100
, 200
, 500
, 1000
 и 5000
 бурлей.

Входные данные
В первой строке вам дано единственное целое число t
 (1≤t≤1000)
 — количество покупок, которое хочет совершить Максим.

В каждой из следующих t
 строк находится число n
 (100≤n≤10000000)
 — стоимость совершаемой покупки в бурлях, при чём n
 нацело делится на сто.

Выходные данные
Для каждой покупки в отдельной строке выведите пять чисел — количество купюр номиналом 100
, 200
, 500
, 1000
 и 5000
 бурлей, которые нужны для оплаты.*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long int factorial(int n){
    if(n == 1 || n == 0){
        return 1;
    }
    return n*factorial(n-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 100, 200, 500, 1000, 5000

    vector<int> a = {5000, 1000, 500, 200, 100};

    int n;
    cin >> n;

    for(int i=0; i<n; ++i){
        int price;
        cin >> price;
        vector<int> count = {0, 0, 0, 0, 0};

        while(price){
            for(int j=0; j<5; ++j){
                while(price-a[j] >= 0){
                    price -= a[j];
                    count[j]++;
                }
            }
        }

        for(int j=4; j>=0; --j){
            cout << count[j] << " ";
        }
        cout << "\n";
    }
}

// 5900 200+200+500+5000
