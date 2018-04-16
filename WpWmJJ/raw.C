#define raw_cxx
// The class definition in raw.h has been generated automatically
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
// Root > T->Process("raw.C")
// Root > T->Process("raw.C","some options")
// Root > T->Process("raw.C+")
//

#include "raw.h"
#include <TH2.h>
#include <TStyle.h>

#define ptbins 1000
#define etabins 100
#define phibins 100
#define mbins 1000

void raw::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   _histo_LHElepton_pt = new TH1F ("p_{T,lepton}","p_{T,lepton}",ptbins,0,2000.);
   _histo_LHElepton_eta = new TH1F ("#eta_{lepton}","#eta_{lepton}",etabins,-5,5);
   _histo_LHElepton_phi = new TH1F ("#phi_{lepton}","#phi_{lepton}",phibins,-3.5,3.5);
   _histo_LHElepton_id = new TH1F ("ID_{lepton}","Particle ID",36,18,18);
   _histo_LHEparton_pt = new TH1F ("p_{T,parton}","p_{T,parton}",ptbins,0,2000.);
   _histo_LHEparton_eta = new TH1F ("#eta_{parton}","#eta_{parton}",etabins,-8,8);
   _histo_LHEparton_phi = new TH1F ("#phi_{parton}","#phi_{parton}",phibins,-3.5,3.5);
   _histo_LHEparton_id = new TH1F ("ID_{parton}","Particle ID",36,-18,18);
   _histo_LHEneutrino_pt = new TH1F ("p_{T,neutrino}","p_{T,neutrino}",ptbins,0,2200.);
   _histo_LHEneutrino_eta = new TH1F ("#eta_{neutrino}","#eta_{neutrino}",etabins,-5,5);
   _histo_LHEneutrino_phi = new TH1F ("#phi_{neutrino}","#phi_{neutrino}",phibins,-3.5,3.5);
   _histo_LHEneutrino_id = new TH1F ("ID_{neutrino}","Particle ID",36,-18,18);
   _histo_metLHE_pt = new TH1F ("p_{T,MET}","p_{T,MET}",ptbins,0,2200.);
   _histo_metLHE_eta = new TH1F ("#eta_{MET}","#eta_{MET}",etabins,-5,5);
   _histo_metLHE_phi = new TH1F ("#phi_{MET}","#phi_{MET}",phibins,-3.5,3.5);
   _histo_LHEneutrino_ptsum = new TH1F ("p_{T,sum}","p_{T,sum}",ptbins,0,2200.);
   _histo_LHEneutrino_etasum = new TH1F ("#eta_{sum}","#eta_{sum}",etabins,-5,5);
   _histo_LHEneutrino_phisum = new TH1F ("#phi_{sum}","#phi_{sum}",phibins,-3.5,3.5);
   _histo_jj_deltaeta = new TH1F ("#Delta#eta", "#Delta#eta_{jet-jet}", etabins, 0, +10);
   _histo_jj_m = new TH1F ("M_{jet-jet}", "M_{jet-jet}", mbins, 0, +3500);
   _histo_LHEmlvlv = new TH1F ("M_{l#nul#nu}", "M_{l#nul#nu}", mbins, 0, +1500);
   _histo_leptons_per_event = new TH1F ("l#nu", "Leptoni+neutrini per evento", 100, 0, 10);
   _histo_partons_per_event = new TH1F ("j", "Partoni per evento", 100, 0, 10);
   _histo2_lepton_pt_mlvlv = new TH2F ("p_{T, lepton1} vs M_{l#nul#nu}", "p_{T, lepton1} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 1200.);
   _histo2_met_pt_mlvlv = new TH2F ("p_{T, MET} vs M_{l#nul#nu}", "p_{T, MET} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 1200.);
   _histo2_mlvlv_t_mlvlv = new TH2F ("M^{T}_{l#nul#nu} vs M_{l#nul#nu}", "M^{T}_{l#nul#nu} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 1200.);
   TString option = GetOption();

}

void raw::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t raw::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either raw::GetEntry() or TBranch::GetEntry()
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

   unsigned int counts = 0;
   for(int j = 0; j < std_vector_LHEparton_pt->size(); j++) {
      if(std_vector_LHEparton_pt->at(j) >= 0.)
         counts++;
   }
   _histo_partons_per_event->Fill(counts);

   counts = 0;
   for(int j = 0; j < std_vector_LHElepton_pt->size(); j++) {
      if(std_vector_LHElepton_pt->at(j) >= 0.)
         counts++;
      if(std_vector_LHEneutrino_pt->at(j) >= 0.)
         counts++;
   }
   _histo_leptons_per_event->Fill(counts);

   Float_t lepton_id1 = std_vector_LHElepton_id->at(0), lepton_id2 = std_vector_LHElepton_id->at(1);

   Float_t pt1 = std_vector_LHEneutrino_pt->at(0), pt2 = std_vector_LHEneutrino_pt->at(1);
   Float_t phi1 = std_vector_LHEneutrino_phi->at(0), phi2 = std_vector_LHEneutrino_phi->at(1);
   Float_t eta1 = std_vector_LHEneutrino_eta->at(0), eta2 = std_vector_LHEneutrino_eta->at(1);
   p_neutrino1.SetPtEtaPhiM(pt1, eta1, phi1, 0.);     //Approssimo la massa del neutrino a 0
   p_neutrino2.SetPtEtaPhiM(pt2, eta2, phi2, 0.);     //Approssimo la massa del neutrino a 0

   pt1 = std_vector_LHElepton_pt->at(0), pt2 = std_vector_LHElepton_pt->at(1);
   phi1 = std_vector_LHElepton_phi->at(0), phi2 = std_vector_LHElepton_phi->at(1);
   eta1 = std_vector_LHElepton_eta->at(0), eta2 = std_vector_LHElepton_eta->at(1);
   p_lepton1.SetPtEtaPhiM(pt1, eta1, phi1, 0.);    //Approssimo la massa del leptone a 0
   p_lepton2.SetPtEtaPhiM(pt2, eta2, phi2, 0.);    //Approssimo la massa del leptone a 0
   p_lvlv = p_neutrino1 + p_neutrino2 + p_lepton1 + p_lepton2;
   LHE_mlvlv = p_lvlv.M();

   pt1 = std_vector_LHEparton_pt->at(0), pt2 = std_vector_LHEparton_pt->at(1);
   phi1 = std_vector_LHEparton_phi->at(0), phi2 = std_vector_LHEparton_phi->at(1);
   eta1 = std_vector_LHEparton_eta->at(0), eta2 = std_vector_LHEparton_eta->at(1);
   p_parton1.SetPtEtaPhiM(pt1, eta1, phi1, 0.);    //Approssimo la massa del partone a 0
   p_parton2.SetPtEtaPhiM(pt2, eta2, phi2, 0.);    //Approssimo la massa del partone a 0
   p_jj = p_parton1 + p_parton2;
   LHE_mjj = p_jj.M();

   p_met.SetPtEtaPhiM(metLHEpt, metLHEeta, metLHEphi, 0.);
   p_lvlv_t.SetPtEtaPhiM(p_lvlv.Pt(), 0., p_lvlv.Phi(), p_lvlv.M());
   LHE_mlvlv_t = p_lvlv_t.M();

   int i = 0;
   //if(pt1 > 30. && fabs(eta1) < 4.7 && pt2 > 30. && fabs(eta2) < 4.7 && abs(lepton_id1) != 15 && abs(lepton_id2) != 15 && LHE_mlvlv > 130.) {   //seleziono gli eventi senza TAUONI
      while(i < 2) {    //ciclo sulle coppie di particelle: partoni, leptoni, neutrini
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

   _histo_jj_deltaeta->Fill(fabs(eta2 - eta1)); //Riempio istogramma deltaeta jet-jet
   _histo_jj_m->Fill(LHE_mjj);                  //Riempio istogramma massa invariante jet-jet

   _histo2_lepton_pt_mlvlv->Fill(LHE_mlvlv, p_lepton1.Pt());   //Riempio istogrammi 2-D
   _histo2_met_pt_mlvlv->Fill(LHE_mlvlv, p_met.Pt());
   _histo2_mlvlv_t_mlvlv->Fill(LHE_mlvlv, LHE_mlvlv_t);

   _histo_LHEneutrino_ptsum->Fill((p_neutrino1 + p_neutrino2).Pt());
   _histo_LHEneutrino_phisum->Fill((p_neutrino1 + p_neutrino2).Phi());
   _histo_LHEneutrino_etasum->Fill((p_neutrino1 + p_neutrino2).PseudoRapidity());
   _histo_LHEmlvlv->Fill(LHE_mlvlv);
   _histo_metLHE_pt->Fill(metLHEpt);
   _histo_metLHE_eta->Fill(metLHEeta);
   _histo_metLHE_phi->Fill(metLHEphi);

   //}

   return kTRUE;
}

void raw::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void raw::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   gStyle->SetOptFit(1111);

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
   //c1->Print("Raw/leptons.png");

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
   //c2->Print("Raw/partons.png");

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
   //c3->Print("Raw/neutrinos.png");

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
   //c4->Print("Raw/MET.png");

   TCanvas* c5 = new TCanvas ("c5", "c5", 1200, 800);
   c5->Divide(2, 2);
   _histo_LHEneutrino_ptsum->SetFillColor(kYellow);
   _histo_LHEneutrino_etasum->SetFillColor(kRed);
   _histo_LHEneutrino_phisum->SetFillColor(kBlue);
   c5->cd(1);
   _histo_LHEneutrino_ptsum->Draw();
   c5->cd(2);
   _histo_LHEneutrino_etasum->Draw();
   c5->cd(3);
   _histo_LHEneutrino_phisum->Draw();
   //c5->Print("Raw/neutrinos_sum.png");

   TCanvas* c6 = new TCanvas ("c6", "c6", 1200, 800);
   _histo_jj_deltaeta->SetFillColor(kYellow);
   _histo_jj_deltaeta->Draw();
   //c6->Print("Raw/delta_eta_jj.png");

   TCanvas* c7 = new TCanvas ("c7", "c7", 1200, 800);
   _histo_leptons_per_event->SetFillColor(kYellow);
   _histo_leptons_per_event->Draw();
   //c7->Print("Raw/leptons_number.png");

   TCanvas* c8 = new TCanvas ("c8", "c8", 1200, 800);
   _histo_partons_per_event->SetFillColor(kYellow);
   _histo_partons_per_event->Draw();
   //c8->Print("Raw/partons_number.png");

   TCanvas* c9 = new TCanvas ("c9", "c9", 1200, 800);
   _histo_jj_m->SetFillColor(kYellow);
   _histo_jj_m->Draw();
   //c9->Print("Raw/mass_jj.png");

   TCanvas* c10 = new TCanvas ("c10", "c10", 1200, 800);
   _histo_LHEmlvlv->SetFillColor(kYellow);
   _histo_LHEmlvlv->Draw();
   //c10->Print("Raw/mass_lvlv.png");
   //TF1* fitfunc = new TF1 ("fitfunc","gaus", 124.995, 125.005);       //Fit della risonanza dell'Higgs
   //fitfunc->SetParameter(1, 125.0);
   //fitfunc->SetParameter(2, 0.008);
   //_histo_LHEmlvlv->Fit("fitfunc", "R");

   TCanvas* c11 = new TCanvas ("c11", "c11", 1200, 800);
   _histo2_lepton_pt_mlvlv->Draw("COLZ");
   //c11->Print("Raw/pt_lepton1_vs_mlvlv.png");

   TCanvas* c12 = new TCanvas ("c12", "c12", 1200, 800);
   _histo2_met_pt_mlvlv->Draw("COLZ");
   //c12->Print("Raw/met_pt_vs_mlvlv.png");

   TCanvas* c13 = new TCanvas ("c13", "c13", 1200, 800);
   _histo2_mlvlv_t_mlvlv->Draw("COLZ");
   //c13->Print("Raw/mlvlv_t_vs_mlvlv.png");

}
