#ifndef EpamStackingAction_H
#define EpamStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "EpamEventAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class EpamEventAction;

class EpamStackingAction : public G4UserStackingAction
{
  public:
    EpamStackingAction(EpamEventAction*);
   ~EpamStackingAction();
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

  private:
    G4int TotalPhotonCounter;
    EpamEventAction* eventaction;
};


#endif




