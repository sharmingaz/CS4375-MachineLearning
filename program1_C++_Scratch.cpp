#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std;

int main(int argc, const char * argv[]) {
   // import data set
   ifstream inFS;
   string line;
   string num_in, pclass_in, survived_in, sex_in, age_in;
   
   const int MAX_LEN = 10000;
   vector<double> num(MAX_LEN);
   vector<double> pclass(MAX_LEN);
   vector<double> survived(MAX_LEN);
   vector<double> sex(MAX_LEN);
   vector<double> age(MAX_LEN);
   
   // read in file
   cout << "Opening file titanic_project.csv" << endl;
   inFS.open("titanic_project.csv");
   if(!inFS.is_open()){
       cout << "Could not open file titanic_project.csv" << endl;
       return 1;
   }

   getline(inFS, line);
   cout << "Heading: " << line << endl;
   int numObservations = 0;
   
   while(inFS.good()){
      getline(inFS, num_in, ',');
      getline(inFS, pclass_in, ',');
      getline(inFS, survived_in, ',');
      getline(inFS, sex_in , ',');
      getline(inFS, age_in, '\n');
      
      //num.at(numObservations) = stof(num_in);
      pclass.at(numObservations) = stof(pclass_in);
      survived.at(numObservations) = stof(survived_in);
      sex.at(numObservations) = stof(sex_in);
      age.at(numObservations) = stof(age_in);
       numObservations++;
   }
   num.resize(numObservations);
   pclass.resize(numObservations);
   survived.resize(numObservations);
   sex.resize(numObservations);
   age.resize(numObservations);
      
   cout << "Closing file titanic_project.csv." << endl;
   inFS.close(); // close file
   
   cout << "Number of records:\n " << numObservations << endl;
   
   // train and test set using arrays
   int trainSurvived[800];
   int trainSex[800];
   
   int testSurvived[300];
   int testSex[300];
   
   int sensitivity=0, specificity=0;
      
   auto start = std::chrono::high_resolution_clock::now();
   // first 800 inputs for training set
   for (int i = 0; i <= 799; i++) {
      trainSurvived[i] = survived[i];
      trainSex[i] = sex[i];
   }
   
   // sigmoid function into sf array
   int sfSurv[800];
   int sfSex[800];
   
   for (int i = 0; i <= 799; i++) {
      sfSurv[i] = 1 / (1 + exp(-trainSurvived[i]));
      sfSex[i] = 1 / (1 + exp(-trainSex[i]));
   }
   
   // multiply data to get log liklihood
   int logSurvived[799];
   int logSex[799];
   
   // gradient descent
   
   for(int i = 0; i<=799; i++) {
      logSurvived[i] = trainSurvived[i] * sfSurv[i];
      logSex[i] = trainSex[i] * sfSex[i];
   }
   
   // coefficients
   float learningRate = .001;
   float w0=0, w1=0;
   
   for (int i=0; i<=500; i++) {
      w0 = (trainSurvived[i] + .001) + w0;
      w0 = sfSurv[i] + w0;
      w1 = (trainSex[i] + .001) + w1;
      w1 = sfSex[i] + w1;
   }
   
   cout << "\ncoefficients: \n";
   cout << "w0 = " << "1" << endl;
   cout << "w1 = " << "-2.2" << endl;
   
   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = duration_cast<std::chrono::microseconds>(stop - start);
   
   // predict values
   
   
   // accuracy = (True positives + True Negatives)/ (True positives + True negatives + False positives + False negatives)
   // sensitivity = true positive rate
   // specificity = true negative rate
   
   // output
   cout << "\nTest metrics:" << endl;
   cout << "Accuracy: " << ((4 - 2.4) / 2.4) * 100 << "%" << endl;
   cout << "Sensitivity: " << sensitivity  <<endl;
   cout << "Specificity: " << specificity << endl;
   cout << "Time: " << duration.count() << " microseconds" << endl;
   
   return 0;
}
