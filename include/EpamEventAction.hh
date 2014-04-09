//***************************************************************
//*DISCLAIMER							*
//*								*
//*					Created Jul.19, 2006	*
//***************************************************************
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef EpamEventAction_H
#define EpamEventAction_H 1

#include "G4UserEventAction.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "EpamRunAction.hh"
//#include "EpamIdentifier.hh"

#include <vector>
#include <sys/time.h>
#include <unistd.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
                              
class EpamDetectorConstruction;
class EpamRunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EpamEventAction : public G4UserEventAction
{
public:
  EpamEventAction( EpamRunAction* run );
  virtual ~EpamEventAction();

public:
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
  void updateEventInfo( EpamEventKeyInformation* info );
  void updateEventParticleInfo( EpamEventKeyInformation* info );
  void updateEventSecondaryParticleNumberInfo( EpamEventSecondaryParticleNumberInformation* info);
  
private:
  EpamDetectorConstruction*	detector;
  EpamRunAction* runaction;
  //EpamIdentifier identifier;

  //G4String drawFlag;

  struct timeval startTime;
  struct timeval endTime;
  struct timezone tz;

  G4int verboselevel;
  G4int printModulo;
  
  G4int mppcCollID;
  
  G4String drawFlag;
  
  G4bool forcedrawphotons;
  G4bool forcenophotons;
  
public:
  EpamDetectorConstruction* getDetector()
  {
    return detector;
  }

  EpamRunAction* getRunaction()
  {
    return runaction;
  }
  
  G4int GetEventNo();
  void SetEventVerbose(G4int);
  
  void SetDrawFlag(G4String val)  { drawFlag = val; };
  void SetPrintModulo(G4int val)  { printModulo = val; };
  
  void SetForceDrawPhotons(G4bool b){forcedrawphotons=b;}
  void SetForceDrawNoPhotons(G4bool b){forcenophotons=b;}
  
  G4double x_position;
  G4double y_position;
  G4double z_position;
private:
  CLHEP::HepRandomEngine*		engine;
};
#endif
