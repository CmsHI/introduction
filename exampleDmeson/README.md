# Plot and fit the invariant mass of D mesons

## Run macros
```
source run_macros.sh
```

## What the macros do

### savehist.C
* Fill a histogram with `Dmass` 
* Plot the histogram and save the plot
* Save the histogram in a root file

### fitD.C
* Read the histogram from the root file produced in savehist.C
* Fit the histogram with a double gaussian and a polynomial to shape signal and background respectively
* Plot signal and background components respectively
* Create and plot legends
* Save the plot
