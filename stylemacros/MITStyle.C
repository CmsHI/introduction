TCanvas* MakeCanvas(const char* name, const char *title)
{
  // Start with a canvas
  TCanvas *canvas = new TCanvas(name,title);
  // General overall stuff
  canvas->SetFillColor      (0);
  canvas->SetBorderMode     (0);
  canvas->SetBorderSize     (10);
  // Set margins to reasonable defaults
  canvas->SetLeftMargin     (0.20);
  canvas->SetRightMargin    (0.06);
  canvas->SetTopMargin      (0.08);
  canvas->SetBottomMargin   (0.15);
  // Setup a frame which makes sense
  canvas->SetFrameFillStyle (0);
  canvas->SetFrameLineStyle (0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderSize(10);
  canvas->SetFrameFillStyle (0);
  canvas->SetFrameLineStyle (0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderSize(10);

  return canvas;
}

void InitSubPad(TPad* pad, int i)
{
  //printf("Pad: %p, index: %d\n",pad,i);

  pad->cd(i);
  TPad *tmpPad = (TPad *) pad->GetPad(i);
  tmpPad->SetLeftMargin  (0.20);
  tmpPad->SetTopMargin   (0.06);
  tmpPad->SetRightMargin (0.08);
  tmpPad->SetBottomMargin(0.15);
  return;
}

void InitHist(TH1        *hist,
	      const char *xtit,
	      const char *ytit  = "Number of Entries",
	      EColor      color = kBlack)
{
  hist->SetXTitle(xtit);
  hist->SetYTitle(ytit);
  hist->SetLineColor(color);
  hist->SetTitleSize  (0.06,"X");
  hist->SetTitleSize  (0.06,"Y");
  hist->SetTitleSize  (0.06,"Z");
  hist->SetTitleOffset(3.800,"Y");
  hist->SetTitleOffset(3.800,"X");
  hist->SetTitleOffset(3.800,"Z");
  hist->SetLabelOffset(0.008,"Y");
  hist->SetLabelSize  (0.050,"Y");
  hist->SetLabelFont  (42   ,"Y");
  hist->SetMarkerStyle(20);
  hist->SetMarkerColor(color);
  hist->SetMarkerSize (0.6);
  // Strangely enough this cannot be set anywhere else??
  hist->GetYaxis()->SetTitleFont(42);
  hist->SetTitle("");
  return;
}

void fixedFontHist1D(TH1D * h, Float_t xoffset=0.9, Float_t yoffset=2.3)
{
  h->SetLabelFont(43,"X");
  h->SetLabelFont(43,"Y");
  //h->SetLabelOffset(0.01);
  h->SetLabelSize(16);
  h->SetTitleFont(43);
  h->SetTitleSize(20);
  h->SetLabelSize(15,"Y");
  h->SetTitleFont(43,"Y");
  h->SetTitleSize(17,"Y");
  h->SetTitleOffset(xoffset,"X");
  h->SetTitleOffset(yoffset,"Y");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
}

void fixedFontHist(TH2D * h, Float_t xoffset=0.9, Float_t yoffset=2.3)
{
  h->SetLabelFont(43,"X");
  h->SetLabelFont(43,"Y");
  //h->SetLabelOffset(0.01);
  h->SetLabelSize(16);
  h->SetTitleFont(43);
  h->SetTitleSize(20);
  h->SetLabelSize(15,"Y");
  h->SetTitleFont(43,"Y");
  h->SetTitleSize(17,"Y");
  h->SetTitleOffset(xoffset,"X");
  h->SetTitleOffset(yoffset,"Y");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
}

void SetStyle() {

  TH1::SetDefaultSumw2();
  gROOT->SetStyle("Plain");

  TStyle *MITStyle = new TStyle("MIT-Style","The Perfect Style for Plots ;-)");
  gStyle = MITStyle;

  gStyle->SetTitleSize(0.08,"t");//  gStyle->SetTitleX(0.8);
  gStyle->SetTitleW(0.3);
  gStyle->SetFrameFillColor(2);
  gStyle->SetFrameLineColor(2);

  // Canvas

  MITStyle->SetCanvasColor     (0);
  MITStyle->SetCanvasBorderSize(10);
  MITStyle->SetCanvasBorderMode(0);

  MITStyle->SetCanvasDefH      (500);
  MITStyle->SetCanvasDefW      (550);
  //  MITStyle->SetCanvasDefX      (100);
  //  MITStyle->SetCanvasDefY      (100);

  // Pads

  MITStyle->SetPadColor       (0);
  //  MITStyle->SetPadBorderSize  (10);
  MITStyle->SetPadBorderMode  (0);
  MITStyle->SetPadBottomMargin(0.18);
  MITStyle->SetPadTopMargin   (0.06);
  MITStyle->SetPadLeftMargin  (0.22);
  MITStyle->SetPadRightMargin (0.06);
  MITStyle->SetPadGridX       (0);
  MITStyle->SetPadGridY       (0);
  MITStyle->SetPadTickX       (1);
  MITStyle->SetPadTickY       (1);

  // Frames

  MITStyle->SetFrameFillStyle ( 0);
  MITStyle->SetFrameFillColor ( 0);
  MITStyle->SetFrameLineColor ( 1);
  MITStyle->SetFrameLineStyle ( 0);
  MITStyle->SetFrameLineWidth ( 1);
  //  MITStyle->SetFrameBorderSize(10);
  MITStyle->SetFrameBorderMode( 0);

  // Histograms

  MITStyle->SetHistLineColor(1);
  MITStyle->SetHistLineStyle(0);
  MITStyle->SetHistLineWidth(3);
  MITStyle->SetNdivisions(505,"X");
  MITStyle->SetNdivisions(505,"Y");
  MITStyle->SetNdivisions(505,"Z");

  // Functions

  MITStyle->SetFuncColor(1);
  MITStyle->SetFuncStyle(0);
  MITStyle->SetFuncWidth(2);

  // Various

  MITStyle->SetMarkerStyle(20);
  MITStyle->SetMarkerColor(kBlack);
  MITStyle->SetMarkerSize (1.2);

//  MITStyle->SetTitleSize  (0.1,"t");

  MITStyle->SetTitleSize  (0.070,"X");
  MITStyle->SetTitleOffset(1.0,"X");
  MITStyle->SetTitleFont  (42,"X");
  MITStyle->SetLabelOffset(0.005,"X");
  MITStyle->SetLabelSize  (0.070,"X");
  MITStyle->SetLabelFont  (42   ,"X");

  MITStyle->SetTitleSize  (0.070,"Y");
  MITStyle->SetTitleOffset(1.0,"Y");
  MITStyle->SetTitleFont  (42,"Y");
  MITStyle->SetLabelOffset(0.005,"Y");
  MITStyle->SetLabelSize  (0.070,"Y");
  MITStyle->SetLabelFont  (42   ,"Y");

  MITStyle->SetTitleSize  (0.06,"Z");
  MITStyle->SetTitleOffset(1.640,"Z");
  MITStyle->SetTitleFont  (42,"Z");
  MITStyle->SetLabelOffset(0.005,"Z");
  MITStyle->SetLabelSize  (0.070,"Z");
  MITStyle->SetLabelFont  (42   ,"Z");

  MITStyle->SetStripDecimals(kFALSE);
  MITStyle->SetTitleBorderSize(0);
  MITStyle->SetTitleFillColor(0);
  //  MITStyle->SetTitleAlign(6);

  MITStyle->SetTextSize   (20);
  MITStyle->SetTextFont   (43);

  MITStyle->SetStatFont   (42);
  MITStyle->SetOptStat    (0);

  MITStyle->SetLegendBorderSize(0);
  MITStyle->SetEndErrorSize(0);
  MITStyle->SetErrorX(0);

  MITStyle->SetPalette    (1,0);
}

void MITStyle() {
  SetStyle();
}
