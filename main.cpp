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

    // unit test 6: set_mRate and get_mRate
    cout << "\n unit test 6: set_mRate and get_mRate " << endl;
    genome g2;
    g2.allocate(4);
    cout << "default mRate (expect 0): " << g2.get_mRate() << endl;
    g2.set_mRate(0.5);
    cout << "after set_mRate(0.5) (expect 0.5): " << g2.get_mRate() << endl;
    g2.set_mRate(-1);   // invalid, should change nothing
    cout << "after set_mRate(-1) (expect 0.5): " << g2.get_mRate() << endl;
    g2.set_mRate(2);    // invalid, should change nothing
    cout << "after set_mRate(2) (expect 0.5): " << g2.get_mRate() << endl;
    g2.set_mRate(0);    // valid boundary
    cout << "after set_mRate(0) (expect 0): " << g2.get_mRate() << endl;
    g2.set_mRate(1);    // valid boundary
    cout << "after set_mRate(1) (expect 1): " << g2.get_mRate() << endl;

    // unit test 7: set_pixel and get_pixel
    cout << "\n unit test 7: set_pixel and get_pixel " << endl;
    genome g3;
    g3.allocate(4);
    Pixel p;
    p.red = 100; p.green = 150; p.blue = 200;
    g3.set_pixel(2, p);
    Pixel result = g3.get_pixel(2);
    cout << "Pixel 2 red   (expect 100): " << result.red   << endl;
    cout << "Pixel 2 green (expect 150): " << result.green << endl;
    cout << "Pixel 2 blue  (expect 200): " << result.blue  << endl;
    // invalid index
    Pixel bad = g3.get_pixel(99);
    cout << "get_pixel(99) red (expect -1): " << bad.red << endl;
    // invalid pixel values
    Pixel invalidPixel;
    invalidPixel.red = 999; invalidPixel.green = 0; invalidPixel.blue = 0;
    g3.set_pixel(0, invalidPixel);  // should change nothing
    Pixel unchanged = g3.get_pixel(0);
    cout << "after invalid set_pixel, pixel 0 red (expect 0): " << unchanged.red << endl;

    // unit test 8: mutate_gene
    cout << "\n unit test 8: mutate_gene " << endl;
    genome g4;
    g4.allocate(4);
    g4.set_mRate(0.0);  // mRate 0 means nothing should ever change
    g4.print();
    g4.mutate_gene(0);
    cout << "after mutate_gene with mRate 0 (expect no change): " << endl;
    g4.print();
    g4.set_mRate(1.0);  // mRate 1 means everything should always change
    g4.mutate_gene(0);
    cout << "after mutate_gene with mRate 1 (expect pixel 0 changed): " << endl;
    g4.print();
    // invalid index should do nothing
    g4.mutate_gene(-1);
    g4.mutate_gene(99);
    cout << "after invalid mutate_gene (expect no change): " << endl;
    g4.print();

    // unit test 9: mutate
    cout << "\n unit test 9: mutate " << endl;
    genome g5;
    g5.allocate(4);
    g5.set_mRate(1.0);  // all pixels should change
    cout << "before mutate: " << endl;
    g5.print();
    g5.mutate();
    cout << "after mutate with mRate 1 (expect all pixels changed): " << endl;
    g5.print();

    // unit test 10: calculate_gene_fitness
    cout << "\n unit test 10: calculate_gene_fitness " << endl;
    genome g6;
    g6.allocate(1);
    g6.set_red(0, 0);
    g6.set_green(0, 0);
    g6.set_blue(0, 0);
    Pixel target;
    target.red = 0; target.green = 0; target.blue = 0;
    cout << "fitness with identical pixels (expect 0): " << g6.calculate_gene_fitness(0, target) << endl;
    target.red = 256; target.green = 256; target.blue = 256;
    cout << "fitness with max difference (expect -1): " << g6.calculate_gene_fitness(0, target) << endl;

    // unit test 11: calculate_overall_fitness
    cout << "\n unit test 11: calculate_overall_fitness " << endl;
    genome g7;
    g7.allocate(3);
    g7.set_red(0, 0);   g7.set_green(0, 0);   g7.set_blue(0, 0);
    g7.set_red(1, 0);   g7.set_green(1, 0);   g7.set_blue(1, 0);
    g7.set_red(2, 0);   g7.set_green(2, 0);   g7.set_blue(2, 0);
    Pixel targetArray[3];
    targetArray[0].red = 0;   targetArray[0].green = 0;   targetArray[0].blue = 0;
    targetArray[1].red = 0;   targetArray[1].green = 0;   targetArray[1].blue = 0;
    targetArray[2].red = 0;   targetArray[2].green = 0;   targetArray[2].blue = 0;
    cout << "overall fitness identical (expect 0): " << g7.calculate_overall_fitness(targetArray, 3) << endl;
    // size mismatch should return -1
    cout << "size mismatch (expect -1): " << g7.calculate_overall_fitness(targetArray, 99) << endl;

    return 0;
}