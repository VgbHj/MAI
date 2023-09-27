/*
На плоскости расположены две окружности, определите имеют ли они общие точки.

Входные данные
В первой строке вам даны три целых числа x1
, y1
 (−100⩽x1,y1⩽100)
 — координаты центра первой окружности, r1
 (1⩽r1⩽1000)
 — радиус первой окружности, во второй строке так же даны три целых числа x2
, y2
 (−100⩽x2,y2⩽100)
 — координаты центра второй окружности, r2
 (1⩽r2⩽1000)
 — радиус второй окружности.

Выходные данные
Выведите «YES», если данные окружности имеют общие точки, иначе выведите «NO». (Вывод осуществляется без кавычек)
*/
#include <iostream>
#include <cmath>

using namespace std;

int min(int r1, int r2){
    if (r1 < r2) return r1;
    return r2;
}

int max(int r1, int r2){
    if (r1 > r2) return r1;
    return r2;
}

int main() {
    int x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    double l = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    if ((l <= r1+r2) and ( (max(r1,r2)-l-min(r1,r2)) <= 0)){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
}