// Every .cc fine should include this file.

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

// EpamDetectorConstruction

// ** Using "Epam Sketch Ver. 0.0"

// -- The World and Core
#define WORLD_DIAM                                                  800          *mm

// -- The Visible Light Shield
#define VISIBLE_LIGHT_SHIELD_AL_THICKNESS                        15         *um
#define VISIBLE_LIGHT_SHIELD_MYLAR_THICKNESS                     0.0001          *um  
#define VISIBLE_LIGHT_SHIELD_DIAM                               11.670          *mm
#define VISIBLE_LIGHT_SHIELD_FRONT_CENTER_POSITION              300.000          *mm
#define VISIBLE_LIGHT_SHIELD_REAR_CENTER_POSITION              -300.000          *mm

// -- The Layers
#define LAYER_FIRST_THICKNESS                                     50           *um
#define LAYER_SECOND_THICKNESS                                     550          *um

#define LAYER_FIRST_DIAM                                            15          *mm
#define LAYER_SECOND_DIAM                                           20          *mm

#define LAYER_FIRST_FRONT_CENTER_POSITION                           280          *mm
#define LAYER_FIRST_REAR_CENTER_POSITION                           -280          *mm
#define LAYER_SECOND_FRONT_CENTER_POSITION                          250          *mm
#define LAYER_SECOND_REAR_CENTER_POSITION                          -250          *mm

// -- Dead Areas
#define DEAD_AREA_THICKNESS                                        0.5          *um

// -- Electrode
#define ELECTRODE_THICKNESS                                        0.5         *um

// -- Calorimeter
#define CALORIMETER_XY                                              25          *mm //25 *mm
#define CALORIMETER_Z                                               320         *mm
#define CALORIMETER_CENTER_POSITION                                  0          *mm

/*
// -- Collimator
#define FE_COLLIMATOR_INNER_DIAM_1                             23.1660          *mm
#define FE_COLLIMATOR_INNER_DIAM_2                             20.1610          *mm
#define FE_COLLIMATOR_INNER_DIAM_3                             13.8043          *mm
#define FE_COLLIMATOR_INNER_DIAM_4                             20.0000          *mm
#define FE_COLLIMATOR_INNER_DIAM_5                             20.0000          *mm
#define FE_COLLIMATOR_INNER_DIAM_6                             20.0000          *mm

#define FE_COLLIMATOR_OUTTER_DIAM_1                            23.1660          *mm
#define FE_COLLIMATOR_OUTTER_DIAM_2                            39.7610          *mm
#define FE_COLLIMATOR_OUTTER_DIAM_3                            33.4043          *mm
#define FE_COLLIMATOR_OUTTER_DIAM_4                            33.4043          *mm
#define FE_COLLIMATOR_OUTTER_DIAM_5                            30.0000          *mm
#define FE_COLLIMATOR_OUTTER_DIAM_6                            30.0000          *mm

#define FE_COLLIMATOR_PLANE_POSITION_1                               0          *mm
#define FE_COLLIMATOR_PLANE_POSITION_2                         3.53086          *mm
#define FE_COLLIMATOR_PLANE_POSITION_3                         11.0000          *mm
#define FE_COLLIMATOR_PLANE_POSITION_4                         11.0000          *mm
#define FE_COLLIMATOR_PLANE_POSITION_5                         15.0000          *mm
#define FE_COLLIMATOR_PLANE_POSITION_6                         15.0000          *mm

#define FE_COLLIMATOR_FRONT_POSITION                             -55.0          *mm
*/

#define TA_COLLIMATOR_INNER_DIAM_1                             25.10              *mm
#define TA_COLLIMATOR_INNER_DIAM_2                             25.10              *mm
#define TA_COLLIMATOR_OUTTER_DIAM_1                            25.20              *mm 
#define TA_COLLIMATOR_OUTTER_DIAM_2                            25.20              *mm
#define TA_COLLIMATOR_PLANE_POSITION_1                         0.0               *mm
#define TA_COLLIMATOR_PLANE_POSITION_2                         300.0             *mm

#define TA_COLLIMATOR_FRONT_POSITION                         -150.0             *mm


// -- Materials
#define VISIBLE_LIGHT_SHIELD_MATERIAL_NAME_AL                       "G4_Al"
#define VISIBLE_LIGHT_SHIELD_MATERIAL_NAME_MYLAR                    "G4_MYLAR"
#define LAYERS_MATERIALS_NAME                                       "G4_Si"
#define CALORIMETER_MATERIAL_NAME                                   "G4_PLASTIC_SC_VINYLTOLUENE"                        // "G4_CESIUM_IODIDE" // CsI
#define ELECTRODE_MATERIAL_NAME                                     "G4_Al"
#define OPTICAL_SURFACE_MATERIAL_NAME                               "G4_POLYETHYLENE"
/*
#define FE_COLLIMATOR_MATERIAL_NAME                                 "G4_Fe"
#define TA_COLLIMATOR_MATERIAL_NAME                                 "G4_Ta"
*/

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

// EpamPhysicsList

#define LOW_ENERGY_SECONDARY_PHOTON        100*eV

/*
#define FE_COLLIMATOR_CUT                  1*mm
#define TA_COLLIMATOR_CUT                  0.1*mm
*/

#define UNI_CUT 10*um
#define VISIBLE_LIGHT_SHIELD_CUT           0.1*um

#define LAYERS_CUT                         5*um
#define LAYER_FIRST_CUT                    LAYERS_CUT
#define LAYER_SECOND_CUT                   LAYERS_CUT

#define CALORIMETER_CUT                    1*mm

#define DEAD_AREA_CUT                      0.05*um
#define ELECTRODE_CUT                      0.05*um
#define SURFACE_CUT                0.05*um

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

// EpamPrimaryGeneratorAction

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

// Epam Eventaction

#define SILICON_LAYER_ELECTRONICS_NOISE          30*keV
#define SILICON_LAYER_RESOLOTION                 1.06/100

#define HIGH_ENERGY_SECONDARY_CONDITION          200*keV

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

/*
// EpamIdentifier
#define Z_SOLVE_PRECISION                         0.01
#define Z_SOLVE_STEPS_LIMIT                       1000
#define Z_SOLVE_START_VALUE                       1.0

#define SUCCESS_CODE_USING_FIRST_LAYER                               1
// Penetrated the first layer, and the first layer can be treated
// as a 'thin' layer. See also FIRST_LAYER_AS_THIN_CONDITION
#define SUCCESS_CODE_USING_FIRST_AND_SECOND_LAYER                    2
#define SUCCESS_CODE_USING_FIRST_SECOND_AND_THIRD_LAYER              3
#define SUCCESS_CODE_USING_ALL_SILICONG_DETECTORS                    4
#define FAILURE_CODE_STOPPED_IN_FIRST_LAYER                         -1
#define FAILURE_CODE_REACHED_ANTI_COINCIDENCE                       -2
#define FAILURE_CODE_TOO_LARGE_INCIDENT_ANGLE                       -3
#define FAILURE_CODE_MERELY_PASS_THROUGH_FIRST_LAYER                -4
#define FAILURE_CODE_OTHER_REASON                                   -5
#define FAILURE_CODE_REACHED_MAX_STEP_NUMBER                        -6
#define FAILURE_CODE_PASSED_FOURTH_SILICON_LAYER_EDGE               -7

#define FIRST_LAYER_ACTIVATE_THRESHOLD            (SILICON_LAYER_ELECTRONICS_NOISE * 3)
#define SECOND_LAYER_ACTIVATE_THRESHOLD           (SILICON_LAYER_ELECTRONICS_NOISE * 3)
#define THIRD_LAYER_ACTIVATE_THRESHOLD            (SILICON_LAYER_ELECTRONICS_NOISE * 3)
#define FOURTH_LAYER_ACTIVATE_THRESHOLD           (SILICON_LAYER_ELECTRONICS_NOISE * 3)
#define CALORIMETER_ACTIVATE_THRESHOLD            (300*keV)
#define ANTI_COINCIDENCE_ACTIVATE_THRESHOLD       (SILICON_LAYER_ELECTRONICS_NOISE * 2)

#define FIRST_LAYER_AS_THIN_CONDITION                          0.50
#define FIRST_AND_SECOND_LAYER_AS_THIN_CONDITION               0.50
#define FIRST_SECOND_AND_THIRD_LAYER_AS_THIN_CONDITION         0.25
#define ALL_SILICON_DETECTOR_AS_THIN_CONDITION                 0.25

#define FOURTH_LAYER_PASSING_EDGE_JUDGEMENT_ADJUST_COEFFICIENT 0.95
*/

//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....
//.....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.......oooOO0OOooo....

