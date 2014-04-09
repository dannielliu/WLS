#include "EpamStackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"



EpamStackingAction::EpamStackingAction(EpamEventAction* evtact)
: TotalPhotonCounter(0),eventaction(evtact)
{;}


EpamStackingAction::~EpamStackingAction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
EpamStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      TotalPhotonCounter++;
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamStackingAction::NewStage()
{
  G4cout << "Number of optical photons produces in this event : "
         << TotalPhotonCounter << G4endl;
  //eventaction->SetTotalPhotonCount( TotalPhotonCounter );
  G4cout << "hi"<< G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EpamStackingAction::PrepareNewEvent()
{ 
  TotalPhotonCounter = 0; 
}



