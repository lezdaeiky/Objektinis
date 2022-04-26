#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <algorithm>
#include <chrono>

#include "functions.h"
#include "student.h"

using namespace std;
using namespace std::chrono; 

int main()
{
    Timer timer;

    int sum = 0;

    for(int i = 1000; i<=10000000; i = i * 10)
    {
        timer.Start();
        generate_students(i);
        timer.Finish();
        double time = timer.Finish(); sum += time;
        cout<<i<<" studentu failo sukurimas: "<<time<<"ms"<<endl;

        timer.Start();
        ReadPrintFile("data" + to_string(i) + ".txt");
        timer.Finish();
        time = timer.Finish(); sum += time;
        cout<<i<<" studentu nuskaitymas is failo: "<<time<<"ms"<<endl;

        timer.Start();
        KietekaiVargseliai(i);
        timer.Finish();
        time = timer.Finish(); sum += time;
        cout<<i<<" studentu surusiavimas i dvi kategorijas: "<<time<<"ms"<<endl;

        timer.Start();
        PrintKietekai();
        timer.Finish();
        time = timer.Finish(); sum += time;
        cout<<i<<" studentu kieteku irasymas i faila: "<<time<<"ms"<<endl;

        timer.Start();
        PrintVargseliai();
        timer.Finish();
        time = timer.Finish(); sum += time;
        cout<<i<<" studentu vargseliu irasymas i faila: "<<time<<"ms"<<endl;

        cout<<endl<<i<<" studentu visos progrmaos veikimo laikas: "<<sum/1000<<" seconds\n"<<endl;        
    }

    return 0;
}