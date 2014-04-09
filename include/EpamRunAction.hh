//
//***************************************************************
//*DISCLAIMER                                                   *
//*                                                             *
//*                                     Created Jul.23, 2006    *
//***************************************************************
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef EpamRunAction_H
#define EpamRunAction_H 1


#include "G4UserRunAction.hh"
#include "G4UnitsTable.hh"

#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TStorage.h"

#include <fstream>
#include <vector>
#include <sys/time.h>
#include <unistd.h>

#include "EpamDefs.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EpamDetectorConstruction;
class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EpamEventKeyInformation
{
public:
  G4double visibleLightShieldEnergyDeposit[2]; // 0:Front; 1:Rear
  G4double siliconLayersEnergyDeposit[3]; // 0:FirstFront; 1:SencondFront; 2:SencondRear; 3:FirstRear
  G4double calorimeterEnergyDeposit;

  G4double siliconLayersEnergyDepositWithError[3];
  G4double calorimeterEnergyDepositWithError;

  G4double totalEnergy;
  
  G4int ifPrimaryReachVisibleLightShield[2];
  G4int ifPrimaryReachSiliconLayer[3];
  G4int ifPrimaryReachCalorimeter;
  
  G4int particleZ;
  G4int particleA;
  G4double particleMass;
  G4double particleEnergy;
  G4double particlePosition[3];
  G4double particleDirection[3];

  G4int secondaryParticleNumber;
  G4int highEnergySecondaryParticleNumber; // Please refer to HIGH_ENERGY_SECONDARY_CONDITION

  void reset()
  {
    visibleLightShieldEnergyDeposit[0] = 0;
    visibleLightShieldEnergyDeposit[1] = 0;
    siliconLayersEnergyDeposit[0] = 0;
    siliconLayersEnergyDeposit[1] = 0;
    siliconLayersEnergyDeposit[2] = 0;
    //siliconLayersEnergyDeposit[3] = 0;
    calorimeterEnergyDeposit = 0;

    siliconLayersEnergyDepositWithError[0] = 0;
    siliconLayersEnergyDepositWithError[1] = 0;
    siliconLayersEnergyDepositWithError[2] = 0;
    //siliconLayersEnergyDepositWithError[3] = 0;
    calorimeterEnergyDepositWithError = 0;
        
    totalEnergy = 0;

    ifPrimaryReachVisibleLightShield[0] = false;
    ifPrimaryReachVisibleLightShield[1] = false;
    ifPrimaryReachSiliconLayer[0] = false;
    ifPrimaryReachSiliconLayer[1] = false;
    ifPrimaryReachSiliconLayer[2] = false;
    //ifPrimaryReachSiliconLayer[3] = false;
    ifPrimaryReachCalorimeter = 0;
    
    particleZ = 0;
    particleA = 0;
    particleMass = 0;
    particlePosition[0] = 0;
    particlePosition[1] = 0;
    particlePosition[2] = 0;
    particleDirection[0] = 0;
    particleDirection[1] = 0;
    particleDirection[2] = 0;
    secondaryParticleNumber = 0;
    highEnergySecondaryParticleNumber = 0;
  };
  
  EpamEventKeyInformation():
    calorimeterEnergyDeposit( 0 ),
    calorimeterEnergyDepositWithError( 0 ),
    totalEnergy( 0 ),
    ifPrimaryReachCalorimeter( 0 ),
    particleZ( 0 ),
    particleA( 0 ),
    particleMass( 0 ),
    secondaryParticleNumber( 0 ),
    highEnergySecondaryParticleNumber( 0 )
  {
    for( G4int ptr = 0; ptr < 3; ptr++ ){
      siliconLayersEnergyDeposit[ptr] = 0;
      siliconLayersEnergyDepositWithError[ptr] = 0;
      ifPrimaryReachSiliconLayer[ptr] = 0;
    }
    for( G4int ptr = 0; ptr < 3; ptr++ ){
      particlePosition[ptr] = 0;
      particleDirection[ptr] = 0;
    }
    for( G4int ptr = 0; ptr < 2; ptr++ ){
      visibleLightShieldEnergyDeposit[ptr] = 0;
      ifPrimaryReachVisibleLightShield[ptr] = false;
    }
  }
};

class EpamEventSecondaryParticleNumberInformation
{
public :
  G4double fiberPhotonNumber[320];
  //G4double gammaNumber[12];
  
  void reset()
  {
    for (G4int ptr=0; ptr<320; ptr++)
      {
	fiberPhotonNumber[ptr]=0;
      }
  }
  
  EpamEventSecondaryParticleNumberInformation()
  {
    for (G4int ptr=0; ptr<320; ptr++)
      {
	fiberPhotonNumber[ptr]=0;
      }
  }
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EpamRunAction : public G4UserRunAction
{
public:
  EpamRunAction( EpamDetectorConstruction* myDet );
  ~EpamRunAction();

public:
  void BeginOfRunAction( const G4Run* );
  void EndOfRunAction( const G4Run* );

private:
  EpamDetectorConstruction*	detector;
  G4int runID;

  //  struct timeval startTime;
  //struct timeval endTime;
  //struct timzone tz;

public:
  EpamEventKeyInformation eventInfo;
  EpamEventSecondaryParticleNumberInformation eventSecondaryParticleNumberInfo;

  TFile* epamDataFile;
  TTree* epamDataTree;
  TTree* epamGoodDataTree;
  
  std::ofstream* epamDataMatematicaEnergies;
  std::ofstream* epamDataMatematicaEnergiesFiltered;
  std::ofstream* epamDataMatematicaParticleInformation;

public:
  G4int GetRunID(){
    return runID;
  }

  EpamDetectorConstruction* getDetector()
  {
    return detector;
  }
 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
