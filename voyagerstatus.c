// Voyager Status 2.0
// Written by Camden Mecklem, 2023
// Released under GPL 3: https://www.gnu.org/licenses/gpl-3.0.en.html

// This is a C rewrite of my Voyager Status bash script from 2021.

// The calculation is pretty simple. I went to https://voyager.jpl.nasa.gov/mission/status/
// and got the distances at that moment, and set CALIBRATION_TIME to the time of my visit.
// This script calculates the seconds elapsed since then, and multiplies them by the velocity
// of each probe. This results in a value similar to the ones shown on the NASA JPL website.

#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

// Unix epoch time from the moment I got the starting values.
const unsigned long long CALIBRATION_TIME = 1639617646;

// Kilometers
const unsigned long long V1_CALIBRATION_DISTANCE = 23175321333;
const unsigned long long V2_CALIBRATION_DISTANCE = 19281870994;

// Kilometers per second
const float V1_VELOCITY = 16.9995;
const float V2_VELOCITY = 15.3741;

// Amount to multiply by for converting kilometers to miles
const float KM_TO_MILES_OPERAND = 0.6213712;

void print_color_str(char* color_str)
{
  if (strcmp(color_str, "--color=red") == 0)
  {
    printf("\e[0;31m");
  }
  else if (strcmp(color_str, "--color=blue") == 0)
  {
    printf("\e[0;34m");
  }
  else if (strcmp(color_str, "--color=green") == 0)
  {
    printf("\e[0;32m");
  }
  else if (strcmp(color_str, "--color=cyan") == 0)
  {
    printf("\e[0;36m");
  }
  else if (strcmp(color_str, "--color=black") == 0)
  {
    printf("\e[0;30m");
  }
  else if (strcmp(color_str, "--color=yellow") == 0)
  {
    printf("\e[0;33m");
  }
  else if (strcmp(color_str, "--color=purple") == 0)
  {
    printf("\e[0;35m");
  }
  else if (strcmp(color_str, "--color=white") == 0)
  {
    printf("\e[0;37m");
  }
  else
  {
    printf("Unrecognized color in argument %s\n", color_str);
  }
}

struct Config {
  int only_show_v1;
  int only_show_v2;
  int use_miles;
};

enum Voyager {One = 0, Two = 1};

void display_distance(unsigned long long distance, struct Config config)
{
  if (config.use_miles) {
    unsigned long long m_distance;
    m_distance = distance * KM_TO_MILES_OPERAND;

    printf("%'llu miles", m_distance);
  } else {
    printf("%'llu kilometers", distance);
  }
};

float get_distance(enum Voyager voyager, unsigned long long seconds_since_calibration)
{
  switch(voyager){
    case 0:
      return (seconds_since_calibration * V1_VELOCITY) + V1_CALIBRATION_DISTANCE;
      break;
    case 1:
      return (seconds_since_calibration * V2_VELOCITY) + V2_CALIBRATION_DISTANCE;
      break;
  }
}

void display_v1(struct Config config, unsigned long long seconds_since_calibration)
{
  float distance;
  distance = get_distance(0, seconds_since_calibration);

  printf("Voyager 1 is ");
  display_distance(distance, config);
  printf(" from the Sun.\n");
};

void display_v2(struct Config config, unsigned long long seconds_since_calibration)
{
  float distance;
  distance = get_distance(1, seconds_since_calibration);

  printf("Voyager 2 is ");
  display_distance(distance, config);
  printf(" from the Sun.\n");
};

struct Config parse_arg(char* arg, struct Config config)
{
  if (strcmp(arg, "-v1") == 0)
  {
    config.only_show_v1 = 1;
  }
  else if (strcmp(arg, "-v2") == 0)
  {
    config.only_show_v2 = 1;
  }
  else if (strcmp(arg, "-m") == 0)
  {
    config.use_miles = 1;
  }
  else if (strncmp(arg, "--color=", 8) == 0)
  {
    print_color_str(arg);
  }
  else
  {
    printf("Unrecognized argument: %s\n", arg);
  }

  return config;
}

int main(int argc, char** argv)
{
  // Enable formatting such as commas for number display
  setlocale(LC_NUMERIC, "");

  struct Config config = {
    .only_show_v1 = 0,
    .only_show_v2 = 0,
    .use_miles = 0
  };

  int i;
  for (i = 1; i < argc; i++) {
    config = parse_arg(argv[i], config);
  };

  unsigned long long seconds_since_calibration;
  seconds_since_calibration = time(0) - CALIBRATION_TIME;

  if (config.only_show_v1)
  {
    display_v1(config, seconds_since_calibration);
  }
  else if (config.only_show_v2)
  {
    display_v2(config, seconds_since_calibration);
  }
  else
  {
    display_v1(config, seconds_since_calibration);
    display_v2(config, seconds_since_calibration);
  }
};
