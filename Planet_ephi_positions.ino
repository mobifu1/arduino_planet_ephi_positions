//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
// Calculation the Positions of Planets by elliptic Orbit in the Solarsystem between Year 2000-2100
// Author: Andreas Jahnke, aajahnke@aol.com
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

// Symbol:   Bedeutung:
//   a      grosse Halbachse
//   e      Exzentrität
//   t0     Zeitpunkt des Periheldurchgangs
//   T      Umlaufzeit
//   Ω      Länge des aufsteigenden Knotens
//   i      Neigung der Bahnebene zur Ekliptik
//   ω      Winkel zwischen Perihel und aufsteigendem Knoten

// Tables:
const int day_of_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
String planet_name[8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun"};
String star_name[1] = {"Sun"};

const float planet_data[8][7] = {// a, e, t0, T, Ω, i, ω
  {0, 0, 0, 0, 0, 0, 0}, // Mercury
  {0, 0, 0, 0, 0, 0, 0}, // Venus
  {0, 0, 0, 0, 0, 0, 0}, // Earth
  {0, 0, 0, 0, 0, 0, 0}, // Mars
  {0, 0, 0, 0, 0, 0, 0}, // Jupiter
  {0, 0, 0, 0, 0, 0, 0}, // Saturn
  {0, 0, 0, 0, 0, 0, 0}, // Uranus
  {0, 0, 0, 0, 0, 0, 0}, // Neptun
};

void setup() {


}

void loop() {


}
