#include <iostream>
#include "PSO.h"
using namespace std;

double particle::Cost_Function()
{
    /*
        Define cost function for optimization problem
    */


    return x[0]*x[0] + 4*x[0] + 2;
}

int main()
{
    double* ub, *lb, wp, wg, psi;
    int numVariables, numParticles, numIterations;

    numVariables = 1;
    numParticles = 20;
    numIterations = 1000;

    wp = 1;
    wg = 1;
    psi = 1;

    lb = new double[numVariables];
    ub = new double[numVariables];
    lb[0] = -100;
    ub[0] = 100;

    PSO myPSO(numVariables,lb,ub,numParticles,numIterations, wp, wg, psi);

    myPSO.run();

    return 0;
}
