#include <iostream>

class particle
{
public:
    particle() {}
    ~particle();
    void initialize(const int numVariables, const double* lb, const double* ub);
    double Cost_Function();
    void iterateParticle(const double* gBestValues, const double wp, const double wg, const double psi, const double* lb, const double* ub);

    int numVariables;
    double* x;
    double* velocity;
    double pBest;
    double* pBestValues;

};



class PSO
{
public:
    PSO(int numVariables, double* lb, double* ub, int numParticles, int numIterations, double wp, double wg, double psi);
    ~PSO();

    void run();
    void runIteration();
    void returnResults();

    int numVariables;
    int numParticles;
    int numIterations;
    double wp;
    double wg;
    double psi;

    double gBest;
    double* gBestValue;

    double* ub;
    double* lb;

    particle* particles;
};
