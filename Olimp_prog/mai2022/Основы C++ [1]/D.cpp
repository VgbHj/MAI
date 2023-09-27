/*
Сидя на крыше и пуская самолётики из бумаги Вася заметил как на земле, в лучах солнца, мирно греется кот. Вася очень любит наводить хаос вокруг себя и поэтому решил так или иначе растревожить бедное животное, и первой его идеей стало запустить в него самолётик. Так как Вася пускал самолётики уже давно он точно знает, что ни один самолётик не может пролететь более чем D
 метров, так же он прикинул, что если бы его дом находился в начале координат, то кот бы находился в точке (X
 м, Y
 м). Помогите Василию определить реализуема ли его идея или нужно придумать что-то другое.

Входные данные
В первой строке содержится единственное натуральное число D
 (D⩽100)
, максимальное расстояние, на которое может быть запущен самолётик. В следующей строке содержатся два целых числа X
 и Y
 (−100⩽X,Y⩽100)
, координаты бедного животного.

Выходные данные
Выведите единственную строку содержащую «YES», если идея Васи реализуема, иначе выведите «NO».
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int d, x, y;
    cin >> d >> x >> y;

    if (d*d >= (x*x + y*y)){
        cout << "YES";
    }
    else{
        cout << "NO";
    }

}