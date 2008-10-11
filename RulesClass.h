#ifndef RULES_H
#define RULES_H

/*
		HUGE thanks to DCoder
		for converting the property list!	*/

#include <ArrayClasses.h>
#include <GeneralDefinitions.h>

//forward declarations
class AircraftTypeClass;
class AnimTypeClass;
class BuildingTypeClass;
class BulletTypeClass;
class InfantryTypeClass;
class OverlayTypeClass;
class ParticleSystemTypeClass;
class SmudgeTypeClass;
class TerrainTypeClass;
class UnitTypeClass;
class VoxelAnimTypeClass;
class WarheadTypeClass;
class WeaponTypeClass;

struct SHPStruct;

//Difficulty
struct DifficultyStruct
{
	BYTE will_do_soon[0x50];
};

class RulesClass
{
public:
	//Static
	static RulesClass* Global()
		{ return *((RulesClass**)0x8871E0); }

	//CTOR / DTOR
protected:
	RulesClass() JMP_THIS(0x665650);
	~RulesClass() JMP_THIS(0x667A30);

	//Properties
	PROPERTY (int				, DetailMinFrameRateNormal);
	PROPERTY (int				, DetailMinFrameRateMovie);
	PROPERTY (int				, DetailBufferZoneWidth);
	PROPERTY (int				, AmmoCrateDamage);
	PROPERTY (UnitTypeClass*			, LargeVisceroid);
	PROPERTY (UnitTypeClass*			, SmallVisceroid);
	PROPERTY (int				, AttackingAircraftSightRange);
private: DWORD align_1C;
	PROPERTY (double			, TunnelSpeed);
	PROPERTY (double			, TiberiumHeal);
	PROPERTY (int				, SelfHealInfantryFrames);
	PROPERTY (int				, SelfHealInfantryAmount);
	PROPERTY (int				, SelfHealUnitFrames);
	PROPERTY (int				, SelfHealUnitAmount);
	PROPERTY (bool				, FreeMCV);
	PROPERTY (bool				, BerzerkAllowed);
	PROPERTY (int				, PoseDir);
	PROPERTY (int				, DeployDir);
	PROPERTY (AnimTypeClass*			, DropPodPuff);
	PROPERTY (int				, WaypointAnimationSpeed);
	PROPERTY (AnimTypeClass*			, BarrelExplode);
	PROPERTY_STRUCT (TypeList<VoxelAnimTypeClass*>	, BarrelDebris);
	PROPERTY (ParticleSystemTypeClass*		, BarrelParticle);
	PROPERTY (float				, RadarEventColorSpeed);
	PROPERTY (int				, RadarEventMinRadius);
	PROPERTY (float				, RadarEventSpeed);
	PROPERTY (float				, RadarEventRotationSpeed);
	PROPERTY (int				, FlashFrameTime);
	PROPERTY (int				, RadarCombatFlashTime);
	PROPERTY (int				, MaxWaypointPathLength);
	PROPERTY (AnimTypeClass*			, Wake);
	PROPERTY (AnimTypeClass*			, NukeTakeOff);
	PROPERTY (AnimTypeClass*			, InfantryExplode);
	PROPERTY (AnimTypeClass*			, FlamingInfantry);
	PROPERTY (AnimTypeClass*			, InfantryHeadPop);
	PROPERTY (AnimTypeClass*			, InfantryNuked);
	PROPERTY (AnimTypeClass*			, InfantryVirus);
	PROPERTY (AnimTypeClass*			, InfantryBrute);
	PROPERTY (AnimTypeClass*			, InfantryMutate);
	PROPERTY (AnimTypeClass*			, Behind);
private: DWORD align_BC;
	PROPERTY (double			, AITriggerSuccessWeightDelta);
	PROPERTY (double			, AITriggerFailureWeightDelta);
	PROPERTY (double			, AITriggerTrackRecordCoefficient);
	PROPERTY (int				, VeinholeMonsterStrength);
	PROPERTY (int				, MaxVeinholeGrowth);
	PROPERTY (int				, VeinholeGrowthRate);
	PROPERTY (int				, VeinholeShrinkRate);
	PROPERTY (AnimTypeClass*			, VeinAttack);
	PROPERTY (int				, VeinDamage);
	PROPERTY (int				, MaximumQueuedObjects);
	PROPERTY (int				, AircraftFogReveal);
	PROPERTY (OverlayTypeClass*			, WoodCrateImg);
	PROPERTY (OverlayTypeClass*			, CrateImg);
	PROPERTY (OverlayTypeClass*			, WaterCrateImg);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, DropPod);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, DeadBodies);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, MetallicDebris);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, BridgeExplosions);
	PROPERTY (int				, DigSound);
	PROPERTY (int				, CreateUnitSound);
	PROPERTY (int				, CreateInfantrySound);
	PROPERTY (int				, CreateAircraftSound);
	PROPERTY (int				, BaseUnderAttackSound);
	PROPERTY (int				, GUIMainButtonSound);
	PROPERTY (int				, GUIBuildSound);
	PROPERTY (int				, GUITabSound);
	PROPERTY (int				, GUIOpenSound);
	PROPERTY (int				, GUICloseSound);
	PROPERTY (int				, GUIMoveOutSound);
	PROPERTY (int				, GUIMoveInSound);
	PROPERTY (int				, GUIComboOpenSound);
	PROPERTY (int				, GUIComboCloseSound);
	PROPERTY (int				, GUICheckboxSound);
	PROPERTY (int				, ScoreAnimSound);
	PROPERTY (int				, IFVTransformSound);
	PROPERTY (int				, PsychicSensorDetectSound);
	PROPERTY (int				, BuildingGarrisonedSound);
	PROPERTY (int				, BuildingAbandonedSound);
	PROPERTY (int				, BuildingRepairedSound);
	PROPERTY (int				, CheerSound);
	PROPERTY (int				, PlaceBeaconSound);
	PROPERTY (int				, DefaultChronoSound);
	PROPERTY (int				, StartPlanningModeSound);
	PROPERTY (int				, AddPlanningModeCommandSound);
	PROPERTY (int				, ExecutePlanSound);
	PROPERTY (int				, EndPlanningModeSound);
	PROPERTY (int				, CrateMoneySound);
	PROPERTY (int				, CrateRevealSound);
	PROPERTY (int				, CrateFireSound);
	PROPERTY (int				, CrateArmourSound);
	PROPERTY (int				, CrateSpeedSound);
	PROPERTY (int				, CrateUnitSound);
	PROPERTY (int				, CratePromoteSound);
	PROPERTY (int				, ImpactWaterSound);
	PROPERTY (int				, ImpactLandSound);
	PROPERTY (int				, SinkingSound);
	PROPERTY (int				, BombTickingSound);
	PROPERTY (int				, BombAttachSound);
	PROPERTY (int				, YuriMindControlSound);
	PROPERTY (int				, ChronoInSound);
	PROPERTY (int				, ChronoOutSound);
	PROPERTY (int				, SpySatActivationSound);
	PROPERTY (int				, SpySatDeactivationSound);
	PROPERTY (int				, UpgradeVeteranSound);
	PROPERTY (int				, UpgradeEliteSound);
	PROPERTY (int				, VoiceIFVRepair);
	PROPERTY (int				, SlavesFreeSound);
	PROPERTY (int				, SlaveMinerDeploySound);
	PROPERTY (int				, SlaveMinerUndeploySound);
	PROPERTY (int				, BunkerWallsUpSound);
	PROPERTY (int				, BunkerWallsDownSound);
	PROPERTY (int				, RepairBridgeSound);
	PROPERTY (int				, PsychicDominatorActivateSound);
	PROPERTY (int				, GeneticMutatorActivateSound);
	PROPERTY (int				, PsychicRevealActivateSound);
	PROPERTY (int				, MasterMindOverloadDeathSound);
	PROPERTY (int				, AirstrikeAbortSound);
	PROPERTY (int				, AirstrikeAttackVoice);
	PROPERTY (int				, MindClearedSound);
	PROPERTY (int				, EnterGrinderSound);
	PROPERTY (int				, LeaveGrinderSound);
	PROPERTY (int				, EnterBioReactorSound);
	PROPERTY (int				, LeaveBioReactorSound);
	PROPERTY (int				, ActivateSound);
	PROPERTY (int				, DeactivateSound);
	PROPERTY (int				, SpyPlaneCamera);
	PROPERTY (int				, LetsDoTheTimeWarpOutAgain);
	PROPERTY (int				, LetsDoTheTimeWarpInAgain);
	PROPERTY (int				, DiskLaserChargeUp);
	PROPERTY (int				, SpyPlaneCameraFrames);
	PROPERTY (AnimTypeClass*			, Dig);
	PROPERTY (AnimTypeClass*			, IonBlast);
	PROPERTY (AnimTypeClass*			, IonBeam);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, DamageFireTypes);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, WeatherConClouds);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, WeatherConBolts);
	PROPERTY (AnimTypeClass*			, WeatherConBoltExplosion);
	PROPERTY (WarheadTypeClass*			, DominatorWarhead);
	PROPERTY (AnimTypeClass*			, DominatorFirstAnim);
	PROPERTY (AnimTypeClass*			, DominatorSecondAnim);
	PROPERTY (int				, DominatorFireAtPercentage);
	PROPERTY (int				, DominatorCaptureRange);
	PROPERTY (int				, DominatorDamage);
	PROPERTY (int				, MindControlAttackLineFrames);
	PROPERTY (int				, DrainMoneyFrameDelay);
	PROPERTY (int				, DrainMoneyAmount);
	PROPERTY (AnimTypeClass*			, DrainAnimationType);
	PROPERTY (AnimTypeClass*			, ControlledAnimationType);
	PROPERTY (AnimTypeClass*			, PermaControlledAnimationType);
	PROPERTY (AnimTypeClass*			, ChronoBlast);
	PROPERTY (AnimTypeClass*			, ChronoBlastDest);
	PROPERTY (AnimTypeClass*			, ChronoPlacement);
	PROPERTY (AnimTypeClass*			, ChronoBeam);
	PROPERTY (AnimTypeClass*			, WarpIn);
	PROPERTY (AnimTypeClass*			, WarpOut);
	PROPERTY (AnimTypeClass*			, WarpAway);
	PROPERTY (AnimTypeClass*			, ChronoSparkle1);
	PROPERTY (AnimTypeClass*			, IronCurtainInvokeAnim);
	PROPERTY (AnimTypeClass*			, ForceShieldInvokeAnim);
	PROPERTY (AnimTypeClass*			, WeaponNullifyAnim);
	PROPERTY (AnimTypeClass*			, AtmosphereEntry);
	PROPERTY_STRUCT (TypeList<int >		, PrerequisitePower);
	PROPERTY_STRUCT (TypeList<int >		, PrerequisiteFactory);
	PROPERTY_STRUCT (TypeList<int >		, PrerequisiteBarracks);
	PROPERTY_STRUCT (TypeList<int >		, PrerequisiteRadar);
	PROPERTY_STRUCT (TypeList<int >		, PrerequisiteTech);
	PROPERTY_STRUCT (TypeList<int >		, PrerequisiteProc);
	PROPERTY (UnitTypeClass*	, PrerequisiteProcAlternate);
	PROPERTY (int				, GateUp);
	PROPERTY (int				, GateDown);
	PROPERTY (int				, TurnRate);
	PROPERTY (int				, Speed);
private: DWORD align_414;
	PROPERTY (double			, Climb);
	PROPERTY (int				, CruiseHeight);
private: DWORD align_424;
	PROPERTY (double			, Acceleration);
	PROPERTY (double			, WobblesPerSecond);
	PROPERTY (int				, WobbleDeviation);
	PROPERTY_STRUCT (TypeList<int >		, RadarEventSuppressionDistances);
	PROPERTY_STRUCT (TypeList<int >		, RadarEventVisibilityDurations);
	PROPERTY_STRUCT (TypeList<int >		, RadarEventDurations);
	PROPERTY (int				, IonCannonDamage);
	PROPERTY (int				, RailgunDamageRadius);
	PROPERTY (BuildingTypeClass*		, PrismType);
	PROPERTY (float				, PrismSupportModifier);
	PROPERTY (int				, PrismSupportMax);
	PROPERTY (int				, PrismSupportDelay);
	PROPERTY (int				, PrismSupportDuration);
	PROPERTY (int				, PrismSupportHeight);
	PROPERTY (int				, V3RocketPauseFrames);
	PROPERTY (int				, V3RocketTiltFrames);
	PROPERTY (float				, V3RocketPitchInitial);
	PROPERTY (float				, V3RocketPitchFinal);
	PROPERTY (float				, V3RocketTurnRate);
	PROPERTY (float				, V3RocketRaiseRate);
	PROPERTY (float				, V3RocketAcceleration);
	PROPERTY (int				, V3RocketAltitude);
	PROPERTY (int				, V3RocketDamage);
	PROPERTY (int				, V3RocketEliteDamage);
	PROPERTY (int				, V3RocketBodyLength);
	PROPERTY (bool				, V3RocketLazyCurve);
	PROPERTY (AircraftTypeClass*		, V3RocketType);
	PROPERTY (int				, DMislPauseFrames);
	PROPERTY (int				, DMislTiltFrames);
	PROPERTY (float				, DMislPitchInitial);
	PROPERTY (float				, DMislPitchFinal);
	PROPERTY (float				, DMislTurnRate);
	PROPERTY (float				, DMislRaiseRate);
	PROPERTY (float				, DMislAcceleration);
	PROPERTY (int				, DMislAltitude);
	PROPERTY (int				, DMislDamage);
	PROPERTY (int				, DMislEliteDamage);
	PROPERTY (int				, DMislBodyLength);
	PROPERTY (bool				, DMislLazyCurve);
	PROPERTY (AircraftTypeClass*		, DMislType);
	PROPERTY (int				, CMislPauseFrames);
	PROPERTY (int				, CMislTiltFrames);
	PROPERTY (float				, CMislPitchInitial);
	PROPERTY (float				, CMislPitchFinal);
	PROPERTY (float				, CMislTurnRate);
	PROPERTY (float				, CMislRaiseRate);
	PROPERTY (float				, CMislAcceleration);
	PROPERTY (int				, CMislAltitude);
	PROPERTY (int				, CMislDamage);
	PROPERTY (int				, CMislEliteDamage);
	PROPERTY (int				, CMislBodyLength);
	PROPERTY (bool				, CMislLazyCurve);
	PROPERTY (AircraftTypeClass*		, CMislType);
	PROPERTY (int				, ParadropRadius);
	PROPERTY (double			, ZoomInFactor);
	PROPERTY (double			, ConditionRedSparkingProbability);
	PROPERTY (double			, ConditionYellowSparkingProbability);
	PROPERTY (int				, TiberiumExplosionDamage);
	PROPERTY (int				, TiberiumStrength);
	PROPERTY (float				, MinLowPowerProductionSpeed);
	PROPERTY (float				, MaxLowPowerProductionSpeed);
	PROPERTY (float				, LowPowerPenaltyModifier);
	PROPERTY (float				, MultipleFactory);
	PROPERTY (int				, MaximumCheerRate);
private: DWORD align_584;
	PROPERTY (double			, TreeFlammability);
	PROPERTY (double			, MissileSpeedVar);
	PROPERTY (double			, MissileROTVar);
	PROPERTY (int				, MissileSafetyAltitude);
	PROPERTY (WeaponTypeClass*			, DropPodWeapon);
	PROPERTY (int				, DropPodHeight);
	PROPERTY (int				, DropPodSpeed);
	PROPERTY (double			, DropPodAngle);
	PROPERTY (double			, ScrollMultiplier);
	PROPERTY (double			, CrewEscape);
	PROPERTY (int				, ShakeScreen);
	PROPERTY (int				, HoverHeight);
	PROPERTY (double			, HoverBob);
	PROPERTY (double			, HoverBoost);
	PROPERTY (double			, HoverAcceleration);
	PROPERTY (double			, HoverBrake);
	PROPERTY (double			, HoverDampen);
	PROPERTY (double			, PlacementDelay);
	PROPERTY_STRUCT (TypeList<VoxelAnimTypeClass*>	, ExplosiveVoxelDebris);
	PROPERTY (VoxelAnimTypeClass*		, TireVoxelDebris);
	PROPERTY (VoxelAnimTypeClass*		, ScrapVoxelDebris);
	PROPERTY (int				, BridgeVoxelMax);
	PROPERTY (int				, CloakingStages);
	PROPERTY (int				, RevealTriggerRadius);
	PROPERTY (double			, ShipSinkingWeight);
	PROPERTY (double			, IceCrackingWeight);
	PROPERTY (double			, IceBreakingWeight);
	PROPERTY_STRUCT (TypeList<int >		, IceCrackSounds);
	PROPERTY (byte				, CliffBackImpassability);
	PROPERTY (double			, VeteranRatio);
	PROPERTY (double			, VeteranCombat);
	PROPERTY (double			, VeteranSpeed);
	PROPERTY (double			, VeteranSight);
	PROPERTY (double			, VeteranArmor);
	PROPERTY (double			, VeteranROF);
	PROPERTY (double			, VeteranCap);
	PROPERTY (int				, CloakSound);
	PROPERTY (int				, SellSound);
	PROPERTY (int				, GameClosed);
	PROPERTY (int				, IncomingMessage);
	PROPERTY (int				, SystemError);
	PROPERTY (int				, OptionsChanged);
	PROPERTY (int				, GameForming);
	PROPERTY (int				, PlayerLeft);
	PROPERTY (int				, PlayerJoined);
	PROPERTY (int				, MessageCharTyped);
	PROPERTY (int				, Construction);
	PROPERTY_STRUCT (TypeList<int >		, CreditTicks);
	PROPERTY (int				, BuildingDieSound);
	PROPERTY (int				, BuildingSlam);
	PROPERTY (int				, RadarOn);
	PROPERTY (int				, RadarOff);
	PROPERTY (int				, MovieOn);
	PROPERTY (int				, MovieOff);
	PROPERTY (int				, ScoldSound);
	PROPERTY (int				, TeslaCharge);
	PROPERTY (int				, TeslaZap);
	PROPERTY (int				, GenericClick);
	PROPERTY (int				, GenericBeep);
	PROPERTY (int				, BuildingDamageSound);
	PROPERTY (int				, HealCrateSound);
	PROPERTY (int				, ChuteSound);
	PROPERTY (int				, StopSound);
	PROPERTY (int				, GuardSound);
	PROPERTY (int				, ScatterSound);
	PROPERTY (int				, DeploySound);		//TS leftover! Never read from the INI.
	PROPERTY (int				, StormSound);
	PROPERTY_STRUCT (TypeList<int >		, LightningSounds);
	PROPERTY (int				, ShellButtonSlideSound);
private: DWORD align_754;
	PROPERTY (double			, WallBuildSpeedCoefficient);
	PROPERTY (double			, ChargeToDrainRatio);
	PROPERTY (double			, TrackedUphill);
	PROPERTY (double			, TrackedDownhill);
	PROPERTY (double			, WheeledUphill);
	PROPERTY (double			, WheeledDownhill);
	PROPERTY (int				, SpotlightMovementRadius);
	PROPERTY (int				, SpotlightLocationRadius);
	PROPERTY (double			, SpotlightSpeed);
	PROPERTY (double			, SpotlightAcceleration);
	PROPERTY (double			, SpotlightAngle);
	PROPERTY (int				, SpotlightRadius);
	PROPERTY (int				, WindDirection);
	PROPERTY (int				, CameraRange);
	PROPERTY (int				, FlightLevel);
	PROPERTY (int				, ParachuteMaxFallRate);
	PROPERTY (int				, NoParachuteMaxFallRate);
	PROPERTY (int				, BuildingDrop);
	PROPERTY_STRUCT (TypeList<SmudgeTypeClass*>	, Scorches);
	PROPERTY_STRUCT (TypeList<SmudgeTypeClass*>	, Scorches1);
	PROPERTY_STRUCT (TypeList<SmudgeTypeClass*>	, Scorches2);
	PROPERTY_STRUCT (TypeList<SmudgeTypeClass*>	, Scorches3);
	PROPERTY_STRUCT (TypeList<SmudgeTypeClass*>	, Scorches4);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, RepairBay);
	PROPERTY (BuildingTypeClass*		, GDIGateOne);
	PROPERTY (BuildingTypeClass*		, GDIGateTwo);
	PROPERTY (BuildingTypeClass*		, NodGateOne);
	PROPERTY (BuildingTypeClass*		, NodGateTwo);
	PROPERTY (BuildingTypeClass*		, WallTower);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, Shipyard);
	PROPERTY (BuildingTypeClass*		, GDIPowerPlant);
	PROPERTY (BuildingTypeClass*		, NodRegularPower);
	PROPERTY (BuildingTypeClass*		, NodAdvancedPower);
	PROPERTY (BuildingTypeClass*		, ThirdPowerPlant);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildConst);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildPower);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildRefinery);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildBarracks);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildTech);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildWeapons);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, AlliedBaseDefenses);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, SovietBaseDefenses);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, ThirdBaseDefenses);
	PROPERTY_STRUCT (TypeList<int >		, AIForcePredictionFudge);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildDefense);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildPDefense);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildAA);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildHelipad);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildRadar);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, ConcreteWalls);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, NSGates);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, EWGates);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildNavalYard);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, BuildDummy);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, NeutralTechBuildings);
	PROPERTY (double			, GDIWallDefense);
	PROPERTY (double			, GDIWallDefenseCoefficient);
	PROPERTY (double			, NodBaseDefenseCoefficient);
	PROPERTY (double			, GDIBaseDefenseCoefficient);
	PROPERTY (int				, ComputerBaseDefenseResponse);
	PROPERTY (int				, MaximumBaseDefenseValue);
	PROPERTY_STRUCT (TypeList<UnitTypeClass*>		, BaseUnit);
	PROPERTY_STRUCT (TypeList<UnitTypeClass*>		, HarvesterUnit);
	PROPERTY_STRUCT (TypeList<AircraftTypeClass*>	, PadAircraft);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, OnFire);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, TreeFire);
	PROPERTY (AnimTypeClass*			, Smoke);
	PROPERTY (AnimTypeClass*			, Smoke_);	//exists twice
	PROPERTY (AnimTypeClass*			, MoveFlash);
	PROPERTY (AnimTypeClass*			, BombParachute);
	PROPERTY (AnimTypeClass*			, Parachute);
	PROPERTY_STRUCT (TypeList<AnimTypeClass*>		, SplashList);
	PROPERTY (AnimTypeClass*			, SmallFire);
	PROPERTY (AnimTypeClass*			, LargeFire);
	PROPERTY (InfantryTypeClass*		, Paratrooper);
	PROPERTY (int				, EliteFlashTimer);
	PROPERTY (int				, ChronoDelay);
	PROPERTY (int				, ChronoReinfDelay);
	PROPERTY (int				, ChronoDistanceFactor);
	PROPERTY (bool				, ChronoTrigger);
	PROPERTY (int				, ChronoMinimumDelay);
	PROPERTY (int				, ChronoRangeMinimum);
	PROPERTY_STRUCT (TypeList<InfantryTypeClass*>	, AmerParaDropInf);
	PROPERTY_STRUCT (TypeList<int >		, AmerParaDropNum);
	PROPERTY_STRUCT (TypeList<InfantryTypeClass*>	, AllyParaDropInf);
	PROPERTY_STRUCT (TypeList<int >		, AllyParaDropNum);
	PROPERTY_STRUCT (TypeList<InfantryTypeClass*>	, SovParaDropInf);
	PROPERTY_STRUCT (TypeList<int >		, SovParaDropNum);
	PROPERTY_STRUCT (TypeList<InfantryTypeClass*>	, YuriParaDropInf);
	PROPERTY_STRUCT (TypeList<int >		, YuriParaDropNum);
	PROPERTY_STRUCT (TypeList<InfantryTypeClass*>	, AnimToInfantry);
	PROPERTY_STRUCT (TypeList<InfantryTypeClass*>	, SecretInfantry);
	PROPERTY_STRUCT (TypeList<UnitTypeClass*>		, SecretUnits);
	PROPERTY_STRUCT (TypeList<BuildingTypeClass*>	, SecretBuildings);
	PROPERTY (int				, SecretSum);
	PROPERTY (InfantryTypeClass*		, AlliedDisguise);
	PROPERTY (InfantryTypeClass*		, SovietDisguise);
	PROPERTY (InfantryTypeClass*		, ThirdDisguise);
	PROPERTY (int				, SpyPowerBlackout);
	PROPERTY (float				, SpyMoneyStealPercent);
	PROPERTY (bool				, AttackCursorOnDisguise);
	PROPERTY (float				, AIMinorSuperReadyPercent);
	PROPERTY (int				, AISafeDistance);
	PROPERTY (int				, HarvesterTooFarDistance);
	PROPERTY (int				, ChronoHarvTooFarDistance);
	PROPERTY_STRUCT (TypeList<int >		, AlliedBaseDefenseCounts);
	PROPERTY_STRUCT (TypeList<int >		, SovietBaseDefenseCounts);
	PROPERTY_STRUCT (TypeList<int >		, ThirdBaseDefenseCounts);
	PROPERTY_STRUCT (TypeList<int >		, AIPickWallDefensePercent);
	PROPERTY (int				, AIRestrictReplaceTime);
	PROPERTY (int				, ThreatPerOccupant);
	PROPERTY (int				, ApproachTargetResetMultiplier);
	PROPERTY (int				, CampaignMoneyDeltaEasy);
	PROPERTY (int				, CampaignMoneyDeltaHard);
	PROPERTY (int				, GuardAreaTargetingDelay);
	PROPERTY (int				, NormalTargetingDelay);
	PROPERTY (int				, AINavalYardAdjacency);
	PROPERTY_STRUCT (TypeList<int >		, DisabledDisguiseDetectionPercent);
	PROPERTY_STRUCT (TypeList<int >		, AIAutoDeployFrameDelay);
	PROPERTY (int				, MaximumBuildingPlacementFailures);
	PROPERTY_STRUCT (TypeList<int >		, AICaptureNormal);
	PROPERTY_STRUCT (TypeList<int >		, AICaptureWounded);
	PROPERTY_STRUCT (TypeList<int >		, AICaptureLowPower);
	PROPERTY_STRUCT (TypeList<int >		, AICaptureLowMoney);
	PROPERTY (int				, AICaptureLowMoneyMark);
	PROPERTY (int				, AICaptureWoundedMark);
	PROPERTY_STRUCT (TypeList<int >		, AISuperDefenseProbability);
	PROPERTY (int				, AISuperDefenseFrames);
	PROPERTY (float				, AISuperDefenseDistance);
	PROPERTY_STRUCT (TypeList<int >		, OverloadCount);
	PROPERTY_STRUCT (TypeList<int >		, OverloadDamage);
	PROPERTY_STRUCT (TypeList<int >		, OverloadFrames);
	PROPERTY (float				, PurifierBonus);
	PROPERTY (float				, OccupyDamageMultiplier);
	PROPERTY (float				, OccupyROFMultiplier);
	PROPERTY (int				, OccupyWeaponRange);
	PROPERTY (int				, BunkerDamageMultiplier);
	PROPERTY (float				, BunkerROFMultiplier);
	PROPERTY (int				, BunkerWeaponRangeBonus);
	PROPERTY (float				, OpenToppedDamageMultiplier);
	PROPERTY (int				, OpenToppedRangeBonus);
	PROPERTY (int				, OpenToppedWarpDistance);
	PROPERTY (float				, FallingDamageMultiplier);
	PROPERTY (bool				, CurrentStrengthDamage);
	PROPERTY (InfantryTypeClass*		, Technician);
	PROPERTY (InfantryTypeClass*		, Engineer);
	PROPERTY (InfantryTypeClass*		, Pilot);
	PROPERTY (InfantryTypeClass*		, AlliedCrew);
	PROPERTY (InfantryTypeClass*		, SovietCrew);
	PROPERTY (InfantryTypeClass*		, ThirdCrew);
	PROPERTY (WarheadTypeClass*			, FlameDamage);
	PROPERTY (WarheadTypeClass*			, FlameDamage2);
	PROPERTY (WarheadTypeClass*			, NukeWarhead);
	PROPERTY (BulletTypeClass*			, NukeProjectile);
	PROPERTY (BulletTypeClass*			, NukeDown);
	PROPERTY (WarheadTypeClass*			, MutateWarhead);
	PROPERTY (WarheadTypeClass*			, MutateExplosionWarhead);
	PROPERTY (WarheadTypeClass*			, EMPulseWarhead);
	PROPERTY (WarheadTypeClass*			, EMPulseProjectile);
	PROPERTY (WarheadTypeClass*			, C4Warhead);
	PROPERTY (WarheadTypeClass*			, CrushWarhead);
	PROPERTY (WarheadTypeClass*			, V3Warhead);
	PROPERTY (WarheadTypeClass*			, DMislWarhead);
	PROPERTY (WarheadTypeClass*			, V3EliteWarhead);
	PROPERTY (WarheadTypeClass*			, DMislEliteWarhead);
	PROPERTY (WarheadTypeClass*			, CMislWarhead);
	PROPERTY (WarheadTypeClass*			, CMislEliteWarhead);
	PROPERTY (WarheadTypeClass*			, IvanWarhead);
	PROPERTY (int				, IvanDamage);
	PROPERTY (int				, IvanTimedDelay);
	PROPERTY (bool				, CanDetonateTimeBomb);
	PROPERTY (bool				, CanDetonateDeathBomb);
	PROPERTY (int				, IvanIconFlickerRate);
	PROPERTY (WeaponTypeClass*			, DeathWeapon);
	PROPERTY (SHPStruct*				, BOMBCURS_SHP);
	PROPERTY (SHPStruct*				, CHRONOSK_SHP);
	PROPERTY (int				, IronCurtainDuration);
	PROPERTY (int				, PsychicRevealRadius);
	PROPERTY (WarheadTypeClass*			, IonCannonWarhead);
	PROPERTY (TerrainTypeClass*			, VeinholeTypeClass);
	PROPERTY_STRUCT (TypeList<TerrainTypeClass*>	, DefaultMirageDisguises);
	PROPERTY (int				, InfantryBlinkDisguiseTime);
	PROPERTY (ParticleSystemTypeClass*		, DefaultLargeGreySmokeSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultSmallGreySmokeSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultSparkSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultLargeRedSmokeSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultSmallRedSmokeSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultDebrisSmokeSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultFireStreamSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultTestParticleSystem);
	PROPERTY (ParticleSystemTypeClass*		, DefaultRepairParticleSystem);
private: DWORD align_103C;
	PROPERTY (double			, MyEffectivenessCoefficientDefault);
	PROPERTY (double			, TargetEffectivenessCoefficientDefault);
	PROPERTY (double			, TargetSpecialThreatCoefficientDefault);
	PROPERTY (double			, TargetStrengthCoefficientDefault);
	PROPERTY (double			, TargetDistanceCoefficientDefault);
	PROPERTY (double			, DumbMyEffectivenessCoefficient);
	PROPERTY (double			, DumbTargetEffectivenessCoefficient);
	PROPERTY (double			, DumbTargetSpecialThreatCoefficient);
	PROPERTY (double			, DumbTargetStrengthCoefficient);
	PROPERTY (double			, DumbTargetDistanceCoefficient);
	PROPERTY (double			, EnemyHouseThreatBonus);
	PROPERTY (double			, TurboBoost);
	PROPERTY (double			, AttackInterval);
	PROPERTY (double			, AttackDelay);
	PROPERTY (double			, PowerEmergency);
	PROPERTY (double			, AirstripRatio);
	PROPERTY (int				, AirstripLimit);
private: DWORD align_10C4;
	PROPERTY (double			, HelipadRatio);
	PROPERTY (int				, HelipadLimit);
private: DWORD align_10D4;
	PROPERTY (double			, TeslaRatio);
	PROPERTY (int				, TeslaLimit);
private: DWORD align_10E4;
	PROPERTY (double			, AARatio);
	PROPERTY (int				, AALimit);
private: DWORD align_10F4;
	PROPERTY (double			, DefenseRatio);
	PROPERTY (int				, DefenseLimit);
private: DWORD align_1104;
	PROPERTY (double			, WarRatio);
	PROPERTY (int				, WarLimit);
private: DWORD align_1114;
	PROPERTY (double			, BarracksRatio);
	PROPERTY (int				, BarracksLimit);
	PROPERTY (int				, RefineryLimit);
	PROPERTY (double			, RefineryRatio);
	PROPERTY (int				, BaseSizeAdd);
	PROPERTY (int				, PowerSurplus);
	PROPERTY (int				, InfantryReserve);
	PROPERTY (int				, InfantryBaseMult);
	PROPERTY (int				, SoloCrateMoney);
	PROPERTY (int				, TreeStrength);
	PROPERTY (UnitTypeClass*			, UnitCrateType);
private: DWORD align_114C;
	PROPERTY (double			, PatrolScan);
	PROPERTY_STRUCT (TypeList<int >		, TeamDelays);
	PROPERTY_STRUCT (TypeList<int >		, AIHateDelays);
	PROPERTY (int				, DissolveUnfilledTeamDelay);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonConYardValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonWarFactoryValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonPowerValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonTechCenterValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonEngineerValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonThiefValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonHarvesterValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonMCVValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonAPCValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonBaseDefenseValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonPlugValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonHelipadValue);
	PROPERTY_STRUCT (TypeList<int >		, AIIonCannonTempleValue);
	PROPERTY (int				, AIAlternateProductionCreditCutoff);
	PROPERTY_STRUCT (TypeList<int >		, MultiplayerAICM);
	PROPERTY_STRUCT (TypeList<int >		, AIVirtualPurifiers);
	PROPERTY_STRUCT (TypeList<int >		, AISlaveMinerNumber);
	PROPERTY_STRUCT (TypeList<int >		, HarvestersPerRefinery);
	PROPERTY_STRUCT (TypeList<int >		, AIExtraRefineries);
	PROPERTY_STRUCT (TypeList<int >		, MinimumAIDefensiveTeams);
	PROPERTY_STRUCT (TypeList<int >		, MaximumAIDefensiveTeams);
	PROPERTY_STRUCT (TypeList<int >		, TotalAITeamCap);
private: DWORD align_13E4;
	PROPERTY (double			, AIUseTurbineUpgradeProbability);
	PROPERTY_STRUCT (TypeList<int >		, FillEarliestTeamProbability);
private: DWORD align_140C;
	PROPERTY (double			, CloakDelay);
	PROPERTY (double			, GameSpeedBias);
	PROPERTY (double			, BaseBias);
	PROPERTY (double			, ExpSpread);
	PROPERTY (int				, FireSupress);
	PROPERTY (int				, MaxIQLevels);
	PROPERTY (int				, SuperWeapons);
	PROPERTY (int				, Production);
	PROPERTY (int				, GuardArea);
	PROPERTY (int				, RepairSell);
	PROPERTY (int				, AutoCrush);
	PROPERTY (int				, Scatter);
	PROPERTY (int				, ContentScan);
	PROPERTY (int				, Aircraft);
	PROPERTY (int				, Harvester);
	PROPERTY (int				, SellBack);
	PROPERTY (int				, AIBaseSpacing);
	PROPERTY (int				, SilverCrate);
	PROPERTY (int				, WoodCrate);
	PROPERTY (int				, WaterCrate);
	PROPERTY (int				, CrateMinimum);
	PROPERTY (int				, CrateMaximum);
	PROPERTY (int				, unknown_int_1478);	//defaults to 0x2000
	PROPERTY (AnimTypeClass*			, DropZoneAnim);
	PROPERTY (int				, MinMoney);
	PROPERTY (int				, Money);
	PROPERTY (int				, MaxMoney);
	PROPERTY (int				, MoneyIncrement);
	PROPERTY (int				, MinUnitCount);
	PROPERTY (int				, UnitCount);
	PROPERTY (int				, MaxUnitCount);
	PROPERTY (int				, TechLevel);
	PROPERTY (int				, GameSpeed);
	PROPERTY (int				, AIDifficultyStruct);
	PROPERTY (int				, AIPlayers);
	PROPERTY (bool				, BridgeDestruction);
	PROPERTY (bool				, ShadowGrow);
	PROPERTY (bool				, Shroud);
	PROPERTY (bool				, Bases);
	PROPERTY (bool				, TiberiumGrows);
	PROPERTY (bool				, Crates);
	PROPERTY (bool				, CaptureTheFlag);
	PROPERTY (bool				, HarvesterTruce);
	PROPERTY (bool				, MultiEngineer);
	PROPERTY (bool				, AlliesAllowed);
	PROPERTY (bool				, ShortGame);
	PROPERTY (bool				, FogOfWar);
	PROPERTY (bool				, MCVRedeploys);
	PROPERTY (bool				, SuperWeaponsAllowed);
	PROPERTY (bool				, BuildOffAlly);
	PROPERTY (bool				, AllyChangeAllowed);
	PROPERTY (int				, DropZoneRadius);
	PROPERTY (double			, MessageDelay);
	PROPERTY (double			, SavourDelay);
	PROPERTY (int				, Players);
private: DWORD align_14D4;
	PROPERTY (double			, BaseDefenseDelay);
	PROPERTY (int				, SuspendPriority);
private: DWORD align_14E4;
	PROPERTY (double			, SuspendDelay);
	PROPERTY (double			, SurvivorRate);
	PROPERTY (int				, AlliedSurvivorDivisor);
	PROPERTY (int				, SovietSurvivorDivisor);
	PROPERTY (int				, ThirdSurvivorDivisor);
private: DWORD align_1504;
	PROPERTY (double			, ReloadRate);
	PROPERTY (double			, AutocreateTime);
	PROPERTY (double			, BuildupTime);
	PROPERTY (int				, HarvesterLoadRate);
private: DWORD align_1524;
	PROPERTY (double			, HarvesterDumpRate);
	PROPERTY (int				, AtomDamage);
private: DWORD align_1534;
	PROPERTY_STRUCT (DifficultyStruct			, Easy);
	PROPERTY_STRUCT (DifficultyStruct			, Normal);
	PROPERTY_STRUCT (DifficultyStruct			, Difficult);
private: DWORD align_1628[4];
	PROPERTY (double			, GrowthRate);
	PROPERTY (double			, ShroudRate);
	PROPERTY (double			, FogRate);
	PROPERTY (double			, IceGrowthRate);
	PROPERTY (double			, VeinGrowthRate);
	PROPERTY (int				, IceSolidifyFrameTime);
private: DWORD align_1664;
	PROPERTY (double			, AmbientChangeRate);
	PROPERTY (double			, AmbientChangeStep);
	PROPERTY (double			, CrateRegen);
	PROPERTY (double			, TimerWarning);
	PROPERTY (int				, TiberiumTransmogrify);
private: DWORD align_168C;
	PROPERTY (double			, unknown_double_1690);	//2.6875
	PROPERTY (double			, unknown_double_1698);	//2.3125
	PROPERTY (double			, unknown_double_16A0);	//2.5625
	PROPERTY (double			, DamageDelay);
	PROPERTY (double			, SpeakDelay);
	PROPERTY (int				, Gravity);
	PROPERTY (int				, LeptonsPerSightIncrease);
	PROPERTY (int				, Incoming);
	PROPERTY (int				, MinDamage);
	PROPERTY (int				, MaxDamage);
	PROPERTY (int				, RepairStep);
	PROPERTY (double			, RepairPercent);
	PROPERTY (int				, IRepairStep);
private: DWORD align_16DC;
	PROPERTY (double			, RepairRate);
	PROPERTY (double			, URepairRate);
	PROPERTY (double			, IRepairRate);
	PROPERTY (double			, unknown_double_16F8);	//1.875
	PROPERTY (double			, ConditionYellow);
	PROPERTY (double			, ConditionRed);
	PROPERTY (double			, IdleActionFrequency);
	PROPERTY (int				, CloseEnough);
	PROPERTY (int				, Stray);
	PROPERTY (int				, RelaxedStray);
	PROPERTY (int				, GuardModeStray);
	PROPERTY (int				, Crush);
	PROPERTY (int				, CrateRadius);
	PROPERTY (int				, HomingScatter);
	PROPERTY (int				, BallisticScatter);
	PROPERTY (double			, RefundPercent);
	PROPERTY (int				, BridgeStrength);
private: DWORD align_1744;
	PROPERTY (double			, BuildSpeed);
	PROPERTY (double			, C4Delay);
	PROPERTY (int				, CreditReserve);
private: DWORD align_175C;
	PROPERTY (double			, PathDelay);
	PROPERTY (int				, BlockagePathDelay);
private: DWORD align_176C;
	PROPERTY (double			, MovieTime);
	PROPERTY (int				, TiberiumShortScan);
	PROPERTY (int				, TiberiumintScan);
	PROPERTY (int				, SlaveMinerShortScan);
	PROPERTY (int				, SlaveMinerSlaveScan);
	PROPERTY (int				, SlaveMinerintScan);
	PROPERTY (int				, SlaveMinerScanCorrection);
	PROPERTY (int				, SlaveMinerKickFrameDelay);
	PROPERTY (int				, LightningDeferment);
	PROPERTY (int				, LightningDamage);
	PROPERTY (int				, LightningStormDuration);
	PROPERTY (int				, LightningHitDelay);
	PROPERTY (int				, LightningScatterDelay);
	PROPERTY (int				, Lightningintpread);
	PROPERTY (int				, LightningSeparation);
	PROPERTY (bool				, LightningPrintText);
	PROPERTY (WarheadTypeClass*			, LightningWarhead);
	PROPERTY (int				, ForceShieldRadius);
	PROPERTY (int				, ForceShieldDuration);
	PROPERTY (int				, ForceShieldBlackoutDuration);
	PROPERTY (int				, ForceShieldPlayFadeSoundTime);
	PROPERTY (bool				, MutateExplosion);
	PROPERTY (int				, CollapseChance);
	PROPERTY (int				, WeedCapacity);
	PROPERTY (float				, ExtraUnitLight);
	PROPERTY (float				, ExtraInfantryLight);
	PROPERTY (float				, ExtraAircraftLight);
	PROPERTY (bool				, Paranoid);
	PROPERTY (bool				, CurleyShuffle);
	PROPERTY (bool				, BlendedFog);
	PROPERTY (bool				, CompEasyBonus);
	PROPERTY (bool				, FineDiffControl);
	PROPERTY (bool				, TiberiumExplosive);
	PROPERTY (bool				, EnemyHealth);
	PROPERTY (bool				, AllyReveal);
	PROPERTY (bool				, SeparateAircraft);
	PROPERTY (bool				, TreeTargeting);
	PROPERTY (bool				, NamedCivilians);
	PROPERTY (bool				, PlayerAutoCrush);
	PROPERTY (bool				, PlayerReturnFire);
	PROPERTY (bool				, PlayerScatter);
	PROPERTY (bool				, RevealByHeight);
	PROPERTY (bool				, AllowShroudedSubteranneanMoves);
	PROPERTY (bool				, ShroudGrow);
	PROPERTY (bool				, NodAIBuildsWalls);
	PROPERTY (bool				, AIBuildsWalls);
	PROPERTY (bool				, UseMinDefenseRule);
	PROPERTY (AnimTypeClass*			, EMPulseSparkles);
	PROPERTY (float				, EngineerCaptureLevel);
	PROPERTY (float				, EngineerCaptureLevel_);
	PROPERTY (float				, TalkBubbleTime);
	PROPERTY (int				, RadDurationMultiple);
	PROPERTY (int				, RadApplicationDelay);
	PROPERTY (int				, RadLevelMax);
	PROPERTY (int				, RadLevelDelay);
	PROPERTY (int				, RadLightDelay);
	PROPERTY (double			, RadLevelFactor);
	PROPERTY (double			, RadLightFactor);
	PROPERTY (double			, RadTintFactor);
	PROPERTY_STRUCT (ColorStruct				, RadColor);
	PROPERTY (WarheadTypeClass*			, RadSiteWarhead);
	PROPERTY (int				, ElevationIncrement);
private: DWORD align_183C;
	PROPERTY (double			, ElevationIncrementBonus);
	PROPERTY (double			, ElevationBonusCap);
	PROPERTY (bool				, AlliedWallTransparency);
private: DWORD align_1854;
	PROPERTY (double			, WallPenetratorThreshold);
	PROPERTY_STRUCT (ColorStruct				, LocalRadarColor);
	PROPERTY_STRUCT (ColorStruct				, LineTrailColorOverride);
	PROPERTY_STRUCT (ColorStruct				, ChronoBeamColor);
	PROPERTY_STRUCT (ColorStruct				, MagnaBeamColor);
	PROPERTY (int				, OreTwinkleChance);
	PROPERTY (AnimTypeClass*			, OreTwinkle);

	PROPERTY_STRUCT_ARRAY(ColorStruct, ColorAdd, 0x10);

	PROPERTY (int				, LaserTargetColor);
	PROPERTY (int				, IronCurtainColor);
	PROPERTY (int				, BerserkColor);
	PROPERTY (int				, ForceShieldColor);
	PROPERTY (float				, DirectRockingCoefficient);
	PROPERTY (float				, FallBackCoefficient);
};

#endif