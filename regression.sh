# !/bin/sh
# Script per lanciare più volte la regression, applicarla e plottare i risultati.
# Il primo argomento indica il numero di trees (NTrees) per la BDT.

#root -l -q regression.cxx\(\"0.1\"\)
root -l -q regression.cxx\(\"0.2\"\)
root -l -q regression.cxx\(\"0.3\"\)
root -l -q regression.cxx\(\"0.4\"\)
root -l -q regression.cxx\(\"0.5\"\)
root -l -q regression.cxx\(\"0.6\"\)
root -l -q regression.cxx\(\"0.7\"\)
root -l -q regression.cxx\(\"0.8\"\)
root -l -q regression.cxx\(\"0.9\"\)
root -l -q regression.cxx\(\"1.0\"\)
root -l -q regression.cxx\(\"0.05\"\)
root -l -q regression.cxx\(\"0.06\"\)
root -l -q regression.cxx\(\"0.07\"\)
root -l -q regression.cxx\(\"0.08\"\)
root -l -q regression.cxx\(\"0.09\"\)
