//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
// HEADER
// 
// Last Revised: Mar. 12, 2007
// 
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

#include "EpamDetectorConstruction.hh" // .hh
#include "EpamDefs.hh"

#include <fstream>		// Cpp Include
#include <string>

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4String.hh"		// General
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"	// Geometry

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Polyhedra.hh"
#include "G4Polycone.hh"
#include "G4Sphere.hh"	// Geometry

#include "G4Material.hh"
#include "G4NistManager.hh"	// Material
#include "G4Element.hh"

#include "G4UserLimits.hh"
#include "G4Region.hh"		// Regions & Cut

#include "G4VisAttributes.hh"
#include "G4Colour.hh"		// Visulization
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4GeometryManager.hh"
#include "G4SDManager.hh"

#include "G4SolidStore.hh"
#include "G4RegionStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"

#include "G4RunManager.hh"
#include "WLSMaterials.hh"
//#include "WLSPhotonDetSD.hh"

#include "G4UserLimits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "WLSPhotonDetSD.hh"
//#include "EpamMaterials.hh"
//#include "G4Text.hh"

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

WLSPhotonDetSD* EpamDetectorConstruction::mppcSD = NULL;

EpamDetectorConstruction::EpamDetectorConstruction()
  :physiWorld(NULL),
  // The World Parameter
  worldDiam( WORLD_DIAM ),
  
  // Visible Light Shield Parameter
  visibleLightShieldAlThickness( VISIBLE_LIGHT_SHIELD_AL_THICKNESS ),
  visibleLightShieldMylarThickness( VISIBLE_LIGHT_SHIELD_MYLAR_THICKNESS ),
  visibleLightShieldDiam( VISIBLE_LIGHT_SHIELD_DIAM ),
  visibleLightShieldFrontCenterPosition( VISIBLE_LIGHT_SHIELD_FRONT_CENTER_POSITION ),
  visibleLightShieldRearCenterPosition( VISIBLE_LIGHT_SHIELD_REAR_CENTER_POSITION ),

// Layers Parameter
  layerFirstThickness( LAYER_FIRST_THICKNESS ),
  layerSecondThickness( LAYER_SECOND_THICKNESS ),

  layerFirstDiam( LAYER_FIRST_DIAM ),
  layerSecondDiam( LAYER_SECOND_DIAM ),

  layerFirstFrontCenterPosition( LAYER_FIRST_FRONT_CENTER_POSITION ),
//layerFirstRearCenterPosition( LAYER_FIRST_REAR_CENTER_POSITION ),
  layerSecondFrontCenterPosition( LAYER_SECOND_FRONT_CENTER_POSITION ),
  layerSecondRearCenterPosition( LAYER_SECOND_REAR_CENTER_POSITION ),

// Dead Areas
  deadAreaThickness( DEAD_AREA_THICKNESS ),

// Electrode
  electrodeThickness( ELECTRODE_THICKNESS ),

// Calorimeter Parameter
  calorimeterXY( CALORIMETER_XY ),
  calorimeterZ( CALORIMETER_Z ),
  calorimeterCenterPosition( CALORIMETER_CENTER_POSITION ),

//collimator
  surfaceInnerDiam1( TA_COLLIMATOR_INNER_DIAM_1 ),
  surfaceInnerDiam2( TA_COLLIMATOR_INNER_DIAM_2 ),
  surfaceOutterDiam1( TA_COLLIMATOR_OUTTER_DIAM_1 ),
  surfaceOutterDiam2( TA_COLLIMATOR_OUTTER_DIAM_2 ),
  surfacePlanePosition1( TA_COLLIMATOR_PLANE_POSITION_1 ),
  surfacePlanePosition2( TA_COLLIMATOR_PLANE_POSITION_2 ),
  surfaceFrontPosition( TA_COLLIMATOR_FRONT_POSITION ),
  cladingValue(2),
// Materials Parameter
  visibleLightShieldMaterialNameAl( VISIBLE_LIGHT_SHIELD_MATERIAL_NAME_AL ),
  visibleLightShieldMaterialNameMylar( VISIBLE_LIGHT_SHIELD_MATERIAL_NAME_MYLAR ),
  layersMaterialName( LAYERS_MATERIALS_NAME ),
  calorimeterMaterialName( CALORIMETER_MATERIAL_NAME ),
  electrodeMaterialName( ELECTRODE_MATERIAL_NAME ),
  opticalSurfaceMaterialName(OPTICAL_SURFACE_MATERIAL_NAME)
  
{
  materials=NULL;
} // End of EpamDeterctorConstruction::EpamDetectorConstruction()


EpamDetectorConstruction::~EpamDetectorConstruction()
{
  if(materials) delete materials;
}
/*
G4VPhysicalVolume* EpamDetectorConstruction::ConstructVolume()
{
  materials = WLSMaterials::GetInstance();

  return Construct();
}
*/
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

G4VPhysicalVolume* EpamDetectorConstruction::Construct()
{   
  materials = WLSMaterials::GetInstance();
  G4String pName="";            // Name
  G4double pX=0, pY=0, pZ=0;    // X, Y, Z Half Length
  G4double pRmax=0, pRmin=0;    // Maxium & minimum R Length
  G4double pDeltaZ=0;           // Half Length of Z
  G4double pStartPhi=0, pDeltaPhi=0; // Start & Delta Phi Angle
  //G4double pSTheta=0, pDTheta=0;
  //G4bool pSurfChk=false;        // Check Volume Overlap

  G4VSolid* pSolid=0;           // Solid Volume
  G4LogicalVolume* pCurrentLogical=0; // Current Logical Volume
  G4LogicalVolume* pMotherLogical=0; // Mother Logical Volume
  G4Material* pMaterial=0;      // Material
  G4RotationMatrix* pRotateMatrix=0; // Rotation
  G4ThreeVector pTranslate;   // Translation
  G4bool pMany=0;               // By Default 'false'
  G4int pCopyNumber=0;          // Identifies placement
  G4Transform3D pTransform;

  // The World
  solidWorld = new G4Orb(
                         pName = "world",
                         pRmax = worldDiam / 2.0 );
  logicWorld = new G4LogicalVolume(
                                   pSolid = solidWorld,
                                   FindMaterial("G4_Galactic"),
                                   pName = "World" );
  physiWorld = new G4PVPlacement(
                                 pRotateMatrix = 0,
                                 pTranslate = G4ThreeVector(),
                                 pCurrentLogical = logicWorld,
                                 pName = "world",
                                 pMotherLogical = 0,
                                 pMany = false,
                                 pCopyNumber = 0 );
 
  // The Visible Light Shield
  solidVisibleLightShieldFrontAl = new G4Tubs(
                                              pName = "visibleLightShieldFrontAl",
                                              pRmin = 0,
                                              pRmax = visibleLightShieldDiam / 2.0,
                                              pDeltaZ = visibleLightShieldAlThickness / 2.0,
                                              pStartPhi = 0,
                                              pDeltaPhi = 2*pi );
  solidVisibleLightShieldFrontMylar = new G4Tubs(
						 pName = "visibleLightShieldFrontMylar",
						 pRmin = 0,
						 pRmax = visibleLightShieldDiam / 2.0,
						 pDeltaZ = visibleLightShieldMylarThickness / 2.0,
						 pStartPhi = 0,
						 pDeltaPhi = 2*pi );
  solidVisibleLightShieldRearAl = new G4Tubs(
					     pName = "visibleLightShieldRearAl",
					     pRmin = 0,
					     pRmax = visibleLightShieldDiam / 2.0,
					     pDeltaZ = visibleLightShieldAlThickness / 2.0,
					     pStartPhi = 0,
					     pDeltaPhi = 2*pi );
  solidVisibleLightShieldRearMylar = new G4Tubs(
						pName = "visibleLightShieldRearMylar",
						pRmin = 0,
						pRmax = visibleLightShieldDiam / 2.0,
						pDeltaZ = visibleLightShieldMylarThickness / 2.0,
						pStartPhi = 0,
						pDeltaPhi = 2*pi );
  
  
  logicVisibleLightShieldFrontAl = new G4LogicalVolume(
                                                       pSolid = solidVisibleLightShieldFrontAl,
                                                       FindMaterial("G4_AIR"),
                                                       pName = "visibleLightShieldFrontAl" );
  logicVisibleLightShieldFrontMylar = new G4LogicalVolume(
							  pSolid = solidVisibleLightShieldFrontMylar,
							  FindMaterial("G4_AIR"),
							  pName = "visibleLightShieldFrontMylar" );
  logicVisibleLightShieldRearAl = new G4LogicalVolume(
						      pSolid = solidVisibleLightShieldRearAl,
						      FindMaterial("G4_AIR"),
						      pName = "visibleLightShieldRearAl" );
  logicVisibleLightShieldRearMylar = new G4LogicalVolume(
							 pSolid = solidVisibleLightShieldRearMylar,
							 FindMaterial("G4_AIR"),
							 pName = "visibleLightShieldRearMylar" );
  
  physiVisibleLightShieldFrontAl = new G4PVPlacement(
                                                     pRotateMatrix = 0,
                                                     pTranslate = G4ThreeVector( 0, 0, visibleLightShieldFrontCenterPosition + visibleLightShieldAlThickness / 2.0 ),
                                                     pCurrentLogical = logicVisibleLightShieldFrontAl,
                                                     pName = "visibleLightShieldFrontAl",
                                                     pMotherLogical = logicWorld,
                                                     pMany = false,
                                                     pCopyNumber = 0 );
  
  physiVisibleLightShieldFrontMylar = new G4PVPlacement(
							pRotateMatrix = 0,
							pTranslate = G4ThreeVector( 0, 0, visibleLightShieldFrontCenterPosition - visibleLightShieldMylarThickness / 2.0 ),
							pCurrentLogical = logicVisibleLightShieldFrontMylar,
							pName = "visibleLightShieldFrontMylar",
							pMotherLogical = logicWorld,
							pMany = false,
							pCopyNumber = 0
							);
  physiVisibleLightShieldRearAl = new G4PVPlacement(
						    pRotateMatrix = 0,
						    pTranslate = G4ThreeVector( 0, 0, visibleLightShieldRearCenterPosition - visibleLightShieldAlThickness / 2.0 ),
						    pCurrentLogical = logicVisibleLightShieldRearAl,
						    pName = "visibleLightShieldRearAl",
						    pMotherLogical = logicWorld,
						    pMany = false,
						    pCopyNumber = 0
						    );
  physiVisibleLightShieldRearMylar = new G4PVPlacement(
						       pRotateMatrix = 0,
						       pTranslate = G4ThreeVector( 0, 0, visibleLightShieldFrontCenterPosition + visibleLightShieldMylarThickness / 2.0 ),
						       pCurrentLogical = logicVisibleLightShieldRearMylar,
						       pName = "visibleLightShieldRearMylar",
						       pMotherLogical = logicWorld,
						       pMany = false,
						       pCopyNumber = 0
						       );
  
                                              
  // The Layers

  // Layer First
  solidLayerFirstFront = new G4Tubs(
                                    pName = "layerFirstFront",
                                    pRmin = 0,
                                    pRmax = layerFirstDiam / 2.0,
                                    pDeltaZ = layerFirstThickness / 2.0,
                                    pStartPhi = 0,
                                    pDeltaPhi = 2*pi );
      
  logicLayerFirstFront = new G4LogicalVolume(
					     pSolid = solidLayerFirstFront,
					     FindMaterial("G4_AIR"),
					     pName = "layerFirstFront" );
  physiLayerFirstFront = new G4PVPlacement(
					   pRotateMatrix = 0,
					   pTranslate = G4ThreeVector( 0, 0, layerFirstFrontCenterPosition ),
					   pCurrentLogical = logicLayerFirstFront,
					   pName = "layerFirstFront",
					   pMotherLogical = logicWorld,
					   pMany = false,
					   pCopyNumber = 0  );
  /*
    solidLayerFirstRear = new G4Tubs(
    pName = "layerFirstRear",
    pRmin = 0,
    pRmax = layerFirstDiam / 2.0,
    pDeltaZ = 0,
    pStartPhi = 0,
    pDeltaPhi = 2*pi );
      
    logicLayerFirstRear = new G4LogicalVolume(
    pSolid = solidLayerFirstRear,
    pMaterial = nistMngrNew->FindOrBuildMaterial( layersMaterialName ),
    pName = "layerFirstRear" );
    physiLayerFirstRear = new G4PVPlacement(
    pRotateMatrix = 0,
    pTranslate = G4ThreeVector( 0, 0, layerFirstRearCenterPosition ),
    pCurrentLogical = logicLayerFirstRear,
    pName = "layerFirstRear",
    pMotherLogical = logicWorld,
    pMany = false,
    pCopyNumber = 0  );

  */
  // Layer Second
  solidLayerSecondFront = new G4Tubs(
				     pName = "layerSecondFront",
				     pRmin = 0,
				     pRmax = layerSecondDiam / 2.0,
				     pDeltaZ = layerSecondThickness / 2.0,
				     pStartPhi = 0,
				     pDeltaPhi = 2*pi );
      
  logicLayerSecondFront = new G4LogicalVolume(
					      pSolid = solidLayerSecondFront,
					      FindMaterial("G4_AIR"),
					      pName = "layerSecondFront" );
  physiLayerSecondFront = new G4PVPlacement(
					    pRotateMatrix = 0,
					    pTranslate = G4ThreeVector( 0, 0, layerSecondFrontCenterPosition ),
					    pCurrentLogical = logicLayerSecondFront,
					    pName = "layerSecondFront",
					    pMotherLogical = logicWorld,
					    pMany = false,
					    pCopyNumber = 0  );

  solidLayerSecondRear = new G4Tubs(
                                    pName = "layerSecondRear",
                                    pRmin = 0,
                                    pRmax = layerSecondDiam / 2.0,
                                    pDeltaZ = layerFirstThickness / 2.0,
                                    pStartPhi = 0,
                                    pDeltaPhi = 2*pi );
      
  logicLayerSecondRear = new G4LogicalVolume(
					     pSolid = solidLayerSecondRear,
					     FindMaterial("G4_AIR"),
					     pName = "layerSecondRear" );
  physiLayerSecondRear = new G4PVPlacement(
					   pRotateMatrix = 0,
					   pTranslate = G4ThreeVector( 0, 0, layerSecondRearCenterPosition ),
					   pCurrentLogical = logicLayerSecondRear,
					   pName = "layerSecondRear",
					   pMotherLogical = logicWorld,
					   pMany = false,
					   pCopyNumber = 0  );

  // Dead Area
  
  // -- First Front - Front
  solidLayerFirstFrontDeadAreaFront = new G4Tubs(
                                                 pName = "layerFirstFrontDeadAreaFront",
                                                 pRmin = 0,
                                                 pRmax = layerFirstDiam / 2.0,
                                                 pDeltaZ = deadAreaThickness / 2.0,
                                                 pStartPhi = 0,
                                                 pDeltaPhi = 2*pi );
      
  logicLayerFirstFrontDeadAreaFront = new G4LogicalVolume(
                                                          pSolid = solidLayerFirstFrontDeadAreaFront,
                                                          FindMaterial("G4_AIR"),
                                                          pName = "layerFirstFrontDeadAreaFront" );
  physiLayerFirstFrontDeadAreaFront = new G4PVPlacement(
                                                        pRotateMatrix = 0,
                                                        pTranslate = G4ThreeVector( 0, 0, layerFirstFrontCenterPosition + layerFirstThickness / 2.0 + deadAreaThickness / 2.0),
                                                        pCurrentLogical = logicLayerFirstFrontDeadAreaFront,
                                                        pName = "layerFirstFrontDeadAreaFront",
                                                        pMotherLogical = logicWorld,
                                                        pMany = false,
                                                        pCopyNumber = 0
							);
  // -- First Front - Rear
  solidLayerFirstFrontDeadAreaRear = new G4Tubs(
						pName = "layerFirstFrontDeadAreaRear",
						pRmin = 0,
						pRmax = layerFirstDiam / 2.0,
						pDeltaZ = deadAreaThickness / 2.0,
						pStartPhi = 0,
						pDeltaPhi = 2*pi );
      
  logicLayerFirstFrontDeadAreaRear = new G4LogicalVolume(
							 pSolid = solidLayerFirstFrontDeadAreaRear,
							 FindMaterial("G4_AIR"),
							 pName = "layerFirstFrontDeadAreaRear" );
  physiLayerFirstFrontDeadAreaRear = new G4PVPlacement(
						       pRotateMatrix = 0,
						       pTranslate = G4ThreeVector( 0, 0, layerFirstFrontCenterPosition - layerFirstThickness / 2.0 - deadAreaThickness / 2.0),
						       pCurrentLogical = logicLayerFirstFrontDeadAreaRear,
						       pName = "layerFirstFrontDeadAreaRear",
						       pMotherLogical = logicWorld,
						       pMany = false,
						       pCopyNumber = 0  );
  /*
  // -- First Rear - Front
  solidLayerFirstRearDeadAreaFront = new G4Tubs(
  pName = "layerFirstRearDeadAreaFront",
  pRmin = 0,
  pRmax = layerFirstDiam / 2.0,
  pDeltaZ = deadAreaThickness / 2.0,
  pStartPhi = 0,
  pDeltaPhi = 2*pi );
      
  logicLayerFirstRearDeadAreaFront = new G4LogicalVolume(
  pSolid = solidLayerFirstRearDeadAreaFront,
  pMaterial = nistMngrNew->FindOrBuildMaterial( layersMaterialName ),
  pName = "layerFirstRearDeadAreaFront" );
  physiLayerFirstRearDeadAreaFront = new G4PVPlacement(
  pRotateMatrix = 0,
  pTranslate = G4ThreeVector( 0, 0, layerFirstRearCenterPosition + layerFirstThickness / 2.0 + deadAreaThickness / 2.0),
  pCurrentLogical = logicLayerFirstRearDeadAreaFront,
  pName = "layerFirstRearDeadAreaFront",
  pMotherLogical = logicWorld,
  pMany = false,
  pCopyNumber = 0  );
  // -- First Rear - Rear
  solidLayerFirstRearDeadAreaRear = new G4Tubs(
  pName = "layerFirstRearDeadAreaRear",
  pRmin = 0,
  pRmax = layerFirstDiam / 2.0,
  pDeltaZ = deadAreaThickness / 2.0,
  pStartPhi = 0,
  pDeltaPhi = 2*pi );
      
  logicLayerFirstRearDeadAreaRear = new G4LogicalVolume(
  pSolid = solidLayerFirstRearDeadAreaRear,
  pMaterial = nistMngrNew->FindOrBuildMaterial( layersMaterialName ),
  pName = "layerFirstRearDeadAreaRear" );
  physiLayerFirstRearDeadAreaRear = new G4PVPlacement(
  pRotateMatrix = 0,
  pTranslate = G4ThreeVector( 0, 0, layerFirstRearCenterPosition - layerFirstThickness / 2.0 - deadAreaThickness / 2.0),
  pCurrentLogical = logicLayerFirstRearDeadAreaRear,
  pName = "layerFirstRearDeadAreaRear",
  pMotherLogical = logicWorld,
  pMany = false,
  pCopyNumber = 0  );
  */
  // -- Second Front - Front
  solidLayerSecondFrontDeadAreaFront = new G4Tubs(
						  pName = "layerSecondFrontDeadAreaFront",
						  pRmin = 0,
						  pRmax = layerSecondDiam / 2.0,
						  pDeltaZ = deadAreaThickness / 2.0,
						  pStartPhi = 0,
						  pDeltaPhi = 2*pi );
      
  logicLayerSecondFrontDeadAreaFront = new G4LogicalVolume(
							   pSolid = solidLayerSecondFrontDeadAreaFront,
							   FindMaterial("G4_AIR"),
							   pName = "layerSecondFrontDeadAreaFront" );
  physiLayerSecondFrontDeadAreaFront = new G4PVPlacement(
							 pRotateMatrix = 0,
							 pTranslate = G4ThreeVector( 0, 0, layerSecondFrontCenterPosition + layerSecondThickness / 2.0 + deadAreaThickness / 2.0),
							 pCurrentLogical = logicLayerSecondFrontDeadAreaFront,
							 pName = "layerSecondFrontDeadAreaFront",
							 pMotherLogical = logicWorld,
							 pMany = false,
							 pCopyNumber = 0  );
  // -- Second Front - Rear
  solidLayerSecondFrontDeadAreaRear = new G4Tubs(
                                                 pName = "layerSecondFrontDeadAreaRear",
                                                 pRmin = 0,
                                                 pRmax = layerSecondDiam / 2.0,
                                                 pDeltaZ = deadAreaThickness / 2.0,
                                                 pStartPhi = 0,
                                                 pDeltaPhi = 2*pi );
      
  logicLayerSecondFrontDeadAreaRear = new G4LogicalVolume(
                                                          pSolid = solidLayerSecondFrontDeadAreaRear,
                                                          FindMaterial("G4_AIR"),
                                                          pName = "layerSecondFrontDeadAreaRear" );
  physiLayerSecondFrontDeadAreaRear = new G4PVPlacement(
                                                        pRotateMatrix = 0,
                                                        pTranslate = G4ThreeVector( 0, 0, layerSecondFrontCenterPosition - layerSecondThickness / 2.0 - deadAreaThickness / 2.0),
                                                        pCurrentLogical = logicLayerSecondFrontDeadAreaRear,
                                                        pName = "layerSecondFrontDeadAreaRear",
                                                        pMotherLogical = logicWorld,
                                                        pMany = false,
                                                        pCopyNumber = 0  );
  // -- Second Rear - Front
  solidLayerSecondRearDeadAreaFront = new G4Tubs(
                                                 pName = "layerSecondRearDeadAreaFront",
                                                 pRmin = 0,
                                                 pRmax = layerSecondDiam / 2.0,
                                                 pDeltaZ = deadAreaThickness / 2.0,
                                                 pStartPhi = 0,
                                                 pDeltaPhi = 2*pi );
      
  logicLayerSecondRearDeadAreaFront = new G4LogicalVolume(
                                                          pSolid = solidLayerSecondRearDeadAreaFront,
                                                          FindMaterial("G4_AIR"),
                                                          pName = "layerSecondRearDeadAreaFront" );
  physiLayerSecondRearDeadAreaFront = new G4PVPlacement(
                                                        pRotateMatrix = 0,
                                                        pTranslate = G4ThreeVector( 0, 0, layerSecondRearCenterPosition + layerFirstThickness / 2.0 + deadAreaThickness / 2.0),
                                                        pCurrentLogical = logicLayerSecondRearDeadAreaFront,
                                                        pName = "layerSecondRearDeadAreaFront",
                                                        pMotherLogical = logicWorld,
                                                        pMany = false,
                                                        pCopyNumber = 0  );
  // -- Second Rear - Rear
  solidLayerSecondRearDeadAreaRear = new G4Tubs(
						pName = "layerSecondRearDeadAreaRear",
						pRmin = 0,
						pRmax = layerSecondDiam / 2.0,
						pDeltaZ = deadAreaThickness / 2.0,
						pStartPhi = 0,
						pDeltaPhi = 2*pi );
      
  logicLayerSecondRearDeadAreaRear = new G4LogicalVolume(
							 pSolid = solidLayerSecondRearDeadAreaRear,
							 FindMaterial("G4_AIR"),
							 pName = "layerSecondRearDeadAreaRear" );
  physiLayerSecondRearDeadAreaRear = new G4PVPlacement(
						       pRotateMatrix = 0,
						       pTranslate = G4ThreeVector( 0, 0, layerSecondRearCenterPosition - layerFirstThickness / 2.0 - deadAreaThickness / 2.0),
						       pCurrentLogical = logicLayerSecondRearDeadAreaRear,
						       pName = "layerSecondRearDeadAreaRear",
						       pMotherLogical = logicWorld,
						       pMany = false,
						       pCopyNumber = 0  );

  // Electrode
  // -- First Front - Front
  solidLayerFirstFrontElectrodeFront = new G4Tubs(
						  pName = "layerFirstFrontElectrodeFront",
						  pRmin = 0,
						  pRmax = layerFirstDiam / 2.0,
						  pDeltaZ = electrodeThickness / 2.0,
						  pStartPhi = 0,
						  pDeltaPhi = 2*pi );
      
  logicLayerFirstFrontElectrodeFront = new G4LogicalVolume(
							   pSolid = solidLayerFirstFrontElectrodeFront,
							   FindMaterial("G4_AIR"),
							   pName = "layerFirstFrontElectrodeFront" );
  physiLayerFirstFrontElectrodeFront = new G4PVPlacement(
							 pRotateMatrix = 0,
							 pTranslate = G4ThreeVector( 0, 0, layerFirstFrontCenterPosition + layerFirstThickness / 2.0 + deadAreaThickness + electrodeThickness / 2.0),
							 pCurrentLogical = logicLayerFirstFrontElectrodeFront,
							 pName = "layerFirstFrontElectrodeFront",
							 pMotherLogical = logicWorld,
							 pMany = false,
							 pCopyNumber = 0  );
  // -- First Front - Rear
  solidLayerFirstFrontElectrodeRear = new G4Tubs(
                                                 pName = "layerFirstFrontElectrodeRear",
                                                 pRmin = 0,
                                                 pRmax = layerFirstDiam / 2.0,
                                                 pDeltaZ = electrodeThickness / 2.0,
                                                 pStartPhi = 0,
                                                 pDeltaPhi = 2*pi );
      
  logicLayerFirstFrontElectrodeRear = new G4LogicalVolume(
                                                          pSolid = solidLayerFirstFrontElectrodeRear,
                                                          FindMaterial("G4_AIR"),
                                                          pName = "layerFirstFrontElectrodeRear" );
  physiLayerFirstFrontElectrodeRear = new G4PVPlacement(
                                                        pRotateMatrix = 0,
                                                        pTranslate = G4ThreeVector( 0, 0, layerFirstFrontCenterPosition - layerFirstThickness / 2.0 - deadAreaThickness - electrodeThickness / 2.0),
                                                        pCurrentLogical = logicLayerFirstFrontElectrodeRear,
                                                        pName = "layerFirstFrontElectrodeRear",
                                                        pMotherLogical = logicWorld,
                                                        pMany = false,
                                                        pCopyNumber = 0  );
  /*
  // -- First Rear - Front
  solidLayerFirstRearElectrodeFront = new G4Tubs(
  pName = "layerFirstRearElectrodeFront",
  pRmin = 0,
  pRmax = layerFirstDiam / 2.0,
  pDeltaZ = electrodeThickness / 2.0,
  pStartPhi = 0,
  pDeltaPhi = 2*pi );
      
  logicLayerFirstRearElectrodeFront = new G4LogicalVolume(
  pSolid = solidLayerFirstRearElectrodeFront,
  pMaterial = nistMngrNew->FindOrBuildMaterial( layersMaterialName ),
  pName = "layerFirstRearElectrodeFront" );
  physiLayerFirstRearElectrodeFront = new G4PVPlacement(
  pRotateMatrix = 0,
  pTranslate = G4ThreeVector( 0, 0, layerFirstRearCenterPosition + layerFirstThickness / 2.0 + deadAreaThickness + electrodeThickness / 2.0),
  pCurrentLogical = logicLayerFirstRearElectrodeFront,
  pName = "layerFirstRearElectrodeFront",
  pMotherLogical = logicWorld,
  pMany = false,
  pCopyNumber = 0  );
 
  // -- First Rear - Rear
  solidLayerFirstRearElectrodeRear = new G4Tubs(
  pName = "layerFirstRearElectrodeRear",
  pRmin = 0,
  pRmax = layerFirstDiam / 2.0,
  pDeltaZ = electrodeThickness / 2.0,
  pStartPhi = 0,
  pDeltaPhi = 2*pi );
      
  logicLayerFirstRearElectrodeRear = new G4LogicalVolume(
  pSolid = solidLayerFirstRearElectrodeRear,
  pMaterial = nistMngrNew->FindOrBuildMaterial( layersMaterialName ),
  pName = "layerFirstRearElectrodeRear" );
  physiLayerFirstRearElectrodeRear = new G4PVPlacement(
  pRotateMatrix = 0,
  pTranslate = G4ThreeVector( 0, 0, layerFirstRearCenterPosition - layerFirstThickness / 2.0 - deadAreaThickness - electrodeThickness / 2.0),
  pCurrentLogical = logicLayerFirstRearElectrodeRear,
  pName = "layerFirstRearElectrodeRear",
  pMotherLogical = logicWorld,
  pMany = false,
  pCopyNumber = 0  );
  */
  // -- Second Front - Front
  solidLayerSecondFrontElectrodeFront = new G4Tubs(
						   pName = "layerSecondFrontElectrodeFront",
						   pRmin = 0,
						   pRmax = layerSecondDiam / 2.0,
						   pDeltaZ = electrodeThickness / 2.0,
						   pStartPhi = 0,
						   pDeltaPhi = 2*pi );
      
  logicLayerSecondFrontElectrodeFront = new G4LogicalVolume(
							    pSolid = solidLayerSecondFrontElectrodeFront,
							    FindMaterial("G4_AIR"),
							    pName = "layerSecondFrontElectrodeFront" );
  physiLayerSecondFrontElectrodeFront = new G4PVPlacement(
							  pRotateMatrix = 0,
							  pTranslate = G4ThreeVector( 0, 0, layerSecondFrontCenterPosition + layerSecondThickness / 2.0 + deadAreaThickness + electrodeThickness / 2.0),
							  pCurrentLogical = logicLayerSecondFrontElectrodeFront,
							  pName = "layerSecondFrontElectrodeFront",
							  pMotherLogical = logicWorld,
							  pMany = false,
							  pCopyNumber = 0  );
  // -- Second Front - Rear
  solidLayerSecondFrontElectrodeRear = new G4Tubs(
						  pName = "layerSecondFrontElectrodeRear",
						  pRmin = 0,
						  pRmax = layerSecondDiam / 2.0,
						  pDeltaZ = electrodeThickness / 2.0,
						  pStartPhi = 0,
						  pDeltaPhi = 2*pi );
      
  logicLayerSecondFrontElectrodeRear = new G4LogicalVolume(
							   pSolid = solidLayerSecondFrontElectrodeRear,
							   FindMaterial("G4_AIR"),
							   pName = "layerSecondFrontElectrodeRear" );
  physiLayerSecondFrontElectrodeRear = new G4PVPlacement(
							 pRotateMatrix = 0,
							 pTranslate = G4ThreeVector( 0, 0, layerSecondFrontCenterPosition - layerSecondThickness / 2.0 - deadAreaThickness - electrodeThickness / 2.0),
							 pCurrentLogical = logicLayerSecondFrontElectrodeRear,
							 pName = "layerSecondFrontElectrodeRear",
							 pMotherLogical = logicWorld,
							 pMany = false,
							 pCopyNumber = 0  );
  // -- Second Rear - Front
  solidLayerSecondRearElectrodeFront = new G4Tubs(
						  pName = "layerSecondRearElectrodeFront",
						  pRmin = 0,
						  pRmax = layerSecondDiam / 2.0,
						  pDeltaZ = electrodeThickness / 2.0,
						  pStartPhi = 0,
						  pDeltaPhi = 2*pi );
      
  logicLayerSecondRearElectrodeFront = new G4LogicalVolume(
							   pSolid = solidLayerSecondRearElectrodeFront,
							   FindMaterial("G4_AIR"),
							   pName = "layerSecondRearElectrodeFront" );
  physiLayerSecondRearElectrodeFront = new G4PVPlacement(
							 pRotateMatrix = 0,
							 pTranslate = G4ThreeVector( 0, 0, layerSecondRearCenterPosition + layerFirstThickness / 2.0 + deadAreaThickness + electrodeThickness / 2.0),
							 pCurrentLogical = logicLayerSecondRearElectrodeFront,
							 pName = "layerSecondRearElectrodeFront",
							 pMotherLogical = logicWorld,
							 pMany = false,
							 pCopyNumber = 0  );
  // -- Second Rear - Rear
  solidLayerSecondRearElectrodeRear = new G4Tubs(
                                                 pName = "layerSecondRearElectrodeRear",
                                                 pRmin = 0,
                                                 pRmax = layerSecondDiam / 2.0,
                                                 pDeltaZ = electrodeThickness / 2.0,
                                                 pStartPhi = 0,
                                                 pDeltaPhi = 2*pi );
      
  logicLayerSecondRearElectrodeRear = new G4LogicalVolume(
                                                          pSolid = solidLayerSecondRearElectrodeRear,
                                                          FindMaterial("G4_AIR"),
                                                          pName = "layerSecondRearElectrodeRear" );
  physiLayerSecondRearElectrodeRear = new G4PVPlacement(
                                                        pRotateMatrix = 0,
                                                        pTranslate = G4ThreeVector( 0, 0, layerSecondRearCenterPosition - layerFirstThickness / 2.0 - deadAreaThickness - electrodeThickness / 2.0),
                                                        pCurrentLogical = logicLayerSecondRearElectrodeRear,
                                                        pName = "layerSecondRearElectrodeRear",
                                                        pMotherLogical = logicWorld,
                                                        pMany = false,
                                                        pCopyNumber = 0  );
  //
  //------------------------------House-----------------------------------------------------
  //
  G4Box* solidHouse = new G4Box(
				pName = "house",
				pX = 400.*mm/2,
				pY = 400.*mm/2,
				pZ = 400.*mm/2 );
  
  G4LogicalVolume* logicHouse = new G4LogicalVolume(
                                                    pSolid = solidHouse,
						    FindMaterial("G4_AIR"),
						    pName = "house" );
  
  G4VPhysicalVolume* physiHouse = new G4PVPlacement(
						    pRotateMatrix = 0,
						    pTranslate = G4ThreeVector(),
						    pCurrentLogical = logicHouse,
						    pName = "house",
						    pMotherLogical = logicWorld,
						    pMany = false,
						    pCopyNumber = 0 );
  
  //
  //
  //----------------------Reflective Surface--------------------------------------------
  //
    
  G4Box* solidReflective = new G4Box(
                                     pName = "reflective",
				     pX = 324*mm/2,
				     pY = 324*mm/2,
				     pZ = 29.*mm/2 );
  G4LogicalVolume* logicReflective = new G4LogicalVolume(
							 pSolid = solidReflective,
							 FindMaterial("G4_AIR"),
							 pName = "reflective" );
  G4VPhysicalVolume* physiReflective = new G4PVPlacement(
                                                         pRotateMatrix = 0,
							 pTranslate =G4ThreeVector( 0, 0, 0 ),
							 pCurrentLogical = logicReflective,
							 pName = "reflective",
							 pMotherLogical = logicHouse,
							 pMany = false,
							 pCopyNumber = 0 );
  
  //
  //----------------------------Air Box--------------------------------------------------------------------
  //
  G4Box* solidAirBox = new G4Box(
				 pName = "airBox",
				 pX = 322*mm/2,
				 pY = 322*mm/2,
				 pZ = 27.0*mm/2 );//27
  logicAirBox = new G4LogicalVolume(
				    pSolid = solidAirBox,
				    FindMaterial("G4_AIR"),
				    pName = "airBox" );
  
  G4OpticalSurface* TiO2Surface = new G4OpticalSurface("TiO2Surface",
                                                       glisur,
                                                       ground,
                                                       dielectric_metal,
                                                       1);
  
  G4MaterialPropertiesTable* TiO2SurfaceProperty =
                                             new G4MaterialPropertiesTable();

  G4double p_TiO2[2] = {2.00*eV, 3.47*eV};
  G4double refl_TiO2[2] = {1,1};
  G4double effi_TiO2[2] = {0, 0};

  TiO2SurfaceProperty -> AddProperty("REFLECTIVITY",p_TiO2,refl_TiO2,2);
  TiO2SurfaceProperty -> AddProperty("EFFICIENCY",p_TiO2,effi_TiO2,2);

  TiO2Surface -> SetMaterialPropertiesTable(TiO2SurfaceProperty);
  
  G4VPhysicalVolume* physiAirBox = new G4PVPlacement(
                                                     pRotateMatrix = 0,
						     pTranslate =G4ThreeVector( 0, 0, 0 ),
						     pCurrentLogical = logicAirBox,
						     pName = "airBox",
						     pMotherLogical = logicReflective,
						     pMany = false,
						     pCopyNumber = 0 );
    
  G4LogicalSkinSurface* logicSkinSuur = new G4LogicalSkinSurface("TiO2Surface",logicAirBox,TiO2Surface);
  //
  // ----------------------------The Calorimeter-----------------------------------------------------------
  //
  solidCalorimeter = new G4Box(
                               pName = "calorimeter",
                               pX = calorimeterZ / 2.0,
                               pY = calorimeterZ / 2.0,
                               pZ = calorimeterXY / 2.0 );
  logicCalorimeter = new G4LogicalVolume(
                                         pSolid = solidCalorimeter,
                                         FindMaterial("Polystyrene"),
					 pName = "calorimeter" );
  physiCalorimeter = new G4PVPlacement(
                                       pRotateMatrix = 0,
                                       pTranslate = G4ThreeVector( 0, 0, calorimeterCenterPosition ),
                                       pCurrentLogical = logicCalorimeter,
                                       pName = "calorimeter",
                                       pMotherLogical = logicAirBox,
                                       pMany = false,
                                       pCopyNumber = 0  );
  //
  //---------------------------------------------------------------------------------
  //
  
  //
  //---------------------WLS---------------------------------------------------------
  //
  ConstructFiber();
  //
  //
  
  // Setup Visualization Attributes
  //SetVisualizationAttributes();

  return physiWorld;
  
} // End of EpamDetectorConstruction::Construct()

void EpamDetectorConstruction::ConstructFiber()
{
  G4VSolid* pSolid=0;           // Solid Volume
  G4LogicalVolume* pCurrentLogical=0; // Current Logical Volume
  G4LogicalVolume* pMotherLogical=0; // Mother Logical Volume
  G4Material* pMaterial=0;      // Material
  G4RotationMatrix* pRotateMatrix=0; // Rotation
  G4ThreeVector pTranslate;   // Translation
  G4bool pMany=0;               // By Default 'false'
  G4int pCopyNumber=0;          // Identifies placement
  G4Transform3D pTransform;
  G4String pName="";
  
 //   if (!(logicHole) || !(physiHole) ) {
  //std::ostringstream o;
  //o << "The Fiber Hole has not been constructed";
  //G4Exception("EpamDetectorConstruction::ConstructFiber","",
  //FatalException,o.str().c_str());
   // }
  
  // Pointers to the most recently constructed volume
  G4LogicalVolume* logicPlacement = logicCalorimeter;
  G4VPhysicalVolume* physiPlacement = physiCalorimeter;

  //--------------------------------------------------
  // Fiber Construction
  //-------------------------------------------------- 

  // Boundary Surface Properties
  G4OpticalSurface* OpSurface = NULL;
 
  //if (surfaceRoughness < 1.)
  OpSurface = new G4OpticalSurface("RoughSurface",          // Surface Name
				   glisur,                  // SetModel
				   ground,                  // SetFinish
				   dielectric_dielectric,   // SetType
				   1);       // SetPolish
  
  G4LogicalVolume   *logicClad1, *logicClad2;
  G4VPhysicalVolume *physiClad1, *physiClad2;
  
  // Determine the number of cladding layers to be built
  //switch ( numOfCladLayers ) {
  G4int cladValue=2;
  G4double firstFiberPositionX = -148.9 *mm; //-154.5 * mm;// change to -148.9*mm??
  G4double fiberGap = 19.82 *mm; //20 *mm;// change to 19.82*mm??
  G4double firstFiberCenterPosition = 0.0 *mm; //11.5 *mm;// change to 12*mm??
  G4double fiberPitch = 1.0*mm;
  
  switch(cladValue){
  case 2:
    
    //--------------------------------------------------
    // Cladding 2
    //--------------------------------------------------
    
    
   
    G4VSolid* solidClad2;
    
    //if (XYRatio == 1.)
    //solidClad2 = new G4Tubs("Clad2",0.,clad2RX,clad2Z,0.0*rad,twopi*rad);
    solidClad2 = new G4Tubs("Cald2",0,1.0*mm,160*mm,0.0*rad,twopi*rad);
    //else
    //solidClad2 = new G4EllipticalTube("Clad2",clad2RX,clad2RY,clad2Z);
    
    logicClad2  = new G4LogicalVolume(solidClad2,
				      FindMaterial("FPethylene"),
				      "Clad2");
    
    //G4PVPlacement* physiClad2;
    for (G4int j =0; j<2; j++)
      { 
	if (j==0)
	  {
	    pRotateMatrix = new G4RotationMatrix(0,0*deg,0*deg);
	    for (G4int i=0; i<16; i++)
	      {
		for(G4int k=0; k!=9; ++k){// 10 to 9
		  G4RotationMatrix rm;
		  rm.rotateX(90*deg);
		  physiClad2 = new G4PVPlacement(
						 
						 pTransform = G4Transform3D(rm, G4ThreeVector((firstFiberPositionX + i*fiberGap +k*fiberPitch) , 0, 11.5*mm)),
						 //pTranslate = G4ThreeVector((firstFiberPositionX + i*fiberGap + k*fiberPitch) , 12*mm, firstFiberCenterPosition ),
						 pCurrentLogical = logicClad2,
						 pName = "Clad2",
						 pMotherLogical = logicPlacement,
						 pMany = false,
						 pCopyNumber = i*9+k );
		} 
	      }
	  }
	else
	  { 
	    pRotateMatrix = new G4RotationMatrix(0*deg,90*deg,0*deg);
	    for (G4int i=0; i<16; i++)
	      { 
		for(G4int k=0; k!=9; ++k){ 
		  G4RotationMatrix rm;
		  rm.rotateY(90*deg);
		  physiClad2 = new G4PVPlacement(
						 pTransform = G4Transform3D(rm,G4ThreeVector(0, (firstFiberPositionX + i*fiberGap + k*fiberPitch), -11.5*mm)),
						 //pTransform = G4Transform3D(rm, G4ThreeVector(0, (firstFiberPositionX + i*fiberGap + k*fiberPitch), -firstFiberCenterPosition)),
						 pCurrentLogical = logicClad2,     //should be checked
						 pName = "Clad2",
						 pMotherLogical = logicPlacement,
						 pMany = false,
						 pCopyNumber = j*144+i*9+k );
		}
	      }
	  } 
      }
    
    // Place the rough surface only if needed
    if (OpSurface) {
      new G4LogicalBorderSurface("surfaceClad2Out",
				 physiClad2,
				 physiPlacement,
				 OpSurface);
      new G4LogicalBorderSurface("surfaceClad2In",
				 physiPlacement,
				 physiClad2,
				 OpSurface);
    }
    
    logicPlacement = logicClad2;
    physiPlacement = physiClad2;
    //return;
    /*
  case 1:
    
    //--------------------------------------------------
    // Cladding 1
    //--------------------------------------------------
    
    G4VSolid* solidClad1;
    
    //if (XYRatio == 1.)
    //solidClad1 = new G4Tubs("Clad1",0.,clad1RX,clad1Z,0.0*rad,twopi*rad);
    solidClad1 = new G4Tubs("Cald1",0,0.9*mm,320*mm,0.0*rad,twopi*rad);
    //else
    //solidClad1 = new G4EllipticalTube("Clad1",clad1RX,clad1RY,clad1Z);
    
    logicClad1 = new G4LogicalVolume(solidClad1,
				     FindMaterial("Pethylene"),
				     "Clad1");
    
    for (G4int j =0; j<2; j++)
      { 
	if (j==0)
	  {
	    pRotateMatrix = new G4RotationMatrix(0,0*deg,0);
	    for (G4int i=0; i<16; i++)
	      {
		for(G4int k=0; k!=9; ++k){// 10 to 9
		  //G4RotationMatrix rm;
		  //rm.rotateX(90*deg);
		  physiClad1 = new G4PVPlacement(
						 pRotateMatrix,
						 //pTransform = G4Transform3D(rm, G4ThreeVector((firstFiberPositionX + i*fiberGap) , 0, firstFiberCenterPosition- k*fiberPitch)),
						 pTranslate = G4ThreeVector((firstFiberPositionX + i*fiberGap + k*fiberPitch) , 0, firstFiberCenterPosition ),
						 pCurrentLogical = logicClad1,
						 pName = "Clad1",
						 pMotherLogical = logicPlacement,
						 pMany = false,
						 pCopyNumber = i*9+k );
		} 
	      }
	  }
	else
	  { 
	    pRotateMatrix = new G4RotationMatrix(0*deg,90*deg,0);
	    for (G4int i=0; i<16; i++)
	      { 
		for(G4int k=0; k!=9; ++k){ 
		  G4RotationMatrix rm;
		  rm.rotateZ(90*deg);
		  physiClad1 = new G4PVPlacement(pRotateMatrix,
						 pTranslate = G4ThreeVector(0, (firstFiberPositionX + i*fiberGap + k*fiberPitch), -firstFiberCenterPosition ),
						 //pTransform = G4Transform3D(rm, G4ThreeVector(0, (firstFiberPositionX + i*fiberGap + k*fiberPitch), -firstFiberCenterPosition)),
						 pCurrentLogical = logicClad1,     //should be checked
						 pName = "Clad1",
						 pMotherLogical = logicPlacement,
						 pMany = false,
						 pCopyNumber = j*144+i*9+k );
		}
	      }
	  } 
      }
    //
    //
    //
    
    // Place the rough surface only if needed
    if (OpSurface) {
      new G4LogicalBorderSurface("surfaceClad1Out",
				 physiClad1,
				 physiPlacement,
				 OpSurface);
      new G4LogicalBorderSurface("surfaceClad1In",
				 physiPlacement,
				 physiClad1,
				 OpSurface);
    }
    
    logicPlacement = logicClad1;
    physiPlacement = physiClad1;
    */
    //return;
    
  default:
    
    //--------------------------------------------------
    // WLS Fiber
    //--------------------------------------------------
    
    G4VSolid* solidWLSfiber;
    
    //if (XYRatio == 1.)
    solidWLSfiber =
      new G4Tubs("WLSFiber",0.,0.8*mm,160*mm,0.0*rad,twopi*rad);//1*mm,1*m
    //else
    //solidWLSfiber =
    //new G4EllipticalTube("WLSFiber",wlsfiberRX,wlsfiberRY,wlsfiberZ);
    
    G4LogicalVolume* logicWLSfiber = new G4LogicalVolume(solidWLSfiber,
							   FindMaterial("PMMA"),
							   "WLSFiber");
    
    logicWLSfiber->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,10*ms));
    
    G4VPhysicalVolume* physiWLSfiber = new G4PVPlacement(0,
							 G4ThreeVector(0.0,0.0,0.0),
							 logicWLSfiber,
							 "WLSFiber",
							 logicPlacement,
							 false,
							 0);
    
    // Place the rough surface only if needed
    if (OpSurface) {
      new G4LogicalBorderSurface("surfaceWLSOut",
				 physiWLSfiber,
				 physiPlacement,
				 OpSurface);
      new G4LogicalBorderSurface("surfaceWLSIn",
				 physiPlacement,
				 physiWLSfiber,
				 OpSurface);
    }
    
  }
  
  /*
  //--------------------------------------------------
  // Coupling at the read-out end
  //--------------------------------------------------  

  // Clear Fiber (Coupling Layer)
  G4VSolid* solidCouple = new G4Box("Couple",coupleRX,coupleRY,coupleZ);

  G4LogicalVolume*   logicCouple = new G4LogicalVolume(solidCouple,
                                                       FindMaterial("G4_AIR"),
                                                       "Couple");

  new G4PVPlacement(0,
                    G4ThreeVector(0.0,0.0,coupleOrigin),
                    logicCouple,
                    "Couple",
                    logicWorld,
                    false,
                    0);

  //--------------------------------------------------
  // A logical layer in front of PhotonDet
  //--------------------------------------------------  

  // Purpose: Preventing direct dielectric to metal contact  

  // Check for valid placement of PhotonDet
  if (mppcTheta > std::atan(mppcDist / mppcHalfL)) {

     mppcTheta = 0;
     mppcOriginX  = std::sin(mppcTheta) * (mppcDist + clrfiberZ);
     mppcOriginZ  = -coupleZ + std::cos(mppcTheta) * (mppcDist + clrfiberZ);
     G4cerr << "Invalid alignment.  Alignment Reset to 0" << G4endl;     
  }
 
  // Clear Fiber (Coupling Layer)
  G4VSolid* solidClrfiber;
 
  if ( mppcShape == "Square" )
    solidClrfiber = 
                new G4Box("ClearFiber",clrfiberHalfL,clrfiberHalfL,clrfiberZ);
  else
    solidClrfiber =
       new G4Tubs("ClearFiber",0.,clrfiberHalfL,clrfiberZ,0.0*rad,twopi*rad);

  G4LogicalVolume*   logicClrfiber =
                                          new G4LogicalVolume(solidClrfiber,
                                                       FindMaterial("G4_AIR"),
                                                       "ClearFiber");

  new G4PVPlacement(new G4RotationMatrix(CLHEP::HepRotationY(-mppcTheta)),
                    G4ThreeVector(mppcOriginX,0.0,mppcOriginZ),
                    logicClrfiber,
                    "ClearFiber",
                    logicCouple,
                    false,
                    0); 
  */
  //--------------------------------------------------
  // PhotonDet (Sensitive Detector)
  //--------------------------------------------------  

  // Physical Construction
  G4VSolid* solidPhotonDet;
  
  //if ( mppcShape == "Square" )
  solidPhotonDet = new G4Box("PhotonDet",5*mm ,5*mm ,0.5*mm);
  //else
  //solidPhotonDet =
  //           new G4Tubs("PhotonDet",0.,mppcHalfL,mppcZ,0.0*rad,twopi*rad);

  G4LogicalVolume*   logicPhotonDet = new G4LogicalVolume(solidPhotonDet,
							  FindMaterial("G4_Al"),
							  "PhotonDet");
  for (G4int j =0; j<2; j++){ 
    if (j==0){
      //pRotateMatrix = new G4RotationMatrix(0,0*deg,0*deg);
      for (G4int i=0; i<16; i++){
	new G4PVPlacement(0,
			  G4ThreeVector(-144.9*mm+i*fiberGap, 161.0*mm, 11.5*mm),
			  logicPhotonDet,
			  "PhotonDet",
			  logicAirBox,
			  false,
			  i);
      }
    }
    else{
      for (G4int i=0; i<16; i++){
	G4RotationMatrix rm;
	rm.rotateZ(90*deg);
	new G4PVPlacement(
			  pTransform = G4Transform3D(rm,G4ThreeVector(161.0*mm, (-144.9*mm+i*fiberGap), -11.5*mm)),
			  logicPhotonDet,
			  "PhotonDet",
			  logicAirBox,
			  false,
			  j*16+i);
      }
    }
  }
  // PhotonDet Surface Properties
  G4OpticalSurface* PhotonDetSurface = new G4OpticalSurface("PhotonDetSurface",
							    glisur,
							    ground,
							    dielectric_metal,
							    1);
  
  G4MaterialPropertiesTable* PhotonDetSurfaceProperty =
    new G4MaterialPropertiesTable();
  
  G4double p_mppc[2] = {2.00*eV, 3.47*eV};
  G4double refl_mppc[2] = {0,0};
  G4double effi_mppc[2] = {1, 1};
  
  PhotonDetSurfaceProperty -> AddProperty("REFLECTIVITY",p_mppc,refl_mppc,2);
  PhotonDetSurfaceProperty -> AddProperty("EFFICIENCY",p_mppc,effi_mppc,2);
  
  PhotonDetSurface -> SetMaterialPropertiesTable(PhotonDetSurfaceProperty);
  
  new G4LogicalSkinSurface("PhotonDetSurface",logicPhotonDet,PhotonDetSurface); 

  if (!mppcSD) {
     G4String mppcSDName = "WLS/PhotonDet";
     mppcSD = new WLSPhotonDetSD(mppcSDName);

     G4SDManager* SDman = G4SDManager::GetSDMpointer();
     SDman->AddNewDetector(mppcSD);
  }

  // Setting the detector to be sensitive
  logicPhotonDet->SetSensitiveDetector(mppcSD);
  //
  //-------------------------------------------------------------------------
  //
  //
  G4VisAttributes* calVisAttribute = new G4VisAttributes( 1, G4Colour( 0., 0., 0.7 ) );
  calVisAttribute->SetVisibility( true );
  calVisAttribute->SetForceWireframe( true );
  logicCalorimeter->SetVisAttributes(calVisAttribute);
  
  G4VisAttributes* cladVisAttribute = new G4VisAttributes( 1, G4Colour( 1, 1, 0 ) );
  cladVisAttribute->SetVisibility( true );
  cladVisAttribute->SetForceWireframe( true );
  logicClad2->SetVisAttributes(cladVisAttribute);
  /*
  G4VisAttributes* wlsVisAttribute = new G4VisAttributes( 1, G4Colour( 0.8, 0.8, 0.8 ) );
  wlsVisAttribute->SetVisibility( true );
  wlsVisAttribute->SetForceWireframe( true );
  logicWLSfiber->SetVisAttributes(wlsVisAttribute);
  */
  //
}



//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamDetectorConstruction::MaterialDefinition()
{
    ;
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

void EpamDetectorConstruction::SetVisualizationAttributes()
{
  ;
  /*
  // The World
  G4VisAttributes* worldVisAttribute = new G4VisAttributes( 1, G4Colour( 1, 1, 1 ) );
  worldVisAttribute->SetVisibility( false );
  worldVisAttribute->SetForceWireframe( false );
  logicWorld->SetVisAttributes(worldVisAttribute);

  // The Visible Light Shield
  G4VisAttributes* visibleLightShieldVisAttribute = new G4VisAttributes( 1, G4Colour( 0.2, 0.2, 0.2 ) ); // Gray
  visibleLightShieldVisAttribute->SetForceSolid(true);
  visibleLightShieldVisAttribute->SetVisibility( true );
  logicVisibleLightShieldFrontAl->SetVisAttributes( visibleLightShieldVisAttribute );
  logicVisibleLightShieldRearAl->SetVisAttributes( visibleLightShieldVisAttribute );
  visibleLightShieldVisAttribute->SetColour( 1.0, 1.0, 1.0 ); // White
  logicVisibleLightShieldFrontMylar->SetVisAttributes( visibleLightShieldVisAttribute );
  logicVisibleLightShieldRearMylar->SetVisAttributes( visibleLightShieldVisAttribute );

  
  // Collimator
  G4VisAttributes* opticalSurfaceVisAttribute = new G4VisAttributes( 1, G4Colour( 0.0, 0.3, 0.0 ) ); // Green
  opticalSurfaceVisAttribute->SetForceSolid(true);
  logicSurface->SetVisAttributes( opticalSurfaceVisAttribute );
  */
  
  /*
    G4VisAttributes* taCollimatorVisAttribute = new G4VisAttributes( 1, G4Colour( 0.0, 0.3, 0.0 ) ); // Darker Green
    taCollimatorVisAttribute->SetForceSolid(true);
    logicTaCollimator->SetVisAttributes( taCollimatorVisAttribute );
  */
  
  /*
    G4VisAttributes* opticalBottomSurfaceVisAttribute = new G4VisAttributes(1, G4Colour( 0.2, 0.2, 0.2) );
    opticalBottomSurfaceVisAttribute->SetForceSolid(true);
    logicBottomSurface->SetVisAttributes( opticalBottomSurfaceVisAttribute );

    // The Layers
    G4VisAttributes* layersVisAttributes = new G4VisAttributes( true );
    layersVisAttributes->SetForceSolid( true );
    layersVisAttributes->SetColour( 1.0, 0.0, 0.0 ); // Red
    logicLayerFirstFront->SetVisAttributes( layersVisAttributes );
    logicLayerSecondFront->SetVisAttributes( layersVisAttributes );
    //logicLayerFirstRear->SetVisAttributes( layersVisAttributes );
    logicLayerSecondRear->SetVisAttributes( layersVisAttributes );
  
    // The Calorimeter
    G4VisAttributes* calorimeterVisAttributes = new G4VisAttributes( 1, G4Colour( 0.0, 0.0, 0.7 ) ); // Light Blue
    calorimeterVisAttributes->SetForceSolid(true);
    logicCalorimeter->SetVisAttributes( calorimeterVisAttributes );

    // The Dead Areas
    G4VisAttributes* deadAreaVisAttributes = new G4VisAttributes( true );
    deadAreaVisAttributes->SetForceSolid( true );
    deadAreaVisAttributes->SetColour( 0.0, 1.0, 0.0 ); // Green
    logicLayerFirstFrontDeadAreaFront->SetVisAttributes( deadAreaVisAttributes );
    logicLayerFirstFrontDeadAreaRear->SetVisAttributes( deadAreaVisAttributes );
    //logicLayerFirstRearDeadAreaFront->SetVisAttributes( deadAreaVisAttributes );
    //logicLayerFirstRearDeadAreaRear->SetVisAttributes( deadAreaVisAttributes );
    logicLayerSecondFrontDeadAreaFront->SetVisAttributes( deadAreaVisAttributes );
    logicLayerSecondFrontDeadAreaRear->SetVisAttributes( deadAreaVisAttributes );
    logicLayerSecondRearDeadAreaFront->SetVisAttributes( deadAreaVisAttributes );
    logicLayerSecondRearDeadAreaRear->SetVisAttributes( deadAreaVisAttributes );

    // The Electrodes
    G4VisAttributes* electrodeVisAttributes = new G4VisAttributes( true );
    electrodeVisAttributes->SetForceSolid( true );
    electrodeVisAttributes->SetColour( 1.0, 1.0, 0.0 ); // Green
    logicLayerFirstFrontElectrodeFront->SetVisAttributes( electrodeVisAttributes );
    logicLayerFirstFrontElectrodeRear->SetVisAttributes( electrodeVisAttributes );
    //logicLayerFirstRearElectrodeFront->SetVisAttributes( electrodeVisAttributes );
    //logicLayerFirstRearElectrodeRear->SetVisAttributes( electrodeVisAttributes );
    logicLayerSecondFrontElectrodeFront->SetVisAttributes( electrodeVisAttributes );
    logicLayerSecondFrontElectrodeRear->SetVisAttributes( electrodeVisAttributes );
    logicLayerSecondRearElectrodeFront->SetVisAttributes( electrodeVisAttributes );
    logicLayerSecondRearElectrodeRear->SetVisAttributes( electrodeVisAttributes );
  */
}

void EpamDetectorConstruction::UpdateGeometry()
{
  if (!physiWorld) return;

  // clean-up previous geometry
  G4GeometryManager::GetInstance()->OpenGeometry();

  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  G4LogicalSkinSurface::CleanSurfaceTable();
  G4LogicalBorderSurface::CleanSurfaceTable();

  //define new one
  //UpdateGeometryParameters();
 
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());

  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4RunManager::GetRunManager()->PhysicsHasBeenModified();

  G4RegionStore::GetInstance()->UpdateMaterialList(physiWorld);
}

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
G4Material* EpamDetectorConstruction::FindMaterial(G4String name) {
  G4cout<<name<<G4endl;
  G4Material* material = G4Material::GetMaterial(name,true);
  //G4Material* material = WLSMaterials::GetMaterial(name);
  return material;
}
