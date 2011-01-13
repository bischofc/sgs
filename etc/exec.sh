#!/bin/bash

basename='test'
xml=$basename'.xml'

if [ -z $1 ]; then
  timer='1440'
else
  timer=$1
fi

if [ -z $2 ]; then
  res='60'
else
  res=$2
fi

if [ -z $3 ]; then
  consumer='1'
else
  consumer=$3
fi

bin/cbuilder $xml $timer $res $consumer && \
    bin/smgsim $xml && \
    Rscript rscript && \
    gv $basename\_total.pdf && \
    gv $basename\_produced.pdf && \
    gv $basename\_bought.pdf && \
    gv $basename\_consumed.pdf
