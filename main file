#include <iostream>
#include "WeatherHMM.h"  // include our new header
using namespace std;


int main() {
    // Example sequence of observed weather
    vector<ObservedState> observedSeq = {
        ObservedState::Sunny,
        ObservedState::Cloudy,
        ObservedState::Rainy,
        ObservedState::Rainy,
        ObservedState::Cloudy


    };

    // Run the Viterbi algorithm
    vector<HiddenState> hiddenPath = viterbi(observedSeq);

    // Print observed states
    cout << "Observed Sequence:\n";
    for (size_t i = 0; i < observedSeq.size(); i++) {
        cout << "Day " << (i + 1) << ": "
            << observedStateToString(observedSeq[i]) << "\n";
    }

    // Print inferred hidden states
    cout << "\nMost Likely Hidden State Path:\n";
    for (size_t i = 0; i < hiddenPath.size(); i++) {
        cout << "Day " << (i + 1) << ": "
            << hiddenStateToString(hiddenPath[i]) << "\n";

    }

}
