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





