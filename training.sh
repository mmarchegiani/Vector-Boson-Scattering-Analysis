# !/bin/sh
# Script per lanciare più volte la regression. Il primo argomento indica il numero di trees (NTrees) per la BDT.

root -l -q TrainRegression_mlp.cxx\(\"100\"\,\"TMVAReg100.root\"\)
root -l -q TrainRegression_mlp.cxx\(\"200\"\,\"TMVAReg200.root\"\)
root -l -q TrainRegression_mlp.cxx\(\"400\"\,\"TMVAReg400.root\"\)
root -l -q TrainRegression_mlp.cxx\(\"800\"\,\"TMVAReg800.root\"\)
root -l -q TrainRegression_mlp.cxx\(\"1600\"\,\"TMVAReg1600.root\"\)
