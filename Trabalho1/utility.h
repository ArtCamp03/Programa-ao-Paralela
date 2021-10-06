#ifndef UTILITY_H
#define UTILITY_H
#include <random>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>

std::random_device rd;           // seed generator

std::mt19937_64 generator{rd()}; // generator initialized with seed

static const unsigned int NUM_THREADS = 4;

std::uniform_int_distribution<> initialize(unsigned long long int modulus)
{
  std::uniform_int_distribution<> unifDist{0, (int)(modulus - 1)};
  return unifDist;
}

class xorShift128PlusGenerator
{
public:
  xorShift128PlusGenerator()
  {
    state[0] = rd();
    state[1] = rd();
  };

  unsigned long int next()
  {
    unsigned long int x = state[0];
    unsigned long int const y = state[1];
    state[0] = y;
    x ^= x << 23;                             // a
    state[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return state[1] + y;
  }

private:
  std::random_device rd; // seed generator
  unsigned long int state[2];
};

void unifRandVectorThreadRoutine(std::vector<unsigned int> &vector, unsigned int start, unsigned int end)
{
  xorShift128PlusGenerator prng;
  for (unsigned int i = start; i < end; ++i)
  {
    vector[i] = prng.next();
  }
}

std::vector<unsigned int> uniformRandomVector(unsigned int number_of_values, unsigned long long int modulus)
{
  std::uniform_int_distribution<> dist = initialize(modulus);
  std::thread threads[NUM_THREADS]; //number of threads
  
  std::vector<unsigned int> v;
  v.resize(number_of_values);
  // number of entries each thread will take care of
  unsigned int positionsEachThread = number_of_values / NUM_THREADS;
  // all but the last thread
  for (unsigned int i = 0; i < NUM_THREADS - 1; ++i)
  {
    threads[i] = std::thread(unifRandVectorThreadRoutine, std::ref(v), i * positionsEachThread,(i + 1) * positionsEachThread);
    // threads[i].join();
  }
  // last thread
  threads[NUM_THREADS - 1] = std::thread(unifRandVectorThreadRoutine, std::ref(v), (NUM_THREADS - 1) * positionsEachThread, number_of_values);
  // threads[NUM_THREADS - 1].join();
  for (unsigned int i = 0; i < NUM_THREADS; ++i)
  {
    threads[i].join();
  }
  return v;
}
#endif