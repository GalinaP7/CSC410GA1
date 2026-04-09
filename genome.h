#ifndef GENOME_H
#define GENOME_H

struct Pixel {
    int red;
    int blue;
    int green;
};

class genome {
public:
    genome(); // constructor - initializes genes to NULL and nGenes to 0
    ~genome(); // destructor - cleans up memory when object is destroyed
    void allocate(int nGenes); // takes a num, creates array of that many Pixels with RGB all set to 0
    void deallocate(); // frees the memory used by the genes array and sets nGenes to 0
    void randomize(); // gives every Pixel a random RGB value between 0 and 256
    void set_red(int index, int value); // sets red val of Pixel at given index
    int get_red(int index); // returns red value of Pixel at index, returns -1 if index is invalid
    void set_green(int index, int value); 
    int get_green(int index); 
    void set_blue(int index, int value); 
    int get_blue(int index); 
    void print();

private:
    Pixel* genes; // pointer to the array of Pixels
    int nGenes;   // stores the num of Pixels in array
};

#endif