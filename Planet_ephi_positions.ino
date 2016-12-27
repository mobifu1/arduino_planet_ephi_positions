//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
// Calculation the Positions of Planets by elliptic Orbit in the Solarsystem between Year 2000-2100
// http://denknix.com/astro/doc/html/section003.html
// Author: Andreas Jahnke, aajahnke@aol.com
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

// Sechs Bahnelemente:                                                                 / Variable:
// a: Länge der großen Halbachse                                                       / [0] semi major axis in AE
// e: numerische Exzentrizität                                                         / [2] eccentricity
// i: Bahnneigung, Inklination                                                         / [4] inclination
// L                                                                                   / [6] meanLongitude
// ω: Argument der Periapsis, Periapsisabstand                                         / [8] longitude of perihelion
// Ω: Länge/Rektaszension des aufsteigenden Knotens                                    / [10] longitude ascending node

// Tables:
String object_name[8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun"};
String star_name[1] = {"Sun"};

// http://ssd.jpl.nasa.gov/txt/aprx_pos_planets.pdf
const float object_data[8][12] = {// a, aΔ, e, eΔ, i, iΔ,  L, LΔ, ω, ωΔ, Ω, ΩΔ  >>> L2000
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Mercury
  {0.72333566, 0.00000390, 0.00677672, -0.00004107, 3.39467605, -0.00078890, 181.97909950, 58517.81538729, 131.60246718, 0.00268329, 76.67984255, -0.27769418}, // Venus
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Earth
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Mars
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Jupiter
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Saturn
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Uranus
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Neptun
};

// global factors:
const float rad = 0.017453293; // deg to rad
const float deg = 57.29577951; // rad to deg
const float pi = 3.1415926535; //PI
float jd = 0;                  //Juliane date
float eclipticAngle0 = (23.43928) * rad;


//------------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);

  jd = get_julian_date (27, 12, 2016, 14, 00, 00);
  Serial.println("JD:" + String(jd));
  get_object_position (1, jd);

}
//------------------------------------------------------------------------------------------------------------------
void loop() {


}
//------------------------------------------------------------------------------------------------------------------
// =========================================================================
// julian date
// =========================================================================
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
// =========================================================================
// object position
// =========================================================================
void get_object_position (int object_number, float jd) {

  Serial.println("Object:" + object_name[object_number]);

  float T = (jd - 2451545) / 36525.0;
  Serial.println("T:" + String(T, DEC));

  float semiMajorAxis = object_data[object_number][0] + (T * object_data[object_number][1]); // offset + T * delta
  float eccentricity = object_data[object_number][2] + (T * object_data[object_number][3]);
  float inclination = object_data[object_number][4] + (T * object_data[object_number][5]);
  float meanLongitude = object_data[object_number][6] + (T * object_data[object_number][7]);
  float longitudePerihelion = object_data[object_number][8] + (T * object_data[object_number][9]);
  float longitudeAscendingNode = object_data[object_number][10] + (T * object_data[object_number][11]);
  float meanAnomaly = meanLongitude - longitudePerihelion;
  float argumentPerihelion = longitudePerihelion - longitudeAscendingNode;

  Serial.println("semiMajorAxis:" + String(semiMajorAxis, DEC));
  Serial.println("eccentricity:" + String(eccentricity, DEC));
  inclination = calc_modulo_360 (inclination);
  Serial.println("inclination:" + String(inclination, DEC));
  meanLongitude = calc_modulo_360 (meanLongitude);
  Serial.println("meanLongitude:" + String(meanLongitude, DEC));
  longitudePerihelion = calc_modulo_360 (longitudePerihelion);
  Serial.println("longitudePerihelion:" + String(longitudePerihelion, DEC));
  longitudeAscendingNode = calc_modulo_360 (longitudeAscendingNode);
  Serial.println("longitudeAscendingNode:" + String(longitudeAscendingNode, DEC));
  meanAnomaly = calc_modulo_360 (meanAnomaly);
  Serial.println("meanAnomaly:" + String(meanAnomaly, DEC));
  argumentPerihelion = calc_modulo_360 (argumentPerihelion);
  Serial.println("argumentPerihelion:" + String(argumentPerihelion, DEC));

  float eccentricAnomaly = calc_eccentricAnomaly(meanAnomaly, eccentricity);
  eccentricAnomaly = calc_modulo_360 (eccentricAnomaly);
  Serial.println("eccentricAnomaly:" + String(eccentricAnomaly, DEC));

  orbitalCoordinates (semiMajorAxis, eccentricity, eccentricAnomaly);
}
//------------------------------------------------------------------------------------------------------------------
float calc_modulo_360 (float value) {

  if (value >= 360 || value < 0) {
    if (value < 0) {
      value += 360000;
    }
    long x = (long)value;
    float comma = value - x;
    long y = x % 360;
    return comma += y;
  }
  return value;
}
//------------------------------------------------------------------------------------------------------------------
float calc_eccentricAnomaly (float meanAnomaly, float eccentricity) { //271.60 deg   /  0.00677672 rad

  meanAnomaly *= rad;

  float eccentricAnomaly = meanAnomaly + (eccentricity * sin(meanAnomaly));
  float deltaEccentricAnomaly = 1;

  while (abs(deltaEccentricAnomaly) > 0.0000001) {
    deltaEccentricAnomaly = (meanAnomaly - eccentricAnomaly + eccentricity * sin(eccentricAnomaly)) / (1 - eccentricity * cos(eccentricAnomaly));
    //Serial.println(String(deltaEccentricAnomaly, DEC));
    eccentricAnomaly += deltaEccentricAnomaly;
  }

  eccentricAnomaly *= deg;
  return eccentricAnomaly; //174.3823298500084 ????
}
//------------------------------------------------------------------------------------------------------------------
void orbitalCoordinates (float semiMajorAxis, float eccentricity, float eccentricAnomaly) {

  eccentricAnomaly *= rad;
  float lambda = 2 * atan(sqrt((1 + eccentricity) / (1 - eccentricity)) * tan(eccentricAnomaly / 2));
  lambda *= deg;
  lambda = calc_modulo_360 (lambda);

  float radius = semiMajorAxis * (1 - eccentricity * cos(eccentricAnomaly));
  Serial.println("lambda:" + String(lambda, DEC));
  Serial.println("radius:" + String(radius, DEC));
  //lambda  :   271.52
  //radius  : 0.7231735791216789

  calc_vector(0, lambda, radius, "spherical"); // x=beta / y=lambda / z=r

}
//------------------------------------------------------------------------------------------------------------------
void calc_vector(float x, float y, float z, String mode) { // x = beta / y = lambda / z = radius

  x *= rad;

  if (mode == "cartesian") {
  }
  if (mode == "spherical") {//heliocentricOrbital
    // x = beta / y = lambda / z = radius
    x = z * cos(x) * cos(y);
    y = z * cos(x) * sin(y);
    z = z * sin(x);
  }

  //getLongitude:
  float lon;
  if (x > 0 && y > 0) lon = atan(y / x);
  if (x > 0 && y < 0) lon =  2 * pi + atan(y / x);
  if (x > 0 && y == 0)  lon =  0;

  if (x == 0 && y > 0)lon =  pi / 2;
  if (x == 0 && y < 0) lon =  3 * pi / 2;
  if (x == 0 && y == 0) lon =  0;

  if (x < 0 && y > 0)lon =  pi + atan(y / x);
  if (x < 0 && y < 0)lon =  pi + atan(y / x);
  if (x < 0 && y == 0) lon =  pi;
  lon *= deg;
  lon = calc_modulo_360 (lon);
  Serial.println("LON:" + String(lon, DEC));

  //getLatitude:
  float rho = sqrt(x * x + y * y);
  float lat;
  if (rho != 0) {
    lat = atan(z / rho);
  }
  else {
    if (z < 0)
      lat =  -pi / 2;
    if (z > 0)
      lat =  pi / 2;
    if (z == 0)
      lat =  0;
  }
  lat *= deg;
  lat = calc_modulo_360 (lat);
  Serial.println("LAT:" + String(lat, DEC));
  //getDistance:

  float dist = sqrt(x * x + y * y + z * z);
  Serial.println("DIS:" + String(dist, DEC));
  //orbital coordinates :LO :+271:31:00  LAT:+  0:00:00  RAD: 0.72
}
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
