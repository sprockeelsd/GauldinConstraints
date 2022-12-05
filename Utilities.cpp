/**
 * @file Utilities.cpp
 * @author Sprockeels Damien (damien.sprockeels@uclouvain.be)
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Utilities.h"

using namespace Gecode;
using namespace std;

unordered_map<std::string, int> noteNameToValue;

/**
 * @brief Initializes the map of (Note name, value). Value are based on the 0 notes (A0, F#0, ....) so they can easily be scaled to the different octaves. 
 * Note that the values below A0 are not "realistic notes", as in they are not playable on a piano. Using these values make it easier to compute the value
 * for any octave.
 */
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

/**
 * @brief Takes as an argument a note name(e.g.F#3) and returns its MIDI value
 * 
 * @param note the name of a note 
 * @return int the MIDI value of that note
 */
int noteToMidi(std::string note)
{
    int octave = (int)(note[note.size() - 1] - 48);
    std::string name = note.substr(0, note.size() - 1);

    return noteNameToValue.at(name) + octave * 12;
}