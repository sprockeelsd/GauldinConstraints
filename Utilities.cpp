#include "Utilities.h"

using namespace Gecode;
using namespace std;

unordered_map<std::string, int> noteNameToValue;

void fillNoteNameToValue()
{
    noteNameToValue["C"] = 12;
    noteNameToValue["C#"] = 13;
    noteNameToValue["Db"] = 13;
    noteNameToValue["D"] = 14;
    noteNameToValue["D#"] = 15;
    noteNameToValue["Eb"] = 15;
    noteNameToValue["E"] = 16;
    noteNameToValue["F"] = 17;
    noteNameToValue["F#"] = 18;
    noteNameToValue["Gb"] = 18;
    noteNameToValue["G"] = 19;
    noteNameToValue["Ab"] = 20;
    noteNameToValue["G#"] = 20;
    noteNameToValue["A"] = 21;
    noteNameToValue["A#"] = 22;
    noteNameToValue["Bb"] = 22;
    noteNameToValue["B"] = 23;
    
}

int noteToMidi(std::string note)
{
    int octave = (int)(note[note.size() - 1] - 48);
    std::string name = note.substr(0, note.size() - 1);

    return noteNameToValue.at(name) + octave * 12;
}