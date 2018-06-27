# !/bin/sh
# Script per plottare gli istogrammi dell'applicazione della regression. Il primo argomento indica il numero di trees (NTrees) per la BDT.

root -l -q PlotRegression.cxx\(\"BDT\"\,\"100\"\)
root -l -q PlotRegression.cxx\(\"BDT\"\,\"200\"\)
root -l -q PlotRegression.cxx\(\"BDT\"\,\"400\"\)
root -l -q PlotRegression.cxx\(\"BDT\"\,\"800\"\)
#root -l -q PlotRegression.cxx\(\"BDT\"\,\"1600\"\)
#root -l -q PlotRegression.cxx\(\"BDT\"\,\"2000\"\)

root -l -q PlotRegression.cxx\(\"BDTG\"\,\"100\"\)
root -l -q PlotRegression.cxx\(\"BDTG\"\,\"200\"\)
root -l -q PlotRegression.cxx\(\"BDTG\"\,\"400\"\)
root -l -q PlotRegression.cxx\(\"BDTG\"\,\"800\"\)
root -l -q PlotRegression.cxx\(\"BDTG\"\,\"1600\"\)
root -l -q PlotRegression.cxx\(\"BDTG\"\,\"2000\"\)

root -l -q PlotRegression.cxx\(\"BDTG2\"\,\"100\"\)
root -l -q PlotRegression.cxx\(\"BDTG2\"\,\"200\"\)
root -l -q PlotRegression.cxx\(\"BDTG2\"\,\"400\"\)
root -l -q PlotRegression.cxx\(\"BDTG2\"\,\"800\"\)
root -l -q PlotRegression.cxx\(\"BDTG2\"\,\"1600\"\)
#root -l -q PlotRegression.cxx\(\"BDTG2\"\,\"2000\"\)

echo "Controllo plots..."
sleep 2
ls -la BDT_AdaBoost/dataset_*/plots/
ls -la BDT_Grad/dataset_*/plots/
ls -la BDT_Grad_nocuts/dataset_*/plots/
