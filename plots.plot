#!/usr/bin/env plotter.py

rootfile histos
   location="histos.root"
   linecolor=1 #!!!
   desc="t-channel"
   
histo genJMr
   location="SingleTopAnalysis/genJMr"

histo genJMb
   location="SingleTopAnalysis/genJMb"

plot a1
    push=histos.genJMr
    filename="genJMr.png"

plot a2
    push=histos.genJMb
    filename="genJMb.png"
    
print a1
print a2