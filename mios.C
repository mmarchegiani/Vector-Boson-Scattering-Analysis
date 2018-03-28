#define mios_cxx
// The class definition in mios.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("mios.C")
// Root > T->Process("mios.C","some options")
// Root > T->Process("mios.C+")
//

#include "mios.h"
#include <TH2.h>
#include <TStyle.h>

#define nbins 10000

void mios::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   _histo_LHElepton_pt = new TH1F ("lepton_pt","p_{T} momentum of leptons",nbins,0,3000.);
   _histo_LHElepton_eta = new TH1F ("lepton_eta","#eta pseudorapidity of leptons",nbins*0.1,-5,5);
   _histo_LHElepton_phi = new TH1F ("lepton_phi","#phi azimutal angle of leptons",nbins*0.1,-3.5,3.5);
   _histo_LHElepton_id = new TH1F ("lepton_id","Particle ID",36,18,18);
   _histo_LHEparton_pt = new TH1F ("parton_pt","p_{T} momentum of partons",nbins,0,3000.);
   _histo_LHEparton_eta = new TH1F ("parton_eta","#eta pseudorapidity of partons",nbins*0.1,-8,8);
   _histo_LHEparton_phi = new TH1F ("parton_phi","#phi azimutal angle of partons",nbins*0.1,-3.5,3.5);
   _histo_LHEparton_id = new TH1F ("parton_id","Particle ID",36,-18,18);
   _histo_LHEneutrino_pt = new TH1F ("neutrino_pt","p_{T} momentum of neutrinos",nbins,0,3000.);
   _histo_LHEneutrino_eta = new TH1F ("neutrino_eta","#eta pseudorapidity of neutrinos",nbins*0.1,-5,5);
   _histo_LHEneutrino_phi = new TH1F ("neutrino_phi","#phi azimutal angle of neutrinos",nbins*0.1,-3.5,3.5);
   _histo_LHEneutrino_id = new TH1F ("neutrino_id","Particle ID",36,-18,18);
   _histo_metLHE_pt = new TH1F ("met_pt","p_{T} MET",nbins,0,3000.);
   _histo_metLHE_eta = new TH1F ("met_eta","#eta MET pseudorapidity",nbins*0.1,-5,5);
   _histo_metLHE_phi = new TH1F ("met_phi","#phi MET azimutal angle",nbins*0.1,-3.5,3.5);
   _histo_LHEneutrino_ptsum = new TH1F ("neutrino_pt_sum","p_{T} neutrinos momentum sum",nbins,0,3000.);
   _histo_LHEneutrino_phisum = new TH1F ("met_phi_sum","#phi_{sum} azimutal angle ",nbins*0.1,-3.5,3.5);
   _histo_jj_deltaeta = new TH1F ("jj_deltaeta", "#Delta#eta_{jet-jet}", nbins*0.1, 0, +16);
   _histo_jj_m = new TH1F ("jj_m", "M_{jet-jet}", nbins, -1000, +1000);
   _histo_leptons_per_event = new TH1F ("leptons per event", "Leptoni+neutrini per evento", latino->GetEntries(), 0, latino->GetEntries());
   _histo_partons_per_event = new TH1F ("partons per event", "Partoni per evento", latino->GetEntries(), 0, latino->GetEntries());
   TString option = GetOption();

}

void mios::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t mios::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either mios::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   GetEntry(entry);
   //std::cout << std_vector_LHElepton_pt->size() << std::endl;
   //std::cout << entry << std::endl;

   int i = 0, j;
   for(j = 0; j < std_vector_LHEparton_pt->size(); j++) {
	//if(std_vector_LHEparton_pt->at(j) >= 0. && j >= 2)
	if(std_vector_LHEparton_pt->at(j) >= 0.) {
		_histo_partons_per_event->Fill(entry);
		if(j >= 2)
			std::cout << "Nell'evento " << entry << " ci sono più di 2 partoni!" << std::endl;
	}
	else {
		if(j < 2)
			std::cout << "Nell'evento " << entry << " ci sono meno di 2 partoni!" << std::endl;
	}
   }
   for(j = 0; j < std_vector_LHElepton_pt->size(); j++) {
	//if(std_vector_LHElepton_pt->at(j) >= 0. && j >= 2)
	if(std_vector_LHElepton_pt->at(j) >= 0.) {
		_histo_leptons_per_event->Fill(entry);
		if(std_vector_LHEneutrino_pt->at(j) >= 0.)
			_histo_leptons_per_event->Fill(entry);
		if(j >= 2)
			std::cout << "Nell'evento " << entry << " ci sono più di 2 leptoni!" << std::endl;
	}
	else {
		if(j < 2)
			std::cout << "Nell'evento " << entry << " ci sono meno di 2 leptoni!" << std::endl;
	}
   }

   //while(std_vector_LHElepton_pt->at(i) > 0 && abs(std_vector_LHElepton_id->at(i)) != 15) {	//seleziono gli eventi senza TAUONI
   while(std_vector_LHElepton_pt->at(i) > 0) {
    	_histo_LHElepton_pt->Fill(std_vector_LHElepton_pt->at(i));
    	_histo_LHElepton_eta->Fill(std_vector_LHElepton_eta->at(i));
    	_histo_LHElepton_phi->Fill(std_vector_LHElepton_phi->at(i));
    	_histo_LHElepton_id->Fill(std_vector_LHElepton_id->at(i));

    	_histo_LHEparton_pt->Fill(std_vector_LHEparton_pt->at(i));
    	_histo_LHEparton_eta->Fill(std_vector_LHEparton_eta->at(i));
    	_histo_LHEparton_phi->Fill(std_vector_LHEparton_phi->at(i));
    	_histo_LHEparton_id->Fill(std_vector_LHEparton_id->at(i));

    	_histo_LHEneutrino_pt->Fill(std_vector_LHEneutrino_pt->at(i));
    	_histo_LHEneutrino_eta->Fill(std_vector_LHEneutrino_eta->at(i));
    	_histo_LHEneutrino_phi->Fill(std_vector_LHEneutrino_phi->at(i));
    	_histo_LHEneutrino_id->Fill(std_vector_LHEneutrino_id->at(i));

      	//std::cout << std_vector_LHElepton_pt->at(i) << std::endl;
	//std::cout << i << std::endl;
    	i++;
  }


  //if(abs(std_vector_LHElepton_id->at(i)) != 15) {	//Seleziono gli eventi senza TAUONI
  if(1) {
	//LHEneutrino_phisum;
	Float_t pt1 = std_vector_LHEneutrino_pt->at(0), pt2 = std_vector_LHEneutrino_pt->at(1);
	Float_t phi1 = std_vector_LHEneutrino_phi->at(0), phi2 = std_vector_LHEneutrino_phi->at(1);
	Float_t ptx = pt1*cos(phi1) + pt2*cos(phi2), pty = pt1*sin(phi1) + pt2*sin(phi2);
	Float_t phi = phi2 - phi1;
	LHEneutrino_ptsum = sqrt(pt1*pt1 + pt2*pt2 + 2*pt1*pt2*cos(phi));
	LHEneutrino_phisum = atan(pty/ptx);
	if(ptx < 0 && pty > 0)
		LHEneutrino_phisum += 4*atan(1);
	if(ptx < 0 && pty < 0)
		LHEneutrino_phisum -= 4*atan(1);
	_histo_LHEneutrino_ptsum->Fill(LHEneutrino_ptsum);
	_histo_LHEneutrino_phisum->Fill(LHEneutrino_phisum);
	_histo_metLHE_pt->Fill(metLHEpt);
    	_histo_metLHE_eta->Fill(metLHEeta);
    	_histo_metLHE_phi->Fill(metLHEphi);

	_histo_jj_deltaeta->Fill(fabs(std_vector_LHEparton_eta->at(1) - std_vector_LHEparton_eta->at(0)));
	//_histo_jj_m->Fill();
   }

   return kTRUE;
}

void mios::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void mios::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   TCanvas* c1 = new TCanvas ("c1", "c1", 1200, 800);
   c1->Divide(2, 2);
   _histo_LHElepton_pt->SetFillColor(kYellow);
   _histo_LHElepton_eta->SetFillColor(kRed);
   _histo_LHElepton_phi->SetFillColor(kBlue);
   _histo_LHElepton_id->SetFillColor(kGreen);
   c1->cd(1);
   _histo_LHElepton_pt->Draw();
   c1->cd(2);
   _histo_LHElepton_eta->Draw();
   c1->cd(3);
   _histo_LHElepton_phi->Draw();
   c1->cd(4);
   _histo_LHElepton_id->Draw();

   TCanvas* c2 = new TCanvas ("c2", "c2", 1200, 800);
   c2->Divide(2, 2);
   _histo_LHEparton_pt->SetFillColor(kYellow);
   _histo_LHEparton_eta->SetFillColor(kRed);
   _histo_LHEparton_phi->SetFillColor(kBlue);
   _histo_LHEparton_id->SetFillColor(kGreen);
   c2->cd(1);
   _histo_LHEparton_pt->Draw();
   c2->cd(2);
   _histo_LHEparton_eta->Draw();
   c2->cd(3);
   _histo_LHEparton_phi->Draw();
   c2->cd(4);
   _histo_LHEparton_id->Draw();

   TCanvas* c3 = new TCanvas ("c3", "c3", 1200, 800);
   c3->Divide(2, 2);
   _histo_LHEneutrino_pt->SetFillColor(kYellow);
   _histo_LHEneutrino_eta->SetFillColor(kRed);
   _histo_LHEneutrino_phi->SetFillColor(kBlue);
   _histo_LHEneutrino_id->SetFillColor(kGreen);
   c3->cd(1);
   _histo_LHEneutrino_pt->Draw();
   c3->cd(2);
   _histo_LHEneutrino_eta->Draw();
   c3->cd(3);
   _histo_LHEneutrino_phi->Draw();
   c3->cd(4);
   _histo_LHEneutrino_id->Draw();

   TCanvas* c4 = new TCanvas ("c4", "c4", 1200, 800);
   c4->Divide(2, 2);
   _histo_metLHE_pt->SetFillColor(kYellow);
   _histo_metLHE_eta->SetFillColor(kRed);
   _histo_metLHE_phi->SetFillColor(kBlue);
   c4->cd(1);
   _histo_metLHE_pt->Draw();
   c4->cd(2);
   _histo_metLHE_eta->Draw();
   c4->cd(3);
   _histo_metLHE_phi->Draw();

   TCanvas* c5 = new TCanvas ("c5", "c5", 1200, 800);
   //c5->Divide(2, 2);
   c5->Divide(2, 1);
   _histo_LHEneutrino_ptsum->SetFillColor(kYellow);
   //_histo_LHE_etasum->SetFillColor(kRed);
   _histo_LHEneutrino_phisum->SetFillColor(kBlue);
   c5->cd(1);
   _histo_LHEneutrino_ptsum->Draw();
   c5->cd(2);
   _histo_LHEneutrino_phisum->Draw();
   //c5->cd(3);
   //_histo_LHEneutrino_etasum->Draw();

   TCanvas* c6 = new TCanvas ("c6", "c6", 1200, 800);
   _histo_jj_deltaeta->SetFillColor(kYellow);
   _histo_jj_deltaeta->Draw();

   TCanvas* c7 = new TCanvas ("c7", "c7", 1200, 800);
   _histo_leptons_per_event->SetFillColor(kYellow);
   _histo_leptons_per_event->Draw();

   TCanvas* c8 = new TCanvas ("c8", "c8", 1200, 800);
   _histo_partons_per_event->SetFillColor(kYellow);
   _histo_partons_per_event->Draw();

   //TF1* fitfunc = new TF1 ("fitfunc","expo + gaus(2)", 0, 3000.);
   //_histo_LHElepton_pt->Fit("fitfunc", "R");
}
