#include <MyLib/MathLib.hpp>
#include <MyLib/engine.hpp>

#include <iostream>
#include <vector>

using Math::Vector2;
using std::vector;

#define WIDTH   400
#define HEIGHT  400

float GetDist(vector<Vector2> c)
{
    float d = 0;
    for (int i = 1; i < c.size(); i++)
        d += c[i - 1].Dist(c[i]);
    return d;
}

template <typename T>
void Swap(vector<T> &c, int i, int j)
{
    T tmp = c[i];
    c[i] = c[j];
    c[j] = tmp;
}


int main(int argc, char *argv[])
{
    Math::Init();

    Renderer r("TSM Brute force!", WIDTH, HEIGHT);

    vector<Vector2> cities;
    int totalCityNumber;

    if (argc == 1)
        totalCityNumber = 5;
    else
        totalCityNumber = atoi(argv[argc - 1]);

    cities.reserve(totalCityNumber);



    for (int i = 0; i < totalCityNumber; i++)
    {
        cities[i] = Vector2::Random();
        cities[i].x *= WIDTH;
        cities[i].y *= HEIGHT;
    }

    float record = GetDist(cities);

    vector<Vector2> bestEver;

    for (int i = 0; i < totalCityNumber; i++)
        bestEver.push_back(cities[i]);
    
    std::cout << bestEver.size();

    while (!r.WindowShouldClose())
    {
        r.Background({0, 0, 0, 0});

        for (int i = 0; i < totalCityNumber; i++)
            r.FillCircle(cities[i].x, cities[i].y, 4, {1, 1, 1, 1});

        for (int i = 1; i < totalCityNumber; i++)
            r.Line(cities[i - 1].x, cities[i - 1].y, cities[i].x, cities[i].y, {1, 1, 1, 1});

        for (int i = 1; i < bestEver.size(); i++)
            r.Line(bestEver[i - 1].x, bestEver[i - 1].y, bestEver[i].x, bestEver[i].y, {1, 0, 1, 1});


        int i = Math::Random(0, totalCityNumber - 1);
        int j = Math::Random(0, totalCityNumber - 1);
        Swap(cities, i, j);

        float d = GetDist(cities);
        if (d < record)
        {
            record = d;
            for (int i = 0; i < totalCityNumber; i++)
                bestEver[i] = (cities[i]);
        }


        r.SwapBuffers();

        r.PollEvents();
    }

}