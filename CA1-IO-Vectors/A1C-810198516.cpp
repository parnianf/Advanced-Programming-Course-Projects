#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#define ENCRYPT_NAME "encrypt"
#define DECRYPT_NAME "decrypt"
#define SIMPLE_NAME "simple"
#define COMPLICATED_NAME "complicated"
#define FILE_ERROR "could not open the file"
#define MAX_RANDOM 11

typedef string io_t;
typedef string password_t;
typedef int seed_t;
typedef vector<int> encrypted_t;
typedef vector<char> decreypted_t;


enum cipherType { Encryption, Decrytpion };
enum cipherKind { Simple, Complicated };

struct Cipher
{
  cipherType type;
  cipherKind kind;
};

struct FilePath
{
  string inputFilePath;
  string outputFilePath;
};

Cipher getMethod();
string getKey();
FilePath getIO();
seed_t makeSeed(const password_t& key);
encrypted_t encryptSimple(const password_t& key, const vector<char>& list);
encrypted_t readOfEncryptedFile(const io_t& inputFileName);
encrypted_t encryptComplicated(const password_t& key, const vector<char>& list);
encrypted_t processEncrypt(const Cipher &cipher, const password_t &key,vector<char> plainText);
decreypted_t readOfPlainFile(const io_t& inputFileName);
decreypted_t decryptSimple(const encrypted_t& encryptedNumbers, const password_t& key);
decreypted_t processDecrypt(const Cipher &cipher, const password_t &key,vector<int> encrypted);
decreypted_t decryptComplicated(const encrypted_t& encryptedNumbers, const password_t& key);
vector<char> makePassList(const password_t& key, const int size);
void writeOnEncryptedFile(const encrypted_t& encrypted, const io_t& outputFilename);
void writeOnDecryptedFile(const decreypted_t& list, const io_t& outputFilename);
void processOutput(const Cipher &cipher, const password_t &key, const FilePath &io);

int main()
{
  Cipher cipher = getMethod();
  password_t key = getKey();
  FilePath io = getIO();
  processOutput(cipher, key, io);
  return 0;
}

Cipher getMethod()
{
  string cipherType, cipherKind;
  cin >> cipherType >> cipherKind;
  Cipher cipher;
  cipher.type = cipherType == ENCRYPT_NAME ? Encryption : Decrytpion;
  cipher.kind = cipherKind == SIMPLE_NAME ? Simple : Complicated;
  return cipher;
}

password_t getKey()
{
  password_t key;
  cin >> key;
  return key;
}

FilePath getIO()
{
  FilePath io;
  cin >> io.inputFilePath >> io.outputFilePath;
  return io;
}

void processOutput(const Cipher &cipher, const password_t &key, const FilePath &io)
{
  encrypted_t encrypted,encryptedNumbersList;
  vector<char> plainText,decrypted;
  if (cipher.type == Encryption)
  {
    plainText = readOfPlainFile(io.inputFilePath);
    encrypted = processEncrypt(cipher,key,plainText);
    writeOnEncryptedFile(encrypted, io.outputFilePath);
  }
  if (cipher.type == Decrytpion)
  {
    encryptedNumbersList = readOfEncryptedFile(io.inputFilePath);
    decrypted = processDecrypt(cipher,key,encryptedNumbersList);
    writeOnDecryptedFile(decrypted, io.outputFilePath);
  }
}

encrypted_t processEncrypt(const Cipher &cipher, const password_t &key,vector<char> plainText)
{
  encrypted_t encrypted;
  if (cipher.kind == Simple)
  {
      encrypted = encryptSimple(key, plainText);
  }
  if (cipher.kind == Complicated)
  {
      encrypted = encryptComplicated(key, plainText);
  }
  return encrypted;
}

decreypted_t processDecrypt(const Cipher &cipher, const password_t &key,vector<int> encrypted){
  vector<char> decrypted;
  if (cipher.kind == Simple)
  {
    decrypted = decryptSimple(encrypted, key);
  }
  if (cipher.kind == Complicated)
  {
    decrypted = decryptComplicated(encrypted, key);
  }
  return decrypted;
}

encrypted_t readOfEncryptedFile(const io_t& inputFileName)
{
  ifstream inputfile(inputFileName);
  int ch;
  encrypted_t list;
  if (!inputfile)
    cout << FILE_ERROR;
  else
    while (inputfile >> ch)
    {
      list.push_back(ch);
    }
  return list;
}

decreypted_t readOfPlainFile(const io_t& inputFileName)
{
  char fileCharacter;
  decreypted_t list;
  ifstream inputfile(inputFileName);
  if (!inputfile)
    cout << FILE_ERROR;
  else
    while (inputfile.get(fileCharacter))
    {
      list.push_back(fileCharacter);
    }
  return list;
}

vector<char> makePassList(const password_t& key,const int plainTextSize)
{
  vector<char> passlist;
  for (int index = 0; index < plainTextSize; index++)
  {
    passlist.push_back(key[index % key.size()]);
  }
  return passlist;
}

encrypted_t encryptSimple(const password_t& key,const vector<char>& list)
{
  encrypted_t encrypted;
  vector<char> passlist = makePassList(key, list.size());
  for (int index = 0; index < passlist.size(); index++)
  {
    encrypted.push_back(int(passlist[index] + list[index]));
  }
  return encrypted;
}

encrypted_t encryptComplicated(const password_t& key,const vector<char>& list)
{
  encrypted_t complicatedNumbers;
  srand(makeSeed(key));
  for (int index = 0; index < list.size(); index++)
  {
    complicatedNumbers.push_back((rand() % MAX_RANDOM) + list[index]);
  }
  return complicatedNumbers;
}

void writeOnEncryptedFile(const encrypted_t& encrypted,const io_t& outputFilename)
{
  ofstream outputfile(outputFilename);
  for (int index = 0; index < encrypted.size(); index++)
    outputfile << encrypted[index] << endl;
}

void writeOnDecryptedFile(const decreypted_t& list, const io_t &outputFilename)
{
  ofstream outputfile(outputFilename);
  for (int index = 0; index < list.size(); index++)
    outputfile << list[index];
}


decreypted_t decryptSimple(const encrypted_t& encryptedNumbers,const  password_t& key)
{
  decreypted_t decryptedList;
  int temp;
  int size = encryptedNumbers.size();
  vector<char> passlist = makePassList(key, size);
  for (int index = 0; index < encryptedNumbers.size(); index++)
  {
    temp = encryptedNumbers[index] - passlist[index];
    decryptedList.push_back(temp);
  }
  return decryptedList;
}

decreypted_t decryptComplicated(const encrypted_t& encryptedNumbers,const password_t& key)
{
  decreypted_t list;
  char decryptedCharacter;
  srand(makeSeed(key));
  for (int index = 0; index < encryptedNumbers.size(); index++)
  {
    decryptedCharacter = char((encryptedNumbers[index]) - (rand() % MAX_RANDOM));
    list.push_back(decryptedCharacter);
  }
  return list;
}

seed_t makeSeed(const password_t& key)
{
  int seed = 0;
  for (int index = 0; index < key.size(); index++)
  {
    seed += key[index];
  }
  return seed;
}
