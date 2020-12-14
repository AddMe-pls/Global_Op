#include <cmath>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include "header.h"
#include <conio.h>

using namespace std;

void main()
{
    setlocale(LC_ALL, "Russian");
    vector <Trial> trials(1000);
    //trials.clear();
    double a, b;// границы исследования
    double delta, eps;//точность поиска
    double R = 0;//характеристика отрезка
    double MaxR = -10;//наилучшая характеристика
    int t = 1;//порядковый номер интервала с лучшей характеристикой
    int k = 2;//кол-во выбранных точек для исследования
    int tmpi;
    double tmpx, tmpz, tmpx1, tmpz1, NewPoint;
    int p=0;
    double MaxM = 10;//константа Липшеца


    cout << "Введите диапазон исследования:\n"; cin >> a; cin >> b;
    cout << a << " <=x<= " << b << endl;

    trials[0].z = f(a); //испытания на границах функции
    trials[0].x = a;
    trials[1].z = f(b);
    trials[1].x = b;
    
    cout << "Задайте точность eps "; cin >> eps; cout << endl;

    double minz = trials[0].z;
    double minx = trials[0].x;
    delta = trials[1].x - trials[0].x;

        while (delta > eps && k<990)
        {
            /*for (int i = 1; i < k; i++)//находим константу Липшица
                {
                    if (LipshConst(trials[i].x, trials[i - 1].x, trials[i].z, trials[i - 1].z) > MaxM)
                        MaxM = LipshConst(trials[i].x, trials[i - 1].x, trials[i].z, trials[i - 1].z);
                }*/
                for (int i = 1; i < k; i++)
                {
                    R = 0.5 * MaxM * (trials[i].x - trials[i - 1].x) - 0.5 * (trials[i].z + trials[i - 1].z);//вычисляем характеристику каждого интервала
                    if (R > MaxR) {
                        t = i;
                        MaxR = R;
                    }
                }
                delta = abs(trials[t].x - trials[t - 1].x);//нашли лучший интервал где есть минимум
                if (delta <= eps)// если достигли нужной точности, задача решена
                {
                    cout << "Минимум функции найден"<<endl;
                    cout << "min= " << minz <<" при x="<< minx<<endl<<p<< endl;
                    break;
                }
                else
                {
                    NewPoint = 0.5 * (trials[t - 1].x + trials[t].x) - 0.5 * (trials[t].z - trials[t - 1].z) / MaxM;
                    //trials[k + 1].x = 0.5 * (trials[t - 1].x + trials[t].x) - 0.5 * (trials[t].z - trials[t - 1].z) / MaxM;//если точность не та, находим следующую точку для исследования
                    for (int i = k; i > (t-1); i--)//поддерживаем последовательность из x в монотонном виде (возрастающем)
                    {
                        //tmpx = trials[i + 1].x;
                        //tmpz = trials[i + 1].z;
                        //tmpi = i + 1;
                        trials[i].x = trials[i-1].x;
                        trials[i].z = trials[i-1].z;
                    }
                    trials[t].x = NewPoint;
                    trials[t].z = f(trials[t].x);//исследуем точку
                    for (int i = 0; i < (k + 1); i++)//вычисляем приближенное значение минимума
                    {
                        if (trials[i].z < minz)
                        {
                            minz = trials[i].z;
                            minx = trials[i].x;
                        }
                        //cout << "Приближенное значение минимума " << minz << " В точке x=" << minx << endl;
                    }
                    MaxR = 0;
                    k++;
                };
                p++;
         }

}