#!/bin/bash

colorstd='\e[0;37m'
colorred='\e[1;31m'
colorgrn='\e[1;32m'
colorylw='\e[1;33m'

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
  consumer='1000'
else
  consumer=$3
fi

echo "Syntax: $0 timeSteps resolution consumers"
echo
echo -e "${colorylw}#############################################################"
echo "  $timer time steps each with 1/$res h and $consumer consumers"
echo "#############################################################"
echo
echo -e "${colorgrn}Running configuration builder... ${colorstd}"
bin/cbuilder $xml $timer $res $consumer
echo -e "${colorgrn}...finished"
echo
echo -e "Running simulation... ${colorstd}"
bin/smgsim $xml
echo -e "${colorgrn}...finished"
echo
echo "Logfile:"
echo -e "__________________________ ${colorstd}"
cat simulation.log
echo -e "${colorgrn}__________________________ ${colorstd}"
echo

if [ "`which Rscript`" != "" ]; then
  echo -e "${colorgrn}Build diagrams... ${colorstd}"
  Rscript rscript
  Rscript RplotAdjustment
  echo -e "${colorgrn}...finished ${colorstd}"
  echo 
  if [ "`which gv`" != "" ]; then
    echo -e "${colorgrn}Run diagrams: ${colorstd}"
    exec gv adjustment.pdf & gv $basename.pdf
  fi
fi
