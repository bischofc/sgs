#!/bin/bash

basename='test'
xml=$basename'.xml'

timer='20'
producer='1'

if [ -z $1 ]; then
  timer='20'
else
  timer=$1
fi

if [ -z $2 ]; then
  consumer='2'
else
  consumer=$2
fi

bin/cbuilder $xml $timer $consumer && bin/smgsim $xml && Rscript rscript && gv $basename\_total.pdf && gv $basename\_produced.pdf && gv $basename\_consumed.pdf
