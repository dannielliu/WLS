Int_t file(){
  TH1D *h1 = new TH1D("h1","h1",100,0,17);
  TH1D *h2 = new TH1D("h2","h2",100,0,17);
  Double_t a[32]={0};
  ifstream inData("file.dat");
  for(Int_t i=0; !inData.eof(); ++i){
    for(Int_t j=0; j!=32; ++j){
      inData>>a[j];
    }
    h1->Fill(center(&a[0],16));
    h2->Fill(center(&a[16],16));
  }
  TCanvas *c1 = new TCanvas("c1","c1",0,0,600,400);
  c1->Divide(2,1);
  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h2->Draw();
}
Double_t center(Double_t *par, Int_t n){
  Double_t weight=0;
  Double_t sum =0;
  for(Int_t i=0; i!=n; ++i){
    weight = weight + (i+1)*par[i];
    sum = sum+par[i];
  }
  if(sum!=0)
    return weight/sum;
}
