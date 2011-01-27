#!/bin/bash

basename='test'
xml=$basename'.xml'

if [ -z $1 ]; then
  timer='10080'
else
  timer=$1
fi

if [ -z $2 ]; then
  res='60'
else
  res=$2
fi

if [ -z $3 ]; then
  consumer='100'
else
  consumer=$3
fi

echo "Syntax: $0 timeSteps resolution consumers"
echo
echo "#############################################################"
echo "  $timer time steps each with 1/$res h and $consumer consumers"
echo "#############################################################"
echo
echo "Running configuration builder..."
bin/cbuilder $xml $timer $res $consumer
echo "...finished"
echo
echo "Running simulation..."
bin/smgsim $xml
echo "...finished"
echo
echo "Build diagram..."
Rscript rscript
echo "...finished"
echo
echo "Run diagram:"
exec gv $basename\_consumed.pdf
