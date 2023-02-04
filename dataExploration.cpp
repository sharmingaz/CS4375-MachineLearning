#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

int main(int argc, char** argv) {
   
       ifstream inFS;
       string line;
       string rm_in, medv_in;
       const int MAX_LEN = 1000;
       vector<double> rm(MAX_LEN);
       vector<double> medv(MAX_LEN);
       cout << "Opening file Boston.csv" << endl;
       inFS.open("Boston.csv");
       if(!inFS.is_open()){
           cout << "Could not open file Boston.csv" << endl;
           return 1;
       }

       cout << "Reading line 1" << endl;
       getline(inFS, line);
       cout << "Heading: " << line << endl;
       int numObservations = 0;
       while(inFS.good()){
           getline(inFS, rm_in, ',');
           getline(inFS, medv_in , '\n');
           rm.at(numObservations) = stof(rm_in);
           medv.at(numObservations) = stof(medv_in);
           numObservations++;
       }
   
   rm.resize(numObservations);
   medv.resize(numObservations);
   
   cout << "\nNew length " << rm.size() << endl;
   
   cout << "Closing file Boston.csv." << endl;
   inFS.close(); // close file
   
   cout << "Number of records: " << numObservations << endl;
   
   // rm functions (1-4):
   cout << "\nStats for rm:" << endl;
   // sum
   double rmsum = 0;
   for (int i=0; i<numObservations; i++) {
      rmsum = rmsum + rm[i];
   }
   cout << "Sum = " << rmsum << endl;
   // mean
   double rmmean = (rmsum/numObservations);
   cout << "Mean = " << rmmean << endl;
   // sort algorithm for mean
   nth_element(rm.begin(), rm.begin()+rm.size() / 2, rm.end());
   double rmmedian = rm[(rm.size() / 2)];
   cout << "Median = " << rmmedian<< endl;
   //range
   cout << "Range = " << rm[0] << " " << rm[numObservations-1] << endl;
   
   
   // medv functions (1-4)
   cout << "\nStats for medv: " << endl;
   // sum
   double medvsum = 0;
   for (int i=0; i<numObservations; i++) {
      medvsum = medvsum + medv[i];
   }
   cout << "Sum = " << medvsum << endl;
   // mean
   double medvmean = (medvsum/numObservations);
   cout << "Mean = " << medvmean << endl;
   // sorting algorithm for mean
   nth_element(medv.begin(), medv.begin()+(medv.size() / 2), medv.end());
   double medvmedian = medv[(medv.size() / 2)];
   cout << "Median = " << medvmedian << endl;
   // range
   cout << "Range = " << medv[0] << " " << medv[numObservations-1] << endl;
   
   
   // covariance between rm and medv
   double cov = 0;
   for (int i=0; i < numObservations; i++)
      cov = cov + ((rm[i] - rmmean) * (medv[i] - medvmean));
   cout <<  "\nCovariance = " << cov / (numObservations-1);
   
   // correlation for rm and medv
   double cor = 0;
   double rmcor = 0;
   double medvcor = 0;
   for (int i = 0; i < numObservations; i++)
      rmcor = rmcor + (rm[i] - rmmean);
   for (int i = 0; i < numObservations; i++)
      medvcor = medvcor + (medv[i] - medvmean);
   double denom = sqrt((rmcor*rmcor)*(medvcor*medvcor));
   cor = (rmcor*medvcor)/(denom);
   cout << "\nCorrelation = " << cor << endl;
   
   // end of cpp
   cout << "\nProgram terminates.\n";
   return 0;
}
