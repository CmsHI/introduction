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



