#define Analyze_cxx
#include "Analyze.h"
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

   TH1* chi2Hist = new TH1D("chi2","Histogram of Chi2",100,0,2.5);
   chi2Hist->GetXaxis()->SetTitle("chi2");
   chi2Hist->GetYaxis()->SetTitle("number of events");

   TH1* ebeamHist = new TH1D("ebeam", "Histogram of ebeam", 100, 149, 151);
   ebeamHist->GetXaxis()->SetTitle("ebeam");
   ebeamHist->GetYaxis()->SetTicks("number of events");

   TCanvas* c1 = new TCanvas("c1","c1");

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      chi2Hist->Fill(chi2);
      ebeamHist->Fill(ebeam);
   }

   c1->Divide(2);
   c1->cd(1);
   chi2Hist->Draw("e");
   chi2Hist->Fit("gaus");
   c1->cd(2);
   ebeamHist->Draw("e");
   ebeamHist->Fit("gaus");
}
