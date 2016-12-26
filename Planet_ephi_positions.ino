//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
// Calculation the Positions of Planets by elliptic Orbit in the Solarsystem between Year 2000-2100
// http://denknix.com/astro/doc/html/section003.html
// Author: Andreas Jahnke, aajahnke@aol.com
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

// Sechs Bahnelemente:
// a: Länge der großen Halbachse
// e: numerische Exzentrizität
// i: Bahnneigung, Inklination
// Ω: Länge/Rektaszension des aufsteigenden Knotens
// ω: Argument der Periapsis, Periapsisabstand
// t: Zeitpunkt der Periapsispassage, Periapsiszeit, Epoche des Periapsisdurchgangs
// T: Umlaufzeit

// Tables:
String object_name[8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun"};
String star_name[1] = {"Sun"};

// http://ssd.jpl.nasa.gov/txt/aprx_pos_planets.pdf
const float object_data[8][7] = {// a, e, i, L, ω, Ω
  {0, 0, 0, 0, 0, 0, 0}, // Mercury
  {0.72333566, 0.00677672, 3.39467605, 181.97909950, 131.60246718, 76.67984255, 0}, // Venus
  {0, 0, 0, 0, 0, 0, 0}, // Earth
  {0, 0, 0, 0, 0, 0, 0}, // Mars
  {0, 0, 0, 0, 0, 0, 0}, // Jupiter
  {0, 0, 0, 0, 0, 0, 0}, // Saturn
  {0, 0, 0, 0, 0, 0, 0}, // Uranus
  {0, 0, 0, 0, 0, 0, 0}, // Neptun
};

void setup() {

  Serial.begin(9600);

  float jd = get_julian_date (26, 12, 2016, 12, 00, 00);
  Serial.println("JD:" + String(jd));

}

void loop() {


}
//------------------------------------------------------------------------------------------------------------------
float get_julian_date (float day_, float month_, float year_, float hour_, float minute_, float seconds_) { // UTC

  if (month_ <= 2) {
    year_ -= 1;
    month_ += 12;
  }

  hour_ = (hour_ / 24) + (minute_ / 1440) + (seconds_ / 86400);
  long B = 2 - (int)(year_ / 100)  + (int)(year_ / 100 / 4);
  float jd = (long)(365.25 * (year_ + 4716)) + (long)(30.6001 * (month_ + 1)) + day_ + hour_ + (float)B - 1524.5;
  return jd;
}
