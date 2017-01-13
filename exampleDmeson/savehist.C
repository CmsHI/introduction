#include "uti.h"

Double_t BIN_MIN = 1.7;
Double_t BIN_MAX = 2.0;
Double_t BIN_NUM = 60;

void savehist(TString inputdata, TString cuttrigger, TString cut, TString outputfile)
{
  gStyle->SetTextSize(0.045);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  // Open the input data file
  TFile* inf = new TFile(inputdata.Data());
  TTree* nt = (TTree*)inf->Get("ntDkpi");
  nt->AddFriend("ntHlt");

  // Create a histogram and fill it with 'Dmass'
  TH1D* h = new TH1D("h",";m_{#piK} (GeV/c^{2});Entries / (5 MeV/c^{2})",BIN_NUM,BIN_MIN,BIN_MAX);
  nt->Project("h","Dmass",Form("%s&&%s",cuttrigger.Data(),cut.Data()));  

  // Plot the mass spectrum
  TCanvas* c = new TCanvas("c","",600,600);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetAxisRange(0,h->GetMaximum()*1.5,"Y");
  h->GetXaxis()->SetTitleOffset(1.0);
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);

  h->Draw("e");
  c->SaveAs("plots/massSpectra.pdf");

  // Save the histogram in a root file
  TFile* outf = new TFile(outputfile.Data(),"recreate");
  outf->cd();
  h->Write();
  outf->Close();
}

