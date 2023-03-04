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
   
   auto start = std::chrono::high_resolution_clock::now();
   
   // create train and test sets
   int trainAge[800];
   int trainPclass[800];
   int trainSex[800];
   int trainSurvived[800];
   
   int testAge[300];
   int testPclass[300];
   int testSex[300];
   
   // for loop to add first 800 elements
   for (int i = 0; i <= 799; i++) {
      trainAge[i] = age[i];
      trainPclass[i] = pclass[i];
      trainSex[i] = sex[i];
      trainSurvived[i] = survived[i];
   } // for loop
   
   // naive bayes
   float liklihood, classProb, predProb;
   double counter1=0, counter2 = 0, counter3=0;
   
   // find frequency of survived
   for(int i=0; i<=799; i++) {
      if(trainSurvived[i] == 1) {
         counter1++;
      } else {
         continue;
      }
   } // for loop
   
   for(int i=0; i<=799; i++) {
      if(trainSex[i] == 1) {
         counter2++;
      } else {
         continue;
      }
   } // for loop
   
   for(int i=0; i<=799; i++) {
      if(trainPclass[i] == 1) {
         counter3++;
      } else {
         continue;
      }
   } // for loop
   
   int sum=0;
   
   for(int i=0; i<=799; i++) {
      sum += trainAge[i];
   }
   int avg = sum / 800;
   //cout << avg << endl;
   
   // probabilities
   classProb = (468.0 / 800.0); // probability they survive over train
   double sexProb = (573/800.0); // probability of sex over train
   double pClassProb = (214/800.0); // probability of pclass over train
   //cout << pClassProb << endl;
   
   // survived based on sex
   double prob1 = (classProb * sexProb) * 100;
   cout << "\nSurvived based on sex: " << prob1 << "%" << endl;
   // survived based on pclass
   double prob2 = (classProb * pClassProb) * 100;
   cout << "Survived based on pclass: " << prob2 << "%" << endl;
   // survived based on age
   double prob3 = (classProb * avg);
   cout << "Survived based on age: " << prob3 << "%"<< endl;
   
   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = duration_cast<std::chrono::microseconds>(stop - start);
   cout << "\nTime: " << duration.count() << " microseconds" << endl;

   
}
