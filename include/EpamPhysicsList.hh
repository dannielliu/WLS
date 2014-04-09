//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
// HEADER
// 
// Last Revised: Mar 14, 2007
// 
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#ifndef EpamPhysicsList_H 
#define EpamPhysicsList_H 1

#include "G4VUserPhysicsList.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

class G4ParticleDefinition;
class EpamDetectorConstruction;

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

class EpamPhysicsList : public G4VUserPhysicsList
{
public:
  EpamPhysicsList( EpamDetectorConstruction* det );
  ~EpamPhysicsList();

protected:                    // Construction of particles and processes
  void ConstructParticle();
  void ConstructProcess();

 //these methods Construct particles
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructMesons();
  void ConstructBaryons();
  void ConstructIons();
  void ConstructShortLiveds();

//these methods Construct physics processes and register them  
  //void AddTransportation();
  void ConstructEM();
  void ConstructOp();
  //void ConstructHad();
  void ConstructGeneral();
  
  void SetCuts();

private:
  G4int VerboseLevel;
  G4int OpVerbLevel;

private:                        //
  EpamDetectorConstruction*	detector;

public:
  void ConstructAllParticles(); // Construct all Ions
  void ShowParticleTable();
	 
};

#endif
