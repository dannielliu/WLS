//
//***************************************************************
//*DISCLAIMER							*
//*								*
//*				Created Jul.22, 2006		*
//***************************************************************
//
//path: epam/include/SteppingAction.hh

//
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#ifndef EpamSteppingAction_H
#define EpamSteppingAction_H 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "Randomize.hh"

#include "EpamRunAction.hh"
class G4OpBoundaryProcess;
class G4StepPoint;
class G4Track;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class EpamEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class EpamSteppingAction : public G4UserSteppingAction
{
public:
  EpamSteppingAction( EpamDetectorConstruction* , EpamEventAction* );
  ~EpamSteppingAction();
	  
  void UserSteppingAction(const G4Step*);
  
  //public:
  //fiberPhotonNumber[32];
private:
  
  // Artificially kill the photon after it has bounced more than this number
    G4int bounceLimit;
    // number of photons that reach the end
    G4int counterEnd;
    // number of photons that didn't make it to the end
    G4int counterMid;
    // total number of bounces that a photon been through
    G4int counterBounce;
    // number of bounces that a photon been through within the fibre
    G4int counterWLSBounce;
    // number of bounces that a photon been through from Cladding 1 to 2
    G4int counterClad1Bounce;
    // number of bounces that a photon been through from Cladding 2 to World
    G4int counterClad2Bounce;

    // The starting position of the photon
    G4double initZ;
    // initial gamma of the photon
    G4double initGamma;
    // initial theta of the photon
    G4double initTheta;

    G4OpBoundaryProcess* opProcess;

    // maximum number of save states
    static G4int maxRndmSave;
 
    EpamDetectorConstruction* detector;

  //WLSSteppingActionMessenger* steppingMessenger;

    inline void ResetCounters()
    { 
      counterBounce = counterWLSBounce =
      counterClad1Bounce = counterClad2Bounce = 0;
      initGamma = initTheta = -1;
    }

  void UpdateHistogramSuccess(G4StepPoint*, G4Track*);
    void UpdateHistogramReflect(G4StepPoint*, G4Track*);
    void UpdateHistogramEscape(G4StepPoint*, G4Track*);
    void UpdateHistogramAbsorb(G4StepPoint*, G4Track*);

    // save the random status into a sub-directory
    // Pre: subDir must be empty or ended with "/"
    inline void saveRandomStatus(G4String subDir);

  //
  //
  //EpamDetectorConstruction* detector;
  EpamEventAction* eventaction;
  EpamEventKeyInformation stepInfo;
  
  EpamEventSecondaryParticleNumberInformation secondaryParticleNumberInfo;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

