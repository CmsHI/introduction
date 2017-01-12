# Introduction
Getting started with particle physics research and ROOT. 

## Install ROOT: 
Under "Latest ROOT Releases" download the latest "Pro" release, for this example 6.08/02 2016-12-02, https://root.cern.ch/content/release-60802
Ex: for Ubuntu: https://root.cern.ch/download/root_v6.08.02.Linux-ubuntu16-x86_64-gcc5.4.tar.gz

In linux, unzip the file you downloaded, ex:
```bash
gunzip root_v6.08.02.Linux-ubuntu16-x86_64-gcc5.4.tar.gz 
tar -xvf root_v6.08.02.Linux-ubuntu16-x86_64-gcc5.4.tar
```
Now you have a directory root, say it's in your home folder ~/root
To use root we need to source a script to set some environment variables. 
```bash
source ~/root/bin/thisroot.sh
```
Add that line to your ~/.bashrc or ~/.bash_profile file so that it's always executed when you start the terminal and you can always use root. 

## Running ROOT:
To run root just type root from the command line. 
```bash
root
```
If all goes well you should see a splash screen (which means display is working and you can see plots) and something like this:
```
   ------------------------------------------------------------
  | Welcome to ROOT 6.08/02                http://root.cern.ch |
  |                               (c) 1995-2016, The ROOT Team |
  | Built for linuxx8664gcc                                    |
  | From tag v6-08-02, 2 December 2016                         |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q' |
   ------------------------------------------------------------

root [0]
```
This means root works and you can issue commands to the root interpreter line by line for it to run. This is useful for quickly looking at some data and checking if something is working, however for more serious analysis we'll be writing code that we compile and run. For now let's see a few things we can do from the root command prompt. First let's exit root by typing .q
```
root [0] .q
```

##  Looking inside a Data file
Let's grab a sample input file of real collision data and open it in ROOT, and use this to go over some of the ways we can use the root interpreter. 
```bash
wget http://web.mit.edu/mithig/samples/g.pp-photonHLTFilter-v0-HiForest-tutorial.root
root -l g.pp-photonHLTFilter-v0-HiForest-tutorial.root
```
Next we can type .ls to see something like this:
```
root [0] 
Attaching file g.pp-photonHLTFilter-v0-HiForest-tutorial.root as _file0...
(TFile *) 0x2300530
root [1] .ls
TFile**		g.pp-photonHLTFilter-v0-HiForest-tutorial.root	
 TFile*		g.pp-photonHLTFilter-v0-HiForest-tutorial.root	
  KEY: TTree	ztree;	Jet track tree
```
Here root is telling us it's opened the file, and inside it sees a TTree called ztree. We can open a TBrowser to see what's inside:
```
root [2] TBrowser b
```
![Image of TBrowser](http://web.mit.edu/mithig/tutorial/tbrowser-example.png)

Here we see the differnt leaf types inside the tree, which each stores some type of information about the event. While the specific leaves shown here are arbitrarily chosen and will vary from experiments and analyses, the same general concepts apply so let's go through some of them in detail to get a better understanding of what type of collision data there is and how it's stored.

### Global event variables
Each collision will have some global properties that can be represented by a single number or boolean in the tree. Some examples of this are shown below:
```
isPP              = type int , 0 if PbPb collision data, 1 if pp 
run, event, lumi  = a set of numbers making describing when the event was recorded, the combination should be unique in data
vz                = the z possition of the collision along the beampipe, with 0 being the center of the detector
```

### Information about charged particles
Many colliders, CMS included, detect charged particles with high precision by using a detector called a tracker, where the charged particles deposit energy in points as they traverse, and then algorithms reconstruct the trajectories of individual particles from these points and we can extract information like momentum and the charge of the particle by how it bends in a known magnetic field. We call these reconstructed trajectories tracks, and since there can be many charged particles produced in a single collision, we store the information about tracks as arrays indexed by which track we are looking at. The variables are described below:
```
nTrk              = the total number of reconstructed charged particles, this is a single integer for each collision
trkPt[i]          = the transverse momentum of the i'th particle
trkEta[i]         = the pseudorapidity of the i'th particle, in CMS this ranges from -2.4 to 2.4
trkPhi[i]         = the azimuthal angle of the i'th particle, from -pi/2 to pi/2
trkCharge[i]      = the charge of the i'th particle, since we can only reconstruct charged particles this will be -1 or 1
trkWeight[i]      = the correction factor to be applied to the i'th track to account for efficiency and mis-reconstruction 
```

### Information about photons
Photons are reconstructed using the electromagnetic calorimeter in the detector. Like charged particles, there can be multiple photons per collision so we store photon related variables as arrays as well. 
```
nPho              = the number of reconstructed photons, a single integer for each collision
phoE[i]           = the energy of the i'th photon
phoEt[i]          = the transverse energy of the i'th photon
phoEtCorrected[i] = the transverse energy of the i'th photon after applying some corrections
phoEta[i]         = the pseudorapidity of the i'th photon
phoPhi[i]         = the azimuthal angle of the i'th photon
```

### Information about jets
Nature prevents quarks and gluons to exist in a deconfined state that reaches our detector, instead quarks and gluons with high enough momentum will produce lots of particles around themselves and appear in a detector as a collimated spray of particles, which we call a jet. Due to energy and momentum conservation we know that the sum of the total energy and momentum of all the particles in the jet must equal the initial energy and momentum of the quark or gluon the jet originated from. However we don't know for sure which particles are part of the jet and which don't, so we rely on algorithms to both decide and define what is measured as a "jet" . While jets occur more rarely than charged particles, there can still be multiple jets per collision so we also store jet related variables in arrays.
```
njet              = the number of reconstructed jets, a single integer for each collision
jetpt[i]          = the transverse momentum of the i'th jet
jetptCorr[i]      = the transverse momentum of the i'th jet after applying some corrections
jeteta[i]         = the pseudorapidity of the i'th jet
jetphi[i]         = the azimuthal angle of the i'th jet
```

While the names and types of variables you'll encounter in data will be different than these, there idea that certain variables describe a collision, and other variables describe objects within that collision is a general concept. 

## Making quick plots from ROOT
Open the file described above and the TBrowser until you get to the same image as shown above. If you just double click on the variable called nTrk you should see an image like the one below, this shows us the distribution of the number of charged particle per collision, for all collisions in the file that we opened. Try right clicking on the plot and changing the y-axis to log scale and discover what other tools are available to us for manipulating plots. 
![Image of TBrowser](http://web.mit.edu/mithig/tutorial/nTrk-example.png)
Next double click on the variable called trkPt and you should see a new plot appear. This plot will be the distribution of the transverse momentum of all reconstructed charged particles, in all collisions in our file. You'll notice that due to the tail of this distribution most points are close to either the X or Y axis. Suppose we want to take a closer look at the distribution of just particles having trkPt < 10 GeV, if we just zoom in on the axis we'll see 3 points due to the binning. To select just the particles having a trkPt < 10 GeV we go to the root command line and type the following:
```
root [3] ztree->Draw("trkPt","trkPt<10")
```
You should have seen something like this in the tutorial on the root website, but let's go over that this line does in detail. Recall when we did .ls , ROOT told us it sees a TTree called ztree. 
```
root [1] .ls
TFile**		g.pp-photonHLTFilter-v0-HiForest-tutorial.root	
 TFile*		g.pp-photonHLTFilter-v0-HiForest-tutorial.root	
  KEY: TTree	ztree;	Jet track tree
```
In C++ terms ztree is a pointer of type TTree, and thus we can use all the functions a TTree has defined. You can see the full list of what TTree's can do here: https://root.cern.ch/doc/v608/classTTree.html . Usually google-ing the class name will lead you to the documentation, although the results surprise you from time to time like when you try to google for TAxis :) 

So our command takes the TTree pointer ztree, and calls the Draw function with two parameters, the first being what we're drawing ```"trkPt"``` and the second being the cut we are applying ```"trkPt<10"``` . What should the command be if we want to see the azimuthal distribution of charged particles having less than 10 GeV of transverse momentum?

The ROOT command line can also show you both what functions a class has available and what parameters they expect as input by typing the ClassName::FunctionName( and pressing tab, for example below I pressed tab after typing ```TTree::Draw(``` :
```
root [8] TTree::Draw(
Long64_t Draw(const char* varexp, const TCut& selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0)
Long64_t Draw(const char* varexp, const char* selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0) 	// *MENU*
void Draw(Option_t* opt)
void Draw(Option_t* option = "")
root [8] TTree::Draw(
```
You see that the Draw command can take up to 5 arguments but only the first is required, the rest being optional. You can do surprisingly many things from just carefully crafted Draw commands. Try to see if you can plot the difference in the phi coordinate of the first photon (index 0 in the array) and all the charged particles in each event, with the result plotted between 0 and pi (since the largest angle between two vectors is pi).


## Analysis code with ROOT
While analyzing data line by line with Draw commands from the ROOT terminal can get you pretty far, there is a limit to what you can achieve. At some point it's necessary to write code that can do arbitrarily complex logic and cuts. There's quite a few concepts and code that needs to be written to analyze a root file from scratch, however here we're going to take a shortcut and have ROOT auto-generate that for us. At some point it's useful to understand how that works as well but for now we can just use it as a black box that lets us use variables from the file in the code. So to generate the code we open the root file again and use ```ztree->MakeClass``` function:

```
root g.pp-photonHLTFilter-v0-HiForest-tutorial.root
root [0] 
Attaching file g.pp-photonHLTFilter-v0-HiForest-tutorial.root as _file0...
(TFile *) 0x268a3e0
root [1] ztree->MakeClass("analysis")
Info in <TTreePlayer::MakeClass>: Files: analysis.h and analysis.C generated from TTree: ztree
(Int_t) 0
root [2]
```

ROOT created two files for us, analysis.h and analysis.C , which we can start from to analyze the data in the root flie. The code in analysis.h is what makes reads in the root file and sets the variables, we can treat this as a black box for now but feel free to try to understand what it does and ask questions about what is happening under the hood. 

The first thing we'll do is modify the analysis.C so that we can compile it into an executable. All we need to add is a main() function to satisfy the compiler. So add the following lines to the end of analysis.C :

```c++
int main(int argc, char *argv[])
{
   return 0;
}

```

