#!/usr/bin/env bash

# Voyager Status 1.0
# Written by Camden Mecklem, 2021
# Released under GPL 3: https://www.gnu.org/licenses/gpl-3.0.en.html
# This script uses date and bc from GNU coreutils.

# The calculation is pretty simple. I went to https://voyager.jpl.nasa.gov/mission/status/
# and got the distances at that moment, and set CALIBRATION_TIME to the time of my visit.
# This script calculates the seconds elapsed since then, and multiplies them by the velocity
# of each probe. This results in a value similar to the ones shown on the NASA JPL website.

# Unix epoch time from the moment I got the starting values.
CALIBRATION_TIME=1639601110

# Astronomical units
V1_CALIBRATION_DISTANCE=23294850298
V2_CALIBRATION_DISTANCE=19385894076

# Kilometers per second
V1_VELOCITY=16.99995
V2_VELOCITY=15.3741

CURRENT_TIME_UTC=$(date '+%s')
SECONDS_SINCE_CALIBRATION=$(($CURRENT_TIME_UTC - $CALIBRATION_TIME))

declare -A VALID_COLORS

set_up_colors () {
  VALID_COLORS[red]="\e[0;31m"
  VALID_COLORS[blue]="\e[0;34m"
  VALID_COLORS[green]="\e[0;32m"
  VALID_COLORS[cyan]="\e[0;36m"
  VALID_COLORS[black]="\e[0;30m"
  VALID_COLORS[yellow]="\e[0;33m"
  VALID_COLORS[purple]="\e[0;35m"
  VALID_COLORS[white]="\e[0;37m"
}

# Set up default options (show Voyager 1 distance in kilometers)
show_v1=1
show_v2=0
use_miles=0

convert_to_miles () {
  km=$1
  miles_distance=$(echo "${km} * 0.6213712" | bc)
}

format_distance () {
  distance=$1

  if [ $use_miles == 1 ]
  then
    printf "%'.0f" $(echo "${distance} * 0.6213712" | bc)
    echo " miles"
  else
    printf "%'.0f" $distance
    echo " kilometers"
  fi
}

handle_color () {
  color=$1
  set_up_colors
  if [ -v VALID_COLORS[$color] ]
  then
    printf "${VALID_COLORS[$color]}"
  else
    echo "Unrecognized color: $color"
  fi

}

handle_launch_arg () {
  arg=$1

  if [ $arg == "-v1" ]
  then
    show_v1=1
    show_v2=0
  elif [ $arg == "-v2" ]
  then
    show_v1=0
    show_v2=1
  elif [ $arg == "-m" ]
  then
    use_miles=1
  elif [ $arg == "-k" ]
  then
    use_miles=0
  elif [[ $arg == color=* ]]
  then
    handle_color ${arg: 6}
  else
    echo "Unknown launch argument: $arg"
  fi
}

get_v1 () {
  V1_DISTANCE_SINCE_CALIBRATION=$(echo "${SECONDS_SINCE_CALIBRATION} * ${V1_VELOCITY}" | bc)
  V1_FINAL_DISTANCE=$(echo "${V1_DISTANCE_SINCE_CALIBRATION} + ${V1_CALIBRATION_DISTANCE}" | bc)
  echo "Voyager 1 is $(format_distance $V1_FINAL_DISTANCE) away."
}

get_v2 () {
  V2_DISTANCE_SINCE_CALIBRATION=$(echo "${SECONDS_SINCE_CALIBRATION} * ${V2_VELOCITY}" | bc)
  V2_FINAL_DISTANCE=$(echo "${V2_DISTANCE_SINCE_CALIBRATION} + ${V2_CALIBRATION_DISTANCE}" | bc)
  echo "Voyager 2 is $(format_distance $V2_FINAL_DISTANCE) away."
}

main () {
  for i in "${@}"
  do
    handle_launch_arg $i
  done

  if [ $show_v1 == 1 ]
  then
    get_v1
  elif [ $show_v2 == 1 ]
  then
    get_v2
  fi
}

main "$@"