#!/bin/bash

basename='test'
xml=$basename'.xml'

if [ -z $1 ]; then
  processes='1'
else
  processes=$1
fi

if [ -z $2 ]; then
  timer='1440'
else
  timer=$2
fi

if [ -z $3 ]; then
  res='60'
else
  res=$3
fi

if [ -z $4 ]; then
  consumer='1'
else
  consumer=$4
fi

bin/cbuilder $xml $timer $res $consumer && \
    bin/smgsim $xml $processes && \
    Rscript rscript && \
    gv $basename\_total.pdf && \
    gv $basename\_produced.pdf && \
    gv $basename\_bought.pdf && \
    gv $basename\_consumed.pdf
