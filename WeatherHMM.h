#pragma
#ifndef WEATHER_HMM_H
#define WEATHER_HMM_H

#include <string>
#include <vector>
using namespace std;

enum class HiddenState { HighPressure, LowPressure }; // <-- semicolon here
enum class ObservedState { Sunny, Cloudy, Rainy };    // <-- semicolon here


// Convert HiddenState to string
string hiddenStateToString(HiddenState hs);

// Convert ObservedState to string
string observedStateToString(ObservedState os);

// Initial probabilities for hidden states
extern const vector<double> initialProbs;

// Transition probabilities
extern const vector<vector<double>> transitions;

// Emission probabilities
extern const vector<vector<double>> emissions;

// 4) Viterbi function - just the declaration
std::vector<HiddenState> viterbi(const std::vector<ObservedState>& observations);

#endif // WEATHER_HMM_H
