//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
// Calculation the Positions of Planets by elliptic Orbit in the Solarsystem between Year 2000-2100
// http://denknix.com/astro/doc/html/section003.html
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
const int day_of_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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

  Serial.begin(9600);

  float jd = julian_date_now (23, 4, 2016, 17, 31, 00);
  Serial.println("JD:" + String(jd));

}

void loop() {


}
//------------------------------------------------------------------------------------------------------------------
float julian_date_now (float day_, float month_, float year_, float hour_, float minute_, float seconds_) { // UTC

  if (month_ <= 2) {
    year_ -= 1;
    month_ += 12;
  }

  hour_ = (hour_ / 24) + (minute_ / 1440) + (seconds_ / 86400);
  long B = 2 - (int)(year_ / 100)  + (int)(year_ / 100 / 4);
  float jd = (long)(365.25 * (year_ + 4716)) + (long)(30.6001 * (month_ + 1)) + day_ + hour_ + (float)B - 1524.5;
  return jd;
}
