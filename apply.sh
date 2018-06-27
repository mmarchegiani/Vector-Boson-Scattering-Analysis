# !/bin/sh
# Script per lanciare più volte la regression. Il primo argomento indica il numero di trees (NTrees) per la BDT.


root -l -q ApplyRegression.cxx\(\"BDTG\"\,\"100\"\)
root -l -q ApplyRegression.cxx\(\"BDTG\"\,\"200\"\)
root -l -q ApplyRegression.cxx\(\"BDTG\"\,\"400\"\)
root -l -q ApplyRegression.cxx\(\"BDTG\"\,\"800\"\)
root -l -q ApplyRegression.cxx\(\"BDTG\"\,\"1600\"\)
#root -l -q ApplyRegression.cxx\(\"BDTG\"\,\"2000\"\)

