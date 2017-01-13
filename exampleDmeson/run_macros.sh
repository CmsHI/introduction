#!/bin/bash

DO_SAVEHIST=1
DO_FIT=1

#

## svmithi02 @ lxplus 
#INPUTDATA="/data/wangj/TutorialsSamples/rootTutorial/ntD_pp_HeavyFlavor_goldenjson.root"
## hidsk0001 @ cgate
INPUTDATA="/export/d00/scratch/jwang/TutorialsSamples/ntD_pp_HeavyFlavor_goldenjson.root"

CUTTRIGGER="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
CUT="Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dpt>20.&&Dy>-1&&Dy<1"
OUTPUT="outputfiles/massSpectrum.root"

#

FOLDERS=("outputfiles" "plots")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]; then
        mkdir $i
    fi
done

#

if [ $DO_SAVEHIST -eq 1 ]; then
root -b -q "savehist.C+("\"$INPUTDATA\",\"$CUTTRIGGER\",\"$CUT\",\"$OUTPUT\"")"
fi

if [ $DO_FIT -eq 1 ]; then
root -b -q "fitD.C+("\"$OUTPUT\"")"
fi

rm *.d
rm *.pcm
rm *.so