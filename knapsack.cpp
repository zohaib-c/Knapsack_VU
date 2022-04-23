#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void print(std::vector<int> sack, std::vector<int> valuesInSack, int total, int sackSize){
  int actualTotal = 0;
  for (int i = 0; i < sack.size(); i++){
    actualTotal = actualTotal + sack.at(i);
  }

  std::cout << "With a capacity of " << sackSize << " kg, the total value is " << total << " Eur, leading to a total weight of " << actualTotal << " kg \n";
  std::cout << "The following items are included: ";

  for (int j = 0; j < sack.size(); j++){
    std::cout << "[" << sack.at(j) << "," << valuesInSack.at(j) << "] ";
  }
}

int knapsack (int count, int sackSize, std::vector<int> weights, std::vector<int> values, std::vector<bool>& present){
  
  if (sackSize == 0 || count == 0){
    return 0;
  } 
   
  if (weights.at(count-1) > sackSize){
    return knapsack(count-1, sackSize, weights, values, present);
  }

  else{
    std::vector<bool> without = present;
    std::vector<bool> with = present;
    int totalValueWith = values.at(count-1) + knapsack(count-1, sackSize-weights.at(count-1), weights, values, with);
    with.at(count-1) = true;

    int totalValueWithout = knapsack(count-1, sackSize, weights, values, without);

    if (totalValueWith > totalValueWithout){
      present = with;
      return totalValueWith;
    }
    else{
      present = without;
      return totalValueWithout;
    }
  }
}


int readFile(std::string fileName, std::vector<int>& weights, std::vector<int>& values){
  std::ifstream file;

  file.open(fileName);
  if (!file.is_open()){
    std::cout << "Could not open file " << fileName;
    return -1;
  }

  int itemSize;
  int itemValue;
  int sackSize;  
  
  file >> sackSize;

  while (!file.eof()){
    file >> itemSize;
    if (!file.fail()){
      weights.push_back(itemSize);
    }

    file >> itemValue;
    if (!file.fail()){
      values.push_back(itemValue);
    }
  }

file.close();

return sackSize;
}


int main(int argc, char *argv[]) {
  std::vector<int> weights;
  std::vector<int> values;
  int sackSize; 

  if (argc > 1){
    std::string fileName(argv[1]);
    sackSize = readFile(fileName, weights, values);
    if (sackSize == -1){
      return 1;
    }
  }

  else{
    std::cout << "No input filename given";
    return 1;
  }

  std::vector<bool> present (weights.size(), false);
  int count = values.size();
  int total = knapsack(count, sackSize, weights, values, present);


  std::vector<int> sack;
  std::vector<int> valuesInSack;

  for (int i = 0; i < present.size(); i++){
    if (present.at(i) == true){
      sack.push_back(weights.at(i));
      valuesInSack.push_back(values.at(i));
    }
  }

  print(sack, valuesInSack, total, sackSize);
return 0;
}