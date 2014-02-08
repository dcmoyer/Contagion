#include "evoprob.h"

int compare_chars(const void* a, const void*b){
    return(*(char*)a - *(char*)b);
}

void evo_prob(unsigned char oldparams [STUDYSIZE][9], int number_prev_gen){
    
    double U1,U2;
    int index;
    double noise;
    char* histogram_values = new char[number_prev_gen];
    
    for(int j = 0; j < 9; j++){
        
        
        
        for(int i = 0; i < number_prev_gen; i++){
            
            histogram_values[i] = oldparams[i][j];
            
            //Defaulted to ASC order (1,2, 3, 5, 8...)
            
        } 
        std::qsort(histogram_values, number_prev_gen, sizeof(char), compare_chars);
        
        for(int i = 0; i < STUDYSIZE - number_prev_gen; i++){
            index = ((double) rand() / RAND_MAX)*number_prev_gen;
            U1 = (double) rand() / RAND_MAX;
            U2 = (double) rand() / RAND_MAX;
            
            oldparams[number_prev_gen + i][j] = histogram_values[index];
            
            //Box muller Transform
            noise = GAUSS_SCALE*std::sqrt(-2*std::log(U1))*std::cos(2* PI * U2);
            
            oldparams[number_prev_gen + i][j] = (char)(int) (fmin(fmax(((double) oldparams[number_prev_gen + i][j]/255.0) + noise,0), 1) * 255);
            
        }
        
    }
    delete[] histogram_values;
}
