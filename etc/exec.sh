#!/bin/bash

colorstd='\e[0;37m'
colorred='\e[1;31m'
colorgrn='\e[1;32m'
colorylw='\e[1;33m'

basename='test'
xml=$basename'.xml'

if [ -z $1 ]; then
  timer='7'
else
  timer=$1
fi

if [ -z $2 ]; then
  consumer='1000'
else
  consumer=$2
fi

echo "Syntax: $0 [days [consumers]]"
echo
echo -e "${colorylw}###################################"
echo "  $timer day(s) with $consumer consumer(s)"
echo "###################################"
echo
echo -e "${colorgrn}Running configuration builder... ${colorstd}"
bin/cbuilder $xml $timer $consumer
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
  Rscript etc/plotGraphs
  echo -e "${colorgrn}...finished ${colorstd}"
  echo 
  if [ "`which gv`" != "" ]; then
    echo -e "${colorgrn}Run diagrams: ${colorstd}"
    exec gv adjustment.pdf > /dev/null 2>&1 & gv consumer.pdf > /dev/null 2>&1 & gv producer.pdf > /dev/null 2>&1 & gv actual_production.pdf > /dev/null 2>&1
  fi
fi
