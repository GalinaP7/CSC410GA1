#include "genome.h"
#include <iostream>
#include <cstdlib>   // needed for rand()

using namespace std;

// constructor
genome::genome() {
    genes = NULL;
    nGenes = 0;
}

// destructor (automatically cleans up memory)
genome::~genome() {
    deallocate();
}

// allocates an array of numGenes Pixels, all RGB initialized to 0
void genome::allocate(int numGenes) {
    // if array already exists, free it first to avoid memory leak
    if (genes != NULL) {
        deallocate();
    }

    genes = new Pixel[numGenes];  // dynamically create the array
    nGenes = numGenes;

    // loop through every Pixel and set all RGB channels to 0
    for (int i = 0; i < nGenes; i++) {
        genes[i].red   = 0;
        genes[i].green = 0;
        genes[i].blue  = 0;
    }
}

// frees memory and resets to safe empty state
void genome::deallocate() {
    if (genes == NULL) {
        return;  
    }
    delete[] genes; 
    genes = NULL;
    nGenes = 0;
}

void genome::randomize() {
    for (int i = 0; i < nGenes; i++) {
        genes[i].red   = rand() % 256;
        genes[i].green = rand() % 256;
        genes[i].blue  = rand() % 256;
    }
}

void genome::set_red(int index, int value) {
    // check index is valid before touching the array
    if (index < 0 || index >= nGenes) {
        return;   // invalid index, do nothing
    }
    genes[index].red = value;
}

void genome::set_green(int index, int value) {
    if (index < 0 || index >= nGenes) {
        return;
    }
    genes[index].green = value;
}

void genome::set_blue(int index, int value) {
    if (index < 0 || index >= nGenes) {
        return;
    }
    genes[index].blue = value;
}

int genome::get_red(int index) {
    if (index < 0 || index >= nGenes) {
        return -1;   // invalid index, signal error
    }
    return genes[index].red;
}

int genome::get_green(int index) {
    if (index < 0 || index >= nGenes) {
        return -1;
    }
    return genes[index].green;
}

int genome::get_blue(int index) {
    if (index < 0 || index >= nGenes) {
        return -1;
    }
    return genes[index].blue;
}

void genome::print() {
    cout << "GENOME: " << nGenes << " genes ";
    for (int i = 0; i < nGenes; i++) {
        cout << "(" << genes[i].red   << ","
                    << genes[i].green << ","
                    << genes[i].blue  << ") ";
    }
    cout << endl;
}