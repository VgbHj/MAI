/*Вам дано квадратное уравнение вида a⋅x2+b⋅x+c=0
. Найдите все его корни.

Гарантируется, что уравнение имеет один или два корня.

Входные данные
В единственной строке расположены три целых числа a,b,c
 (−106⩽a,b,c⩽106
).

Выходные данные
Если уравнение имеет одно решение, выведите его.

Если уравнение имеет два решения, выведите сначала меньший корень, а затем больший корень.

Абсолютная или относительная погрешность корней не должна превышать 10−9
.*/

#include <iostream>
#include <cmath>
 
using namespace std;
 
int main() {
    double a, b, c;
    cin >> a >> b >> c;
    double D = b*b - 4*a*c;
    double x1, x2;
    x1 = (-b + sqrt(D))/(2*a);
    x2 = (-b - sqrt(D))/(2*a);
    cout.precision(10);
    if (D == 0){
        cout << x1;
    }
    else{
        if (x1 < x2){
            cout << x1 << " " << x2;
        }
        else{
            cout << x2 << " " << x1;
        }
    }
}