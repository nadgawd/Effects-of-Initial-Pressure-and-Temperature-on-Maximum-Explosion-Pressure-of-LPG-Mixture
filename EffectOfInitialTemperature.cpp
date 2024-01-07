//Code to show effect of initial temperature on max pressure

#include <bits/stdc++.h>
using namespace std;

void calccoeff(const vector<double> &temperature, const vector<double> &pressuremax, int degree)
{
    int n = temperature.size();

    vector<vector<double>> TEMP(n, vector<double>(degree + 1, 1.0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j <= degree; ++j)
        {
            TEMP[i][j] = pow(temperature[i], j);
        }
    }

    vector<vector<double>> TEMPT(degree + 1, vector<double>(n));

    for (int i = 0; i < degree + 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            TEMPT[i][j] = TEMP[j][i];
        }
    }

    vector<vector<double>> TEMPTTEMP(degree + 1, vector<double>(degree + 1, 0.0));

    for (int i = 0; i < degree + 1; ++i)
    {
        for (int j = 0; j < degree + 1; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                TEMPTTEMP[i][j] =TEMPTTEMP[i][j] + TEMPT[i][k] * TEMP[k][j];
            }
        }
    }

    vector<double> TEMPTPMAX(degree + 1, 0.0);

    for (int i = 0; i < degree + 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            TEMPTPMAX[i] = TEMPTPMAX[i] + TEMPT[i][j] * pressuremax[j];
        }
    }

    for (int i = 0; i < degree + 1; ++i)
    {
        for (int j = i + 1; j < degree + 1; ++j)
        {
            double factor = TEMPTTEMP[j][i] / TEMPTTEMP[i][i];
            for (int k = 0; k < degree + 1; ++k)
            {
                TEMPTTEMP[j][k] = TEMPTTEMP[j][k] - factor * TEMPTTEMP[i][k];
            }
            TEMPTPMAX[j] = TEMPTPMAX[j] - factor * TEMPTPMAX[i];
        }
    }

    vector<double> coeff(degree + 1, 0.0);

    for (int i = degree; i >= 0; --i)
    {
        coeff[i] = TEMPTPMAX[i];
        for (int j = i + 1; j < degree + 1; ++j)
        {
            coeff[i] = coeff[i] - TEMPTTEMP[i][j] * coeff[j];
        }
        coeff[i] = coeff[i] / TEMPTTEMP[i][i];
    }

    ofstream fkout;
    fkout.open("initialtempout.txt");

    fkout << "Coefficients are:"<<endl;
    for (int i = 0; i < degree + 1; ++i)
    {
        fkout << "a" << i << ": " << coeff[i] <<endl;
    }

    fkout<<endl;

    for(int i=0; i<12; i++)
    {
       float predictedpmax = 0;
       for (int j=0; j<degree +1; j++)
       {
            predictedpmax = predictedpmax + coeff[j]*pow(temperature[i],j);
       } 
       fkout<<"Predicted Maximum Pressure : "<<predictedpmax<<" "<< "and the Percentage Error : " <<abs(pressuremax[i]-predictedpmax)*100/pressuremax[i]<<endl;

    }

    fkout.close();
}

int main()
{
    // For inputting manual data, the code is written and commented below

    // int n,q;
    // cin>>n; //Enter the size
    // vector<double> temperature(n);
    // cout<<"Enter the values for Temperature : "<<endl;
    // for(int i=0; i<n; i++)
    // {
    //     cin>>q;
    //     temperature.push_back(q);
    // }

    // cout<<"Enter the values of Maximum Pressure : "<<endl;
    // vector<double> pressuremax(n);
    // for (int i=0; i<n; i++)
    // {
    //     cin>>q;
    //     pressuremax.push_back(q);
    // }

    // int degree;
    // cout << "Enter the degree : ";
    // cin >> degree;



    //Here we are using the data from the term paper to show this code works
    int degree = 3;

    vector<double> temperature = {25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300};
    vector<double> pressuremax = {0.855, 0.816, 0.763, 0.715, 0.667, 0.629, 0.597, 0.568, 0.542, 0.518, 0.497, 0.478};

    calccoeff(temperature, pressuremax, degree);

    return 0;
}