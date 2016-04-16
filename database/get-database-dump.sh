#!/bin/bash

FTP_SERVER="heasarc.gsfc.nasa.gov"
FTP_USERNAME="anonymous"
FTP_PASSWORD=""

DIR="heasarc/dbase/dump"
FILES=( "heasarc_grbcat.tdat" "heasarc_grbcatag.tdat" "heasarc_grbcatann.tdat" "heasarc_grbcatbox.tdat" "heasarc_grbcatcirc.tdat" "heasarc_grbcatdual.tdat" "heasarc_grbcatflux.tdat" "heasarc_grbcatint.tdat" "heasarc_grbcatinta.tdat" "heasarc_grbcatirr.tdat" )
GUNZIP_EXT=".gz"


################################################################################
#
# FILE: heasarc_grbcat.tdat
#
################################################################################
TIME_DEF_1_TARGET="Earth Crossing Time"
TIME_DEF_1_SOURCE=( "Earth-Crossing Time" "Earth-Crossing-Time" )

TIME_DEF_2_TARGET="Not Specified"
TIME_DEF_2_SOURCE=("Not specified" "Not Specified\." )

TIME_DEF_3_TARGET="Trigger Time"
TIME_DEF_3_SOURCE=( "Trigger time" )

INVALID_ROWS=( 10076 10098 10113 10117 )


function unify_strings()
{
  local FILE_DUMP=$1".dump"
  local FILE_HELP=$1".help"
  local TARGET="$2"
  local SOURCE="$3"
  
  echo "Check $SOURCE = $(grep "$SOURCE" $FILE_DUMP | wc -l)"
  sed "s/$SOURCE/$TARGET/g" $FILE_DUMP > $FILE_HELP
  mv $FILE_HELP $FILE_DUMP
  echo "Check $SOURCE = $(grep "$SOURCE" $FILE_DUMP | wc -l)"
}

function remove_rows()
{
  local FILE_DUMP=$1".dump"
  local FILE_HELP=$1".help"
  local REF_ID=$2
  echo "Removing reference_number = $REF_ID"
  cat $FILE_DUMP | egrep -v "^$REF_ID" > $FILE_HELP
  mv $FILE_HELP $FILE_DUMP
}

function filter_heasarc_grbcat()
{
  local FILE=$1
  local FILE_DUMP=$FILE".dump"
  local FILE_FILT=$FILE".filtered"
  local STR
  local REF
  echo "FILE $FILE -> $FILE_DUMP"
  cat $FILE | grep "|" > $FILE_DUMP
  
  for STR in "${TIME_DEF_1_SOURCE[@]}"; do
    unify_strings $FILE "$TIME_DEF_1_TARGET" "$STR"
  done

  for STR in "${TIME_DEF_2_SOURCE[@]}"; do
    unify_strings $FILE "$TIME_DEF_2_TARGET" "$STR"
  done

  for STR in "${TIME_DEF_3_SOURCE[@]}"; do
    unify_strings $FILE "$TIME_DEF_3_TARGET" "$STR"
  done
    
  for REF in "${INVALID_ROWS[@]}"; do
    remove_rows $FILE $REF
  done
  
  mv $FILE_DUMP $FILE_FILT
}

function main_func()
{
  local FILE
  for FILE in ${FILES[@]}; do
    if [ -f $FILE ]; then
      filter_heasarc_grbcat $FILE
    fi
  done
}

main_func