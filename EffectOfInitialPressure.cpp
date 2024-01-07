//Code to show effect of initial pressure on max pressure
#include<bits/stdc++.h>
using namespace std;

float pressuresqr(float pressure[], int n)
{
    float res = 0;
    for (int i=0; i<n; i++)
    {
        res = res + pressure[i]*pressure[i];
    }
    // cout<<"pressuresqr"<<result<<endl;
    return res;
}

float sumpressure(float pressure[], int n)
{
    float res = 0;
    for (int i=0 ; i<n; i++)
    {
        res = res + pressure[i];

    }
    // cout<<"sumpressure"<<res<<endl;
    return res;
}

float sumpressurepmax(float pressure[], float pmax[], int n)
{
    float res = 0;
    for (int i=0; i<n ; i++)
    {
        res = res + pressure[i]*pmax[i];

    }
    // cout<<"sumpressurepmax"<<res<<endl;
    return res;
}

float sumpmax(float pmax[], int n)
{
    float res=0;
    for (int i = 0; i<n; i++)
    {
        res = res + pmax[i];
    }
    // cout<<"sumpmax"<<res<<endl;
    return res;

}

float st(float pmax[], int n)
{
    float res = 0;
    for (int i = 0; i<n; i++)
    {
        res = res + (pmax[i]-sumpmax(pmax,n)/n)*(pmax[i]-sumpmax(pmax,n)/n);

    }
    return res;
}

float sr(float pmax[], float pressure[], int n)
{
    float res = 0;
    float a1 =  (n*sumpressurepmax(pressure,pmax,n) - sumpressure(pressure,n)*sumpmax(pmax,n))/(n*pressuresqr(pressure,n) - sumpressure(pressure,n)*sumpressure(pressure,n));
    float a0 = (sumpmax(pmax,n)/n) - (sumpressure(pressure,n)/n)*a1;
    for (int i=0; i<n; i++)
    {
        res = res + (pmax[i]-a0-a1*pressure[i])*(pmax[i]-a0-a1*pressure[i]);
    }
    return res;
}

int main()
{
    ifstream fkin;
    fkin.open("initialpressurein.txt");
    int n;
    fkin>>n; // n is the size of data

    float pressure[n];
    for (int i=0; i<n; i++)
    {
        fkin>>pressure[i];
    }


    float pmax[n];
    for (int i =0; i<n; i++)
    {
        fkin>>pmax[i];
    }
    fkin.close();
    ofstream fkout;
    fkout.open("initialpresesureout.txt");

    float a0;
    float a1;

    a1 =  (n*sumpressurepmax(pressure,pmax,n) - sumpressure(pressure,n)*sumpmax(pmax,n))/(n*pressuresqr(pressure,n) - sumpressure(pressure,n)*sumpressure(pressure,n));

    fkout<<"a1 : "<<a1<<endl;

    a0 = (sumpmax(pmax,n)/n) - (sumpressure(pressure,n)/n)*a1;

    fkout<<"a0 : "<<a0<<endl;
    fkout<<endl;
    for (int i = 0; i<n; i++)
    {
        float pmaxpredicted = a0 + a1*pressure[i];
        fkout<<"Predicted Maximum Pressure : "<<pmaxpredicted<<" "<< "and the Percentage Error : " <<abs(pmax[i]-pmaxpredicted)*100/pmax[i]<<endl;
    }
    fkout.close();

}