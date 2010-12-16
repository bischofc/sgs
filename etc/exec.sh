#!/bin/bash

xml='test.xml'
pdf='test.pdf'

if [ -z $1 ]; then
  timer='100'
else
  timer=$1
fi

if [ -z $2 ]; then
  consumer='10'
else
  consumer=$2
fi

bin/cbuilder $xml 20 1 $timer $consumer && bin/smgsim $xml && Rscript rscript && gv $pdf
