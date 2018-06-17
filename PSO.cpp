#include "PSO.h"
#include <cstdlib>


PSO::PSO(int numVariables, double* lb, double* ub, int numParticles, int numIterations, double wp, double wg, double psi)
{
    this->numVariables = numVariables;
    this->numParticles = numParticles;
    this->numIterations = numIterations;
    this->wp = wp;
    this->wg = wg;
    this->psi = psi;
    this->lb = lb;
    this->ub = ub;

    //this->gBestValue = new double[numVariables];
    this->particles = new particle[numParticles];



    for (int ii = 0; ii < numParticles; ii++)
    {
       this->particles[ii].initialize(numVariables, lb, ub);
    }

}

void PSO::run()
{
    this->gBest = particles[0].pBest;
    this->gBestValue = particles[0].pBestValues;
    for (int ii = 1; ii < this->numParticles; ii++)
    {
        if (particles[ii].pBest < this->gBest)
        {
            this->gBest = particles[ii].pBest;
            this->gBestValue = particles[ii].pBestValues;
        }
    }

    for (int ii = 0; ii < this->numIterations; ii++)
    {
        for (int kk = 0; kk < this->numParticles; kk++)
        {
            this->particles[kk].iterateParticle(this->gBestValue,this->wp, this->wg, this->psi, this->lb, this->ub);
        }

        for (int kk = 0; kk < this->numParticles; kk++)
        {
            if (particles[kk].pBest < this->gBest)
            {
                std::cout << "New gBest: " << this->gBest << std::endl;
                this->gBest = this->particles[kk].pBest;
                this->gBestValue = this->particles[kk].pBestValues;
            }
        }

        //std::cout << "gBest: " << this->gBest << std::endl;

    }

    this->returnResults();
}

void particle::initialize(const int numVariables, const double* lb, const double* ub)
{
    this->x = new double[numVariables];
    this->pBestValues = new double[numVariables];
    this->velocity = new double[numVariables];
    this->numVariables = numVariables;

    for (int ii = 0; ii < numVariables; ii++)
    {
        velocity[ii] = 0;
    }

    for (int ii = 0; ii < numVariables; ii++)
    {
        x[ii] = rand() % 100;
        x[ii] *= (ub[ii]-lb[ii]) / 100;
        x[ii] += lb[ii];
        pBestValues[ii] = x[ii];
        pBest = this->Cost_Function();
    }
}

void particle::iterateParticle(const double* gBestValues, const double wp, const double wg, const double psi, const double* lb, const double* ub)
{
    //std::cout << x[0] << std::endl;

    for (int ii = 0; ii < this->numVariables; ii++)
    {
        double randp = rand() % 100;
        double randg = rand() % 100;
        this->velocity[ii] = psi*this->velocity[ii] + wp * randp / 100 * (this->pBestValues[ii]-this->x[ii])
            + wg * randg / 100 * (gBestValues[ii]-this->x[ii]);
        this->x[ii] += this->velocity[ii];

        if (x[ii] < lb[ii])
        {
            x[ii] = lb[ii];
        }
        else if (x[ii] > ub[ii])
        {
            x[ii] = ub[ii];
        }
    }

    double value = this->Cost_Function();

    if (value < this->pBest)
    {
        this->pBest = value;
        for (int ii = 0; ii < this->numVariables; ii++)
        {
            this->pBestValues[ii] = x[ii];
        }
    }
}

void PSO::returnResults()
{
    std::cout << "Final objective value: " << this->gBest << std::endl;
    for (int ii = 0; ii < this->numVariables; ii++)
    {
        std::cout << "X" << ii << ": " << this->gBestValue[ii] << std::endl;
    }
}

PSO::~PSO()
{
    delete[] particles;
    delete[] gBestValue;
    delete[] ub;
    delete[] lb;
}


particle::~particle()
{
    delete[] x;
    delete[] pBestValues;
    delete[] velocity;
}




