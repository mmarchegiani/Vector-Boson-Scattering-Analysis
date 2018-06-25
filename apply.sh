# !/bin/sh
# Script per lanciare più volte la regression. Il primo argomento indica il numero di trees (NTrees) per la BDT.


root -l ApplyRegression.cxx\(\"BDTG\"\,\"100\"\)
root -l ApplyRegression.cxx\(\"BDTG\"\,\"200\"\)
root -l ApplyRegression.cxx\(\"BDTG\"\,\"400\"\)
root -l ApplyRegression.cxx\(\"BDTG\"\,\"800\"\)
root -l ApplyRegression.cxx\(\"BDTG\"\,\"1600\"\)
#r00t ApplyRegression.cxx\(\"BDTG\"\,\"2000\"\)

