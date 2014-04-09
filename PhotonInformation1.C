Int_t PhotonInformation1()
{
  Double_t a[9]={0};
  Double_t upFiber[16]={0};
  Double_t downFiber[16]={0};
  Double_t fiberID[16]={0};
  for(Int_t i=0;i!=16;i++)
  {
    fiberID[i] = i+1;
  }

  TH1D *h1 = new TH1D("h1","h1",20,-2,18);
  TH2D *h2 = new TH2D("h2","h2",20,-2,18,100,0,1600);
  TProfile * p1 = new TProfile("p1","p1",20,-2,18);
  ifstream inData;
  inData.open("PhotonInformation.txt");
  if (!inData.good())
    {
      cout<<"Open file failed"<<endl;
      exit();
    }
  for(Int_t i_event=0; !inData.eof(); ++i_event){
    for(Int_t i=0; i<32; i++){
      for(Int_t j=0; j<9; j++){
	inData>>a[j];
	if(i<16)
	  upFiber[i] += a[j];
	else
	  downFiber[i-16] += a[j];
      }
    }
  
    //inData.close();

    for(Int_t i=0; i<16; i++){
      h1->SetBinContent(i+1, upFiber[i]);
      h1->SetBinError(i+1, sqrt(upFiber[i]));
      h2->Fill(fiberID[i], upFiber[i]);
      p1->Fill(fiberID[i], upFiber[i]);
    }
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",0,0,600,400);
  c1->Divide(2,1);
  c1->cd(1);
  h2->GetXaxis()->SetTitle("fiberID");
  h2->GetYaxis()->SetTitle("Photon Number");
  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->CenterTitle();
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(kRed);
  h2->Draw();
  h2->Fit("gaus");
  c1->cd(2);
  p1->Draw();
  return 0;
}
