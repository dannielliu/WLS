//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
// HEADER
// 
// Last Revised: Mar. 12, 2007
// 
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#ifndef EpamDetectorConstruction_H
#define EpamDetectorConstruction_H 1

#include <vector>		// Cpp Include

#include "globals.hh"		// General


#include "G4RotationMatrix.hh"

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

class G4LogicalVolume;
class G4VPhysicalVolume;

class G4Box;
class G4Tubs;
class G4Cons;
class G4Orb;
class G4Polycone;
class G4Polyhedra;

class G4Material;

class G4VTouchable;

class G4Region;

class G4NistManager;

class WLSMaterials;
class WLSPhotonDetSD;

#include "G4VUserDetectorConstruction.hh" //
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class EpamDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  EpamDetectorConstruction();
  ~EpamDetectorConstruction();
  G4VPhysicalVolume* ConstructVolume();
  //public:                         // Mandatory Function Construct()
  G4VPhysicalVolume* Construct();
  void UpdateGeometry();
  G4Material* FindMaterial(G4String);
private:
  void ConstructFiber();
  //const G4VPhysicalVolume* GetBottom() {return physiCalorimeter;}
  //const G4VPhysicalVolume* GetPMT() {return physiBottomSurface;}
  
    //G4VPhysicalVolume* ConstructDetector();
private:                        // Geometry Parametors
  // The World
  G4double worldDiam;
  WLSMaterials* materials;
  // Visible Light Shield
  G4double visibleLightShieldAlThickness;
  G4double visibleLightShieldMylarThickness;
  G4double visibleLightShieldDiam;
  G4double visibleLightShieldFrontCenterPosition;
  G4double visibleLightShieldRearCenterPosition;
  
  // Layers
  G4double layerFirstThickness;
  G4double layerSecondThickness;
  
  G4double layerFirstDiam;
  G4double layerSecondDiam;
  
  G4double layerFirstFrontCenterPosition;
  //G4double layerFirstRearCenterPosition;
  G4double layerSecondFrontCenterPosition;
  G4double layerSecondRearCenterPosition;
  
  // Dead Areas
  G4double deadAreaThickness;
  
  // Electrode
  G4double electrodeThickness;
  
  // Calorimeter
  G4double calorimeterXY;
  G4double calorimeterZ;
  G4double calorimeterCenterPosition;
  
/*
// Collimator
G4double feCollimatorInnerDiam1;
G4double feCollimatorInnerDiam2;
G4double feCollimatorInnerDiam3;
G4double feCollimatorInnerDiam4;
G4double feCollimatorInnerDiam5;
G4double feCollimatorInnerDiam6;

G4double feCollimatorOutterDiam1;
G4double feCollimatorOutterDiam2;
G4double feCollimatorOutterDiam3;
G4double feCollimatorOutterDiam4;
G4double feCollimatorOutterDiam5;
G4double feCollimatorOutterDiam6;

G4double feCollimatorPlanePosition1;
G4double feCollimatorPlanePosition2;
G4double feCollimatorPlanePosition3;
G4double feCollimatorPlanePosition4;
G4double feCollimatorPlanePosition5;
G4double feCollimatorPlanePosition6;
    
G4double feCollimatorFrontPosition;
*/
  G4double surfaceInnerDiam1;
  G4double surfaceInnerDiam2;
  G4double surfaceOutterDiam1;
  G4double surfaceOutterDiam2;
  G4double surfacePlanePosition1;
  G4double surfacePlanePosition2;
  
  G4double surfaceFrontPosition;
  G4int cladingValue;
  static WLSPhotonDetSD* mppcSD;
private:                        // Materials Parameter
  G4String visibleLightShieldMaterialNameAl;
  G4String visibleLightShieldMaterialNameMylar;
  G4String layersMaterialName;
  G4String calorimeterMaterialName;
  G4String electrodeMaterialName;
  
  G4String opticalSurfaceMaterialName;
  
  /*  
    G4String feCollimatorMaterialName;
    G4String taCollimatorMaterialName;
*/
  
private:                        // The Geometry, LogicalVolumes, and PhysicalVolumes
  // The world
  G4Orb* solidWorld;
  G4LogicalVolume* logicWorld;
  G4VPhysicalVolume* physiWorld;
  
  // Visible Light Shield
  G4Tubs* solidVisibleLightShieldFrontAl;
  G4Tubs* solidVisibleLightShieldFrontMylar;
  G4Tubs* solidVisibleLightShieldRearAl;
  G4Tubs* solidVisibleLightShieldRearMylar;
  G4LogicalVolume* logicVisibleLightShieldFrontAl;
  G4LogicalVolume* logicVisibleLightShieldFrontMylar;
  G4LogicalVolume* logicVisibleLightShieldRearAl;
  G4LogicalVolume* logicVisibleLightShieldRearMylar;
  G4VPhysicalVolume* physiVisibleLightShieldFrontAl;
  G4VPhysicalVolume* physiVisibleLightShieldFrontMylar;
  G4VPhysicalVolume* physiVisibleLightShieldRearAl;
  G4VPhysicalVolume* physiVisibleLightShieldRearMylar;
  
  // First Delta E Layer
  G4Tubs* solidLayerFirstFront;
  G4LogicalVolume* logicLayerFirstFront;
  G4VPhysicalVolume* physiLayerFirstFront;
/*
  G4Tubs* solidLayerFirstRear;
  G4LogicalVolume* logicLayerFirstRear;
  G4VPhysicalVolume* physiLayerFirstRear;
*/
// Second Delta E Layer
  G4Tubs* solidLayerSecondFront;
  G4LogicalVolume* logicLayerSecondFront;
  G4VPhysicalVolume* physiLayerSecondFront;
  
  G4Tubs* solidLayerSecondRear;
  G4LogicalVolume* logicLayerSecondRear;
  G4VPhysicalVolume* physiLayerSecondRear;
  
  
  // Dead Areas
  G4Tubs* solidLayerFirstFrontDeadAreaFront;
  G4LogicalVolume* logicLayerFirstFrontDeadAreaFront;
  G4VPhysicalVolume* physiLayerFirstFrontDeadAreaFront;
  
  G4Tubs* solidLayerFirstFrontDeadAreaRear;
  G4LogicalVolume* logicLayerFirstFrontDeadAreaRear;
  G4VPhysicalVolume* physiLayerFirstFrontDeadAreaRear;
  /*
    G4Tubs* solidLayerFirstRearDeadAreaFront;
    G4LogicalVolume* logicLayerFirstRearDeadAreaFront;
    G4VPhysicalVolume* physiLayerFirstRearDeadAreaFront;

    G4Tubs* solidLayerFirstRearDeadAreaRear;
    G4LogicalVolume* logicLayerFirstRearDeadAreaRear;
    G4VPhysicalVolume* physiLayerFirstRearDeadAreaRear;
  */
  G4Tubs* solidLayerSecondFrontDeadAreaFront;
  G4LogicalVolume* logicLayerSecondFrontDeadAreaFront;
  G4VPhysicalVolume* physiLayerSecondFrontDeadAreaFront;

  G4Tubs* solidLayerSecondFrontDeadAreaRear;
  G4LogicalVolume* logicLayerSecondFrontDeadAreaRear;
  G4VPhysicalVolume* physiLayerSecondFrontDeadAreaRear;

  G4Tubs* solidLayerSecondRearDeadAreaFront;
  G4LogicalVolume* logicLayerSecondRearDeadAreaFront;
  G4VPhysicalVolume* physiLayerSecondRearDeadAreaFront;

  G4Tubs* solidLayerSecondRearDeadAreaRear;
  G4LogicalVolume* logicLayerSecondRearDeadAreaRear;
  G4VPhysicalVolume* physiLayerSecondRearDeadAreaRear;

  
  // Electrode
  G4Tubs* solidLayerFirstFrontElectrodeFront;
  G4LogicalVolume* logicLayerFirstFrontElectrodeFront;
  G4VPhysicalVolume* physiLayerFirstFrontElectrodeFront;

  G4Tubs* solidLayerFirstFrontElectrodeRear;
  G4LogicalVolume* logicLayerFirstFrontElectrodeRear;
  G4VPhysicalVolume* physiLayerFirstFrontElectrodeRear;
  /*
    G4Tubs* solidLayerFirstRearElectrodeFront;
    G4LogicalVolume* logicLayerFirstRearElectrodeFront;
    G4VPhysicalVolume* physiLayerFirstRearElectrodeFront;

    G4Tubs* solidLayerFirstRearElectrodeRear;
    G4LogicalVolume* logicLayerFirstRearElectrodeRear;
    G4VPhysicalVolume* physiLayerFirstRearElectrodeRear;
  */
  G4Tubs* solidLayerSecondFrontElectrodeFront;
  G4LogicalVolume* logicLayerSecondFrontElectrodeFront;
  G4VPhysicalVolume* physiLayerSecondFrontElectrodeFront;

  G4Tubs* solidLayerSecondFrontElectrodeRear;
  G4LogicalVolume* logicLayerSecondFrontElectrodeRear;
  G4VPhysicalVolume* physiLayerSecondFrontElectrodeRear;

  G4Tubs* solidLayerSecondRearElectrodeFront;
  G4LogicalVolume* logicLayerSecondRearElectrodeFront;
  G4VPhysicalVolume* physiLayerSecondRearElectrodeFront;

  G4Tubs* solidLayerSecondRearElectrodeRear;
  G4LogicalVolume* logicLayerSecondRearElectrodeRear;
  G4VPhysicalVolume* physiLayerSecondRearElectrodeRear;
    
  //Calorimeter
  G4Box* solidCalorimeter;
  G4LogicalVolume* logicCalorimeter;
  G4VPhysicalVolume* physiCalorimeter;

  
  //Collimator
  G4Polyhedra* solidReflectiveSurface;
  G4LogicalVolume* logicReflectiveSurface;
  G4VPhysicalVolume* physiReflectiveSurface;
  /*
    G4Polyhedra* solidTaCollimator;
    G4LogicalVolume* logicTaCollimator;
    G4VPhysicalVolume* physiTaCollimator;
  */
  
  G4Box* solidBottomSurface;
  G4LogicalVolume* logicBottomSurface;
  G4VPhysicalVolume* physiBottomSurface;
  
  //G4Box* solidRearSurface;
  //G4LogicalVolume* logicRearSurface;
  //G4VPhysicalVolume* physiRearSurface;
  
  G4Box* solidPMT;
  G4LogicalVolume* logicPMT;
  G4VPhysicalVolume* physiPMT;

  G4LogicalVolume* logicAirBox;

private:                        // Regions
  G4Region* regionVisibleLightShield;

  G4Region* regionLayerFirst;
  G4Region* regionLayerSecond;

  G4Region* regionCalorimeter;

  G4Region* regionDeadArea;
  G4Region* regionElectrode;
  
  
  G4Region* regionReflectiveSurface;
  /*
    G4Region* regionTaCollimator;
  */

  G4Region* regionBottomSurface;
  
  G4Region* regionRearSurface;
  
private:                        // Materials  
  //G4NistManager*        nistMngrNew;
  /*
  G4Material*		Vacuum;     // Vacuum
  G4Material*           YAP;
  G4Material*           PMMA;
  G4Material*           Pethylene;
  
  G4RotationMatrix* pRotateMatrix;
  */
private:                        // Sub Fuctions
  void MaterialDefinition();
  void SetVisualizationAttributes();
  void GetParametersFromFile(G4String filename);

public:                         // Gets() & Sets()
  G4double getWorldDiam()
  { 
    return worldDiam;
  }
  
  //G4Material* FindMaterial(G4String);
  
  //G4NistManager* nistMngr;
  /*
    std::vector<G4double> getActiveAreaThickness() // In 'um'
    {
    std::vector<G4double> activeAreaThickness(0);
    activeAreaThickness.push_back( layerFirstThickness*1000 );
    activeAreaThickness.push_back( layerSecondThickness*1000 );
    activeAreaThickness.push_back( layerThirdThickness*1000 );
    activeAreaThickness.push_back( layerFourthThickness*1000 );

    return activeAreaThickness;
    }
  */
    
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
