/*
Однажды Васе было очень скучно и он решил написать на листе бумаге три числа A
, B
 и C
. Пока он их писал ему стало ещё более скучно и он решил вычислить значение выражения (A+B)∗C
. Однако считать сложнее чем писать случайные числа и он не справился с этой задачей. Помогите Васе решить эту непростую задачу.

Входные данные
В первой и единственной строке вам даны три числа A
, B
 и C
, (|A|,|B|,|C|⩽100)
.

Выходные данные
Выведите одну строку, содержащую результат вычислений с абсолютной или отностительной погрешностью не более 10−6.
*/

#include <iostream>

using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    cout.precision(20);
    cout << (a+b)*c << endl;
}