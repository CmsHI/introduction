#!/bin/bash

# get the input file if needed
[[ ! -e ntD_pp_HeavyFlavor_goldenjson.root ]] && { curl -O http://web.mit.edu/mithig/samples/ntD_pp_HeavyFlavor_goldenjson.root ; }


## hi2
#INPUTDATA=/export/d00/scratch/jwang/scratchHome/mithiSamples/ntD_pp_HeavyFlavor_goldenjson.root
INPUTDATA=ntD_pp_HeavyFlavor_goldenjson.root

CUTTRIGGER="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
CUT="Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dpt>20.&&Dy>-1&&Dy<1"
OUTPUT="outputfiles/massSpectrum.root"

#

FOLDERS=("outputfiles" "plots")
for i in ${FOLDERS[@]} ; do mkdir -p $i ; done ;

#

root -l -b -q "savehist.C+("\"$INPUTDATA\",\"$CUTTRIGGER\",\"$CUT\",\"$OUTPUT\"")"
root -l -b -q "fitD.C+("\"$OUTPUT\"")"


rm *.d
rm *.pcm
rm *.so
