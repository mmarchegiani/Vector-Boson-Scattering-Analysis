# !/bin/sh
# Script per lanciare più volte la regression. Il primo argomento indica il numero di trees (NTrees) per la BDT.

r00t TrainRegression_mlp.cxx\(\"100\"\,\"TMVAReg100.root\"\)
r00t TrainRegression_mlp.cxx\(\"200\"\,\"TMVAReg200.root\"\)
r00t TrainRegression_mlp.cxx\(\"400\"\,\"TMVAReg400.root\"\)
r00t TrainRegression_mlp.cxx\(\"800\"\,\"TMVAReg800.root\"\)
r00t TrainRegression_mlp.cxx\(\"1600\"\,\"TMVAReg1600.root\"\)
