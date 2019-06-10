#define Analyze_cxx
#include "Analyze.h"
#include "TMath.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyze::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyze.C
//      root> Analyze t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // SETUP
   TH1* ptHist = new TH1D("pt","Histogram of pt",100,0,30);
   ptHist->GetXaxis()->SetTitle("pt (GeV)");
   ptHist->GetYaxis()->SetTitle("number of events");

   TH1* thetaHist = new TH1D("theta", "Histogram of theta", 100, 0, 0.2);
   thetaHist->GetXaxis()->SetTitle("theta (rad)");
   thetaHist->GetYaxis()->SetTitle("number of events");

   TCanvas* c1 = new TCanvas("c1","c1");
   c1->Divide(2);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      // LOOP
      Double_t pt = TMath::Sqrt(px*px + py*py);
      ptHist->Fill(pt);

      Double_t theta = TMath::ATan2(pt, pz);
      thetaHist->Fill(theta);
   }

   //WRAP-UP
   c1->cd(1);
   ptHist->Draw("e");

   c1->cd(2);
   thetaHist->Draw("e");
}
