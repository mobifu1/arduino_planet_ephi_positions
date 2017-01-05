//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
// Calculation the Positions of Planets by elliptic Orbit in the Solarsystem between Year 2000-2100
// http://denknix.com/astro/doc/html/section003.html
// http://ssd.jpl.nasa.gov/horizons.cgi
// http://www.jgiesen.de/kepler/kepler.html   Java applet: keppler equation
// Author: Andreas Jahnke, aajahnke@aol.com
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
#include <math.h>
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
  {0.38709927, 0.00000037, 0.20563593, 0.00001906, 7.00497902, -0.00594749, 252.25032350, 149472.67411175, 77.45779628, 0.16047689, 48.33076593, -0.12534081}, // Mercury
  {0.72333566, 0.00000390, 0.00677672, -0.00004107, 3.39467605, -0.00078890, 181.97909950, 58517.81538729, 131.60246718, 0.00268329, 76.67984255, -0.27769418}, // Venus
  {1.00000261, 0.00000562, 0.01671123, -0.00004392, -0.00001531, -0.01294668, 100.46457166, 35999.37244981, 102.93768193, 0.32327364, 0, 0},                    // Earth
  {1.52371034, 0.00001847, 0.09339410, 0.00007882, 1.84969142, -0.00813131, -4.55343205, 19140.30268499, -23.94362959, 0.44441088, 49.55953891, -0.29257343},   // Mars
  {5.20288700, -0.00011607, 0.04838624, -0.00013253, 1.30439695, -0.00183714, 34.39644051, 3034.74612775, 14.72847983, 0.21252668, 100.47390909, 0.20469106},   // Jupiter
  {9.53667594, -0.00125060, 0.05386179, -0.00050991, 2.48599187, 0.00193609, 49.95424423, 1222.49362201, 92.59887831, -0.41897216, 113.66242448, -0.28867794},  // Saturn
  {19.1891646, -0.00196176, 0.04725744, -0.00004397, 0.77263783, -0.00242939, 313.23810451, 428.48202785, 170.95427630, 0.40805281, 074.01692503, 0.04240589}, // Uranus
  { 30.06992276, 0.00026291, 0.00859048, 0.00005105, 1.77004347, 0.00035372, -55.12002969, 218.45945325, 44.96476227, -0.32241464, 131.78422574, -0.00508664}, // Neptun
};


// global factors:
const float rad = 0.017453293; // deg to rad
const float deg = 57.29577951; // rad to deg
const float pi = 3.1415926535; //PI
float jd = 0;                  //Juliane date
float eclipticAngle0 = (23.43928) * rad;

//global coordinates:
float x_coord;
float y_coord;
float z_coord;

//------------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);
  delay(500);
  jd = get_julian_date (04, 01, 2017, 18, 0, 0);
  //jd = 2457752.8875;
  Serial.println("JD:" + String(jd, DEC));
  get_object_position (1, jd);
  get_object_position (2, jd);

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

  float H = (hour_ / 24) + (minute_ / 1440) + (seconds_ / 86400);
  float B = 2 - (long)(year_ / 100)  + (long)(year_ / 100 / 4);
  float jd = (long)(365.25 * (year_ + 4716)) + (long)(30.6001 * (month_ + 1)) + day_ + B + H - 1524.5;
  return jd;

}
// =========================================================================
// object position
// =========================================================================
void get_object_position (int object_number, float jd) {

  Serial.println("----------------------------------------------------");
  Serial.println("Object:" + object_name[object_number]);

  float T = (jd - 2451545) / 36525;
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

  inclination = calc_format_angel_deg (inclination);
  Serial.println("inclination:" + String(inclination, DEC));

  meanLongitude = calc_format_angel_deg (meanLongitude);
  Serial.println("meanLongitude:" + String(meanLongitude, DEC));

  longitudePerihelion = calc_format_angel_deg (longitudePerihelion);
  Serial.println("longitudePerihelion:" + String(longitudePerihelion, DEC));

  longitudeAscendingNode = calc_format_angel_deg (longitudeAscendingNode);
  Serial.println("longitudeAscendingNode:" + String(longitudeAscendingNode, DEC));

  meanAnomaly = calc_format_angel_deg (meanAnomaly);
  Serial.println("meanAnomaly:" + String(meanAnomaly, DEC));

  argumentPerihelion = calc_format_angel_deg (argumentPerihelion);
  Serial.println("argumentPerihelion:" + String(argumentPerihelion, DEC));
  //---------------------------------
  float eccentricAnomaly = calc_eccentricAnomaly(meanAnomaly, eccentricity);
  eccentricAnomaly = calc_format_angel_deg (eccentricAnomaly);
  Serial.println("eccentricAnomaly:" + String(eccentricAnomaly, DEC));
  //---------------------------------
  //to orbital Coordinates:
  Serial.println("orbital Coordinates:");
  calc_orbital_coordinates (semiMajorAxis, eccentricity, eccentricAnomaly);
  //---------------------------------
  //to heliocentric Ecliptic Position:
  Serial.println("heliocentric Ecliptic Position:");
  //print_xyz();
  rot_z (argumentPerihelion);
  //print_xyz();
  rot_x (inclination);
  //print_xyz();
  rot_z (longitudeAscendingNode);
  //print_xyz();
  calc_vector(x_coord, y_coord, z_coord, "");
  //heliocentric ecliptic coordinates :LO :+ 46:07:16  LAT:-  1:43:29  RAD: 0.72
  //---------------------------------

}
//------------------------------------------------------------------------------------------------------------------
float calc_format_angel_deg (float deg) {  //0-360 degrees

  if (deg >= 360 || deg < 0) {
    if (deg < 0) {
      while (deg < 0) {
        deg += 360;
      }
    }
    long x = (long)deg;
    float comma = deg - x;
    long y = x % 360; //modulo 360
    return comma += y;
  }
  return deg;
}
//------------------------------------------------------------------------------------------------------------------
float calc_eccentricAnomaly (float meanAnomaly, float eccentricity) { //271.60 deg   /  0.00677672 rad

  meanAnomaly *= rad;

  int iterations = 0;
  float eccentricAnomaly = meanAnomaly + (eccentricity * sin(meanAnomaly));
  //Serial.println(String(eccentricAnomaly, DEC));
  float deltaEccentricAnomaly = 1;

  while (fabs(deltaEccentricAnomaly) > 0.000001) { // 0.0000001

    deltaEccentricAnomaly = (meanAnomaly - eccentricAnomaly + (eccentricity * sin(eccentricAnomaly))) / (1 - eccentricity * cos(eccentricAnomaly));
    //Serial.println(String(deltaEccentricAnomaly, DEC));
    eccentricAnomaly += deltaEccentricAnomaly;
    //Serial.println(String(eccentricAnomaly, DEC));

    iterations++;
    if (iterations > 20) {
      //Serial.println("Error:Keplergleichung!!!!!");
      eccentricAnomaly = 0;
      break;
    }
  }

  eccentricAnomaly *= deg;
  //eccentricAnomaly = 174.46025007692424;//test
  return eccentricAnomaly;
}
//------------------------------------------------------------------------------------------------------------------
void calc_orbital_coordinates (float semiMajorAxis, float eccentricity, float eccentricAnomaly) {

  eccentricAnomaly *= rad;
  float true_Anomaly = 2 * atan(sqrt((1 + eccentricity) / (1 - eccentricity)) * tan(eccentricAnomaly / 2));
  true_Anomaly *= deg;
  true_Anomaly = calc_format_angel_deg (true_Anomaly);

  float radius = semiMajorAxis * (1 - (eccentricity * cos(eccentricAnomaly)));
  Serial.println("true_Anomaly:" + String(true_Anomaly, DEC));
  Serial.println("radius:" + String(radius, DEC));
  //true_Anomaly  : 278.841
  //radius        : 0.7225

  calc_vector(0, true_Anomaly, radius, "to_rectangular"); // x = beta / y = true_Anomaly / z = radius
  //calc_vector(0, 93.0727, 0.374862, "to_rectangular");//r = 0.374862    v = 93.0727_deg > Test mercury
}
//------------------------------------------------------------------------------------------------------------------
void calc_vector(float x, float y, float z, String mode) { // x = beta / y = true_Anomaly / z = radius  >>>>  true_Anomaly  :   278.841   ,  radius  : 0.7225

  // convert to rectangular coordinates:
  if (mode == "to_rectangular") {

    x *= rad;
    y *= rad;

    Serial.println("x:" + String(x, DEC));
    Serial.println("sin(x):" + String(sin(x), DEC));

    x_coord = z * cos(x) * cos(y);
    y_coord = z * cos(x) * sin(y);
    z_coord = z * sin(x);

    x = x_coord; // x_coord:0.1754642100
    y = y_coord; // y_coord:-0.7004733100
    z = z_coord; // z_coord:0.0000000000
  }

  Serial.println("x_coord:" + String(x, DEC));
  Serial.println("y_coord:" + String(y, DEC));
  Serial.println("z_coord:" + String(z, DEC));


  // convert to spherical coordinates:
  //get Longitude:
  float lon = atan2(y, x);
  lon *= deg;
  lon = calc_format_angel_deg (lon);
  Serial.println("LON:" + String(lon, DEC));//282 deg
  format_angle("degrees", lon);


  //get Latitude:
  float lat = atan2(z, (sqrt(x * x + y * y)));//0.1328591599494871
  lat *= deg;// 8.9 deg ???
  lat = calc_format_angel_deg (lat);
  Serial.println("LAT:" + String(lat, DEC));
  format_angle("degrees-latitude", lat);


  //getDistance:
  float dist = sqrt(x * x + y * y + z * z);
  Serial.println("DIS:" + String(dist, DEC));
  // orbital coordinates :LO :+282:32:27  LAT:+  0:00:00  RAD: 0.72
}
//------------------------------------------------------------------------------------------------------------------
void format_angle(String format, float angle) {

  int d = 0;
  int m = 0;
  int s = 0;
  int h = 0;
  float rest = 0;
  String sign = "";

  if (format == "degrees" || format == "degrees-latitude") {

    rest = calc_format_angel_deg (angle);

    if (format == "degrees-latitude" && rest > 90) {
      rest -= 360;
    }
    if (rest >= 0) {
      sign = "+";
    }
    else {
      sign = "-";
    }

    rest = fabs(rest);
    d = (int)(rest);
    rest = (rest - (float)d) * 60;
    m = (int)(rest);
    rest = (rest - (float)m) * 60;
    s = (int)rest;
    Serial.println(sign + String(d) + ":" + String(m) + ":" + String(s));
  }

  if (format == "degrees-simple" || format == "degrees-simple-latitude") {

    float a = calc_format_angel_deg (angle);
    if (format == "degrees-simple-latitude" && a > 90) {
      a -= 360;
    }
    Serial.println("a:" + String(a));
  }

  if (format == "hours") {
    rest = 0;
    rest = calc_format_angel_deg (angle) * 24 / 360;
    h = (int)(rest);
    rest = (rest - h) * 60;
    m = (int)(rest);
    rest = (rest - m) * 60;
    s = (int)(rest);
    Serial.println(sign + String(h) + ":" + String(m) + ":" + String(s));
  }
}
//--------------------------------------------------------------------------------------------------------------------
void rot_x(float alpha) {

  alpha *= rad;
  float y = cos(alpha) * y_coord - sin(alpha) * z_coord;
  float z = sin(alpha) * y_coord + cos(alpha) * z_coord;
  y_coord = y;
  z_coord = z;
}
//------------------------------------------------------------------------------------------------------------------
void rot_y (float alpha) {

  alpha *= rad;
  float x = cos(alpha) * x_coord + sin(alpha) * z_coord;
  float z = sin(alpha) * x_coord + cos(alpha) * z_coord;
  x_coord = x;
  z_coord = z;
}
//------------------------------------------------------------------------------------------------------------------
void rot_z (float alpha) {

  alpha *= rad;
  float x = cos(alpha) * x_coord - sin(alpha) * y_coord;
  float y = sin(alpha) * x_coord + cos(alpha) * y_coord;
  x_coord = x;
  y_coord = y;
}
//------------------------------------------------------------------------------------------------------------------
void print_xyz() {

  Serial.println("xyz:" + String(x_coord, DEC) + "," + String(y_coord, DEC) + "," + String(z_coord, DEC));
}
