#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

vector < int > encryptSimple(string key, vector < char > list);
vector < int > readOfEncryptedFile(string inputFileName);
vector < char > readOfFile(string inputFileName);
vector < char > decryptSimple(vector < int > listOfEncryptedNumbers, string key);
vector < int > encryptComplicated(string key, vector < char > list);
vector < char > makingPassList(string key, int size);
vector < char > decryptComplicated(vector < int > listOfEncryptedNumbers, string key);
void writeOnDecryptedFile(vector < int > encrypted, string outputFilename);
void writeOnFile(vector < char > list, string outputFilename);
void process_command(string EncryptOrDecrypt, string simpleOrComplicated, string key, string inputFileName, string outputFilename);

int main() {
  string EncryptOrDecrypt, simpleOrComplicated, inputFileName, key, outputFilename;
  cin >> EncryptOrDecrypt >> simpleOrComplicated >> key >> inputFileName >> outputFilename;
  process_command(EncryptOrDecrypt, simpleOrComplicated, key, inputFileName, outputFilename);
  return 0;
}

void process_command(string EncryptOrDecrypt, string simpleOrComplicated, string key, string inputFileName, string outputFilename) {
  vector < int > encrypted;
  vector < char > list;
  vector < int > listOfEncryptedNumbers;
  vector < char > passlist;
  if (EncryptOrDecrypt == "encrypt") {
    list = readOfFile(inputFileName);
    if (simpleOrComplicated == "simple") {
      encrypted = encryptSimple(key, list);
    }
    if (simpleOrComplicated == "complicated") {
      encrypted = encryptComplicated(key, list);
    }
    writeOnDecryptedFile(encrypted, outputFilename);
  }

  if (EncryptOrDecrypt == "decrypt") {
    listOfEncryptedNumbers = readOfEncryptedFile(inputFileName);
    if (simpleOrComplicated == "simple") {
      list = decryptSimple(listOfEncryptedNumbers, key);
    }
    if (simpleOrComplicated == "complicated") {
      list = decryptComplicated(listOfEncryptedNumbers, key);
    }
    writeOnFile(list, outputFilename);
  }
}

vector < char > makingPassList(string key, int size) {
  int keyindex = 0;
  vector < char > passlist;
  for (int index = 0; index < size; index++, keyindex++) {
    if (key[keyindex] == '\0')
      keyindex = 0;
    passlist.push_back(key[keyindex]);
  }
  return passlist;
}

vector < int > encryptSimple(string key, vector < char > list) {
  vector < int > encrypted;
  vector < char > passlist = makingPassList(key, list.size());
  for (int index = 0; index < passlist.size(); index++) {
    encrypted.push_back(int(passlist[index] + list[index]));
  }
  return encrypted;
}

vector < int > encryptComplicated(string key, vector < char > list) {
  int makingSeed = 0;
  vector < int > complicatedNumbers;
  for (int index = 0; index < key.size(); index++) {
    makingSeed += key[index];
  }
  srand(makingSeed);
  for (int index = 0; index < list.size(); index++) {
    complicatedNumbers.push_back((rand() % 11) + list[index]);
  }
  return complicatedNumbers;
}

void writeOnDecryptedFile(vector < int > encrypted, string outputFilename) {
  ofstream outputfile;
  outputfile.open(outputFilename);
  for (int index = 0; index < encrypted.size(); index++)
    outputfile << encrypted[index] << endl;
  outputfile.close();
}

void writeOnFile(vector < char > list, string outputFilename) {
  ofstream outputfile1;
  outputfile1.open(outputFilename);
  for (int index = 0; index < list.size(); index++)
    outputfile1 << list[index];
  outputfile1.close();
}

vector < int > readOfEncryptedFile(string inputFileName) {
  ifstream inputfile;
  int ch;
  vector < int > list;
  inputfile.open(inputFileName);
  if (!inputfile)
    cout << "could not open the file";
  else
    while (inputfile >> ch) {
      list.push_back(ch);
    }
  inputfile.close();
  return list;
}

vector < char > readOfFile(string inputFileName) {
  char ch;
  vector < char > list;
  ifstream inputfile;
  inputfile.open(inputFileName);
  if (!inputfile)
    cout << "could not open the file";
  else
    while (inputfile.get(ch)) {
      list.push_back(ch);
    }
  inputfile.close();
  return list;
}

vector < char > decryptSimple(vector < int > listOfEncryptedNumbers, string key) {
  vector < char > decryptedList;
  int temp;
  int size = listOfEncryptedNumbers.size();
  vector < char > passlist = makingPassList(key, size);
  for (int index = 0; index < listOfEncryptedNumbers.size(); index++) {
    temp = listOfEncryptedNumbers[index] - passlist[index];
    decryptedList.push_back(temp);
  }
  return decryptedList;
}

vector < char > decryptComplicated(vector < int > listOfEncryptedNumbers, string key) {
  vector < char > list;
  char ch;
  int makingSeed = 0;
  for (int index = 0; index < key.size(); index++) {
    makingSeed += key[index];
  }
  srand(makingSeed);
  for (int index = 0; index < listOfEncryptedNumbers.size(); index++) {
    ch = char((listOfEncryptedNumbers[index]) - (rand() % 11));
    list.push_back(ch);
  }
  return list;
}