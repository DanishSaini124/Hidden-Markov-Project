#include "WeatherHMM.h"
#include <cmath>        // for log
#include <limits>       // for -INFINITY
#include <stdexcept>    // for runtime_error
using namespace std;


const vector<double> initialProbs = {
    0.5,  // HighPressure
    0.5   // LowPressure
};

const vector<vector<double>> transitions = {
    // HighPressure -> (HighPressure, LowPressure)
    {0.8, 0.2},
    // LowPressure ->  (HighPressure, LowPressure)
    {0.3, 0.7}
};

const vector<vector<double>> emissions = {
    // If HighPressure: {P(Sunny), P(Cloudy), P(Rainy)}
    {0.6, 0.3, 0.1},
    // If LowPressure:  {P(Sunny), P(Cloudy), P(Rainy)}
    {0.2, 0.3, 0.5}
};

// ---------------------------------------------------------------------------
// String conversion functions
// ---------------------------------------------------------------------------
string hiddenStateToString(HiddenState hs) {
    switch (hs) {
    case HiddenState::HighPressure: return "HighPressure";
    case HiddenState::LowPressure:  return "LowPressure";
    }
    return "UnknownHiddenState"; // fallback
}

string observedStateToString(ObservedState os) {
    switch (os) {
    case ObservedState::Sunny:  return "Sunny";
    case ObservedState::Cloudy: return "Cloudy";
    case ObservedState::Rainy:  return "Rainy";
    }
    return "UnknownObservedState"; // fallback
}

// ---------------------------------------------------------------------------
// Helper to map ObservedState -> integer index for emissions
// ---------------------------------------------------------------------------
static int observedStateToIndex(ObservedState os) {
    switch (os) {
    case ObservedState::Sunny:  return 0;
    case ObservedState::Cloudy: return 1;
    case ObservedState::Rainy:  return 2;
    }
    throw runtime_error("Invalid ObservedState in observedStateToIndex");
}

// ---------------------------------------------------------------------------
// Viterbi Algorithm Implementation
// ---------------------------------------------------------------------------
vector <HiddenState> viterbi(const vector<ObservedState>& observations) {
    size_t T = observations.size();
    if (T == 0) {
       //No observations => no hidden states
        return{};

    }

    // We have 2 hidden states (0 = HighPressure, 1 = LowPressure)
    const size_t N_hidden = 2;
    // 1) Create DP tables
    // viterbiProb[t][j] = log probability of the best path up to time t ending in hidden state j
    vector<vector<double>> viterbiProb(
        T,
        vector<double>(N_hidden, -numeric_limits<double>::infinity())
    );
    //    backpointer[t][j] = index of the hidden state at time t-1 that leads to the best path for j at time t
    vector<vector<int>> backpointer(
        T,
        vector<int>(N_hidden, -1)
    );
    // 2) Initialization at t = 0
    for (size_t j = 0; j < N_hidden; j++) {
        double initProb = initialProbs[j];
        double emisProb = emissions[j][observedStateToIndex(observations[0])];
        // Using log probabilities to avoid underflow
        viterbiProb[0][j] = log(initProb) + log(emisProb);
    }

    // 3) Recursion for t = 1..(T-1)
    for (size_t tIndex = 1; tIndex < T; tIndex++) {
        for (size_t currentState = 0; currentState < N_hidden; currentState++) {
            double maxProb = -numeric_limits<double>::infinity();
            int bestPrevState = -1;

            for (size_t prevState = 0; prevState < N_hidden; prevState++) {
                // Transition probability from prevState -> currentState
                double transProb = transitions[prevState][currentState];

                // Emission probability for currentState given the observation at time tIndex
                double emisProb = emissions[currentState][observedStateToIndex(observations[tIndex])];

                // The candidate log probability if we come from prevState
                double candidateProb = viterbiProb[tIndex - 1][prevState]
                    + log(transProb)
                    + log(emisProb);

                if (candidateProb > maxProb) {
                    maxProb = candidateProb;
                    bestPrevState = static_cast<int>(prevState);
                }
            }
            // Store the best path found for (tIndex, currentState)
            viterbiProb[tIndex][currentState] = maxProb;
            backpointer[tIndex][currentState] = bestPrevState;
        }
    }

    // 4) Termination: pick the best final state at time (T-1)
    double maxFinalProb = -numeric_limits<double>::infinity();
    int bestFinalState = -1;
    for (size_t j = 0; j < N_hidden; j++) {
        if (viterbiProb[T - 1][j] > maxFinalProb) {
            maxFinalProb = viterbiProb[T - 1][j];
            bestFinalState = static_cast<int>(j);
        }
    }
    // 5) Backtracking: reconstruct the best path from end to start
    vector<HiddenState> bestPath(T);
    int current = bestFinalState;
    for (int tIndex = static_cast<int>(T) - 1; tIndex >= 0; tIndex--) {
        // Convert the integer index back to an enum
        bestPath[tIndex] = (current == 0) ? HiddenState::HighPressure : HiddenState::LowPressure;
        // Move to the previous state that led to `current`
        current = backpointer[tIndex][current];
    }
    return bestPath;

}
