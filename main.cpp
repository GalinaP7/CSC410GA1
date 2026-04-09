#include "genome.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    srand(time(0));

    // required test
    genome myGenome;
    myGenome.print();
    myGenome.allocate(4);
    myGenome.print();
    myGenome.randomize();
    myGenome.print();
    myGenome.set_blue(0, 226);
    myGenome.print();

    // unit test 1: allocate() - (all pixels should initialize to 0)
    cout << "\n unit test 1: allocate() " << endl;
    genome g;
    g.allocate(5);
    g.print();

    // unit test 2: randomize() - (pixels should have random values)
    cout << " unit test 2: randomize() " << endl;
    g.randomize();
    g.print();

    // unit test 3: set and get - (should return exactly what we set)
    cout << " unit test 3: set and get " << endl;
    g.set_red(3, 70);
    g.set_green(3, 120);
    g.set_blue(3, 200);
    cout << "Pixel 3 red   (expect 70):  " << g.get_red(3)   << endl;
    cout << "Pixel 3 green (expect 120): " << g.get_green(3) << endl;
    cout << "Pixel 3 blue  (expect 200): " << g.get_blue(3)  << endl;

    // unit test 4: invalid index - (should return -1 and change nothing)
    cout << " unit test 4: invalid index " << endl;
    cout << "get_red(-1) (expect -1): " << g.get_red(-1) << endl;
    cout << "get_red(99) (expect -1): " << g.get_red(99) << endl;
    g.set_red(-1, 999);
    g.print();

    // unit test 5: deallocate 
    cout << " unit test 5: deallocate " << endl;
    g.deallocate();
    cout << "deallocate done" << endl;

    return 0;
}