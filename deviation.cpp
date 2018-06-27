/*
compile with:
g++ deviation.cpp -o deviation.o `root-config --cflags --glibs`
*/

//This program fits the angular correlation graph of gamma-gamma emission from Co60

#include <fstream>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <string>
#include <TLegend.h>
#include <cmath>

int main(int argc, char **argv) {
	if(argc < 2) {
		std::cout << "Errore: inserire file sorgente come argomento." << std::endl;
		return 1;
	}

	const int n = 50;
	//char *method[n];
	double shrink[n], mean[n], rms[n];

	std::ifstream infile(argv[1]);
	int j = 0;
	char buffer[20];
	infile >> buffer >> buffer >> buffer >> buffer;
	while(infile.good()) {
		//infile >> method[j] >> shrink[j] >> mean[j] >> rms[j];
		infile >> buffer >> shrink[j] >> mean[j] >> rms[j];
		j++;
	}
	infile.close();
	int npoints = j;

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraph *deviation = new TGraph(npoints-1, shrink, mean);
	TGraph *RMS = new TGraph(npoints-1, shrink, rms);

	deviation->SetTitle("deviation vs Shrinkage; Shrinkage; Deviation");
	deviation->SetMarkerColor(kBlue);
	deviation->SetLineColor(kBlue);
	deviation->SetMarkerStyle(7);
	deviation->SetMarkerSize(5);

	RMS->SetTitle("RMS vs Shrinkage; Shrinkage; RMS");
	RMS->SetMarkerColor(kRed);
	RMS->SetLineColor(kRed);
	RMS->SetMarkerStyle(7);
	RMS->SetMarkerSize(5);

	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("Shrinkage","Shrinkage",800,600);
	c1->Divide(2,1);
	c1->cd(1);
	deviation->Draw("ape");
	c1->cd(2);
	RMS->Draw("ape");
	c1->Print("Shrinkage/deviation.png");

	Grafica->Run();
	return 0;
}
