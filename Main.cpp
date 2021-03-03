#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) { //checks if num is a prime number
   bool is_prime = true;
   for(int i = 2; i <= num/2; i++) { //checks if any of the numbers from 2 to half of num
      if(num % i == 0) {            // divides evenly into num
         is_prime = false; //i divides evenly into num iff num is not prime
         break; //stop checking for new factors, as we already know num is not prime
      }
   }
   return is_prime;
}

int nextPrimeGreaterThanDouble(int num) {
   int next_prime = 2*num + 1; //initial check (first possible value)
   while(!isPrime(next_prime)) { //while next_prime is not prime
      next_prime++; //increment next_prime (we will exit the loop when next_prime is prime)
   }

   return next_prime;
}

class Hashmap {
private:
   int* arr;
   int size = 11;
   const double LOAD_FACTOR = 0.5;
public:
   Hashmap() { //default constructor
      arr = new int[11]; //create new array of initial size 11 to store values
      for(int i = 0; i < size; i++) { //set every empty bucket to -1 --> this will denote empty buckets
         arr[i] = -1;
      }
   }

   Hashmap(int arr_size) { //overloaded constructor
      arr = new int[arr_size]; //create new array with arr_size elements
      size = arr_size; //save the size into memory
      for(int i = 0; i < size; i++) { //set every empty bucket to -1 --> this will denote empty buckets
         arr[i] = -1;
      }
   }

   ~Hashmap() { //destructor
      delete arr;
   }

   double currentLoad() { //calculate the current load
      int entries = 0;
      for(int i = 0; i < size; i++) {
         if(arr[i] != -1) {
            entries++; //sum the number of full buckets
         }
      }
      return entries / double(size); //divide number of full buckets by the size of the array
   }

   bool isOverloaded() { //return whether the current load has exceeded the load factor
      return currentLoad() > LOAD_FACTOR;
   }

   void hashInsert(int key) {
      int i = 0;
      while(arr[(key + i*i) % size] != -1) { //start at key % size position in arr. While the current bucket is non-empty, quadratically probe until we find an empty bucket
         i++;
      }
      arr[(key + i*i) % size] = key; //store the key in the empty bucket
   }

   Hashmap* rehash() {
      int new_size = nextPrimeGreaterThanDouble(size);
      Hashmap* new_map = new Hashmap(new_size); //create a new hashmap with a size equal to the next prime number greater than double the current map's size

      for(int i = 0; i < size; i++) { //loop through old hashmap
         if(arr[i] != -1) { //if the bucket is non-empty
            new_map->hashInsert(arr[i]); //insert the value into the new hashmap
         }
      }
      return new_map; //return the address of the new hashmap
   }

   friend ostream& operator<<(ostream& os, const Hashmap& rhs) { //output the hashmap to console
      for(int i = 0; i < rhs.size; i++) { //loop through the hashmap
         if(rhs.arr[i] == -1) { //if current bucket is empty
            os << "_"; //show it is empty
         }
         else { //if current bucket is non-empty
            os << rhs.arr[i]; //output value
         }
         os << " "; //space-separated values
      }
      return os;
   }
};

int main() {

   cout << "Please enter the number of values you would like to enter: ";
   int num_values = 0;
   cin >> num_values;
   cout << endl;

   Hashmap* h1 = new Hashmap();
   for(int i = 0; i < num_values; i++) { //loop the number of times the user wants to input a new value
      if(h1->isOverloaded()) { //if current load exceeds load factor
         Hashmap* temp_ptr = h1; //store address of old hashmap
         h1 = h1->rehash(); //rehash, point h1 to the new hashmap
         delete temp_ptr; //delete old hashmap
      }
      cout << "Enter a value: "; //prompt user for new value
      int new_value = 0;
      cin >> new_value;
      cout << endl;
      h1->hashInsert(new_value); //insert the new value
   }

   cout << *h1; //output final hashmap
   return 0;
}
