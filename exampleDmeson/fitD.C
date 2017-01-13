#include "uti.h"

void fitD(TString inputhist)
{
  gStyle->SetTextSize(0.042);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  // Read the histogram
  TFile* inf = new TFile(inputhist.Data());
  TH1D* h = (TH1D*)inf->Get("h");

  // Fit
  TF1* f = new TF1("f","[0]*([7]*exp(-0.5*((x-[1])/[2])**2)/(sqrt(2*3.14159)*[2])+(1-[7])*exp(-0.5*((x-[1])/[8])**2)/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x",1.7,2.0);

  f->SetParLimits(2,0.005,0.05);
  f->SetParLimits(8,0.001,0.05);
  f->SetParLimits(7,0,1);
  f->SetParLimits(4,-1000,1000);

  f->SetParameter(0,100);
  f->SetParameter(1,1.865);
  f->SetParameter(2,0.03);
  f->SetParameter(7,0.1);
  f->SetParameter(8,0.05);

  h->Fit("f","L","",1.7,2.0);

  // Create functions for signal and background respectively
  TF1* background = new TF1("background","[0]+[1]*x+[2]*x*x+[3]*x*x*x",1.7,2.0);
  background->SetParameters(f->GetParameter(3),f->GetParameter(4),f->GetParameter(5),f->GetParameter(6));
  background->SetLineColor(4);
  background->SetLineStyle(2);

  TF1* mass = new TF1("mass","[0]*([3]*exp(-0.5*((x-[1])/[2])**2)/(sqrt(2*3.14159)*[2])+(1-[3])*exp(-0.5*((x-[1])/[2])**2)/(sqrt(2*3.14159)*[4]))",1.7,2.0);
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);

  // Plot
  TCanvas* c = new TCanvas("c","",600,600);
  h->Draw("e");
  background->Draw("same");
  mass->Draw("same");
  f->Draw("same");

  // Create and plot legends
  TLegend* leg = new TLegend(0.65,0.64,0.82,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","pp"));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  TLatex* tex;
  tex = new TLatex(0.22,0.78,"p_{T} > 20 GeV/c");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.22,0.83,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  // Save the plot
  c->SaveAs("plots/fitD.pdf");
}

