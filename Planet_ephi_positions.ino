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
  float jd = julian_date_now (23, 12, 2016, 12, 00);
  Serial.println("JD:" + String(jd));

}

void loop() {


}
//------------------------------------------------------------------------------------------------------------------
float julian_date_now (float day_, float month_, float year_, float hour_, float minute_) { // UTC

  float jd = 0;
  float ut = (hour_ + (minute_ / 60));

  jd = julian_date_0(year_);
  jd += days_to_month(month_) + day_;
  jd += (ut - 12) / 24;
  return jd;
};
//------------------------------------------------------------------------------------------------------------------
float julian_date_0(float year_) {

  float jd0 = (4712 + year_) * 365.24806317;
  Serial.println("JD0:" + String(jd0));//2457389 = 1.1.2016 12:00 UTC / 2451545 = 1.1.2000 12:00 UTC
  return jd0;
};
//------------------------------------------------------------------------------------------------------------------
float days_to_month(float month_) {

  float result = 0;
  for (int m = 1; m < (int)month_; m++) {
    result += (float)day_of_month[m];
  }
  return result;
};
//------------------------------------------------------------------------------------------------------------------

