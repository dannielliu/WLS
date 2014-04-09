//
//***************************************************************
//*DISCLAIMER							*
//*								*
//*				Created Jul.15, 2006		*
//***************************************************************
//
//path : epam/include/EpamPrimaryGeneratorAction.hh
//

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#ifndef EpamPrimaryGeneratorAction_H
#define EpamPrimaryGeneratorAction_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "Randomize.hh"

#include <vector>

#include "EpamDefs.hh"
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4ParticleGun;

class G4GeneralParticleSource;
class G4GeneralParticleSourceMessenger;
class G4Event;

class EpamDetectorConstruction;
class EpamRunAction;
class EpamEventAction;

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EpamPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  EpamPrimaryGeneratorAction( EpamDetectorConstruction*,
                              EpamEventAction* );
  ~EpamPrimaryGeneratorAction();

public:
  void GeneratePrimaries( G4Event* anEvent);
	
private:
  G4GeneralParticleSource* generalParticleSource;
  G4GeneralParticleSourceMessenger* generalParticleSourceMessenger;

  //  G4GeneralParticleSource* particleGun;

  EpamDetectorConstruction*	detector;
  EpamRunAction* runaction;
  EpamEventAction* eventaction;

  G4int shootMode;
  G4int selectMode;
  G4double energyLowerBound;
  G4double energyUpperBound;

public:
};

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#endif

