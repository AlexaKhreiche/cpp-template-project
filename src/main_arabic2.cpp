#include "../include/arabic2.h"

int main() {
    arabic2::setupLocale(); 

    std::string fileName = "arabic.txt"; 
    arabic2::zipfsLawExercise(fileName);
    return 0;
}