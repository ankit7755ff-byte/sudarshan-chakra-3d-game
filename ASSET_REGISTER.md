# ASSET REGISTER: SUDARSHAN (PHASES 01 TO 07)

## Registered Assets

### Phase 01: Foundation
- `Sudarshan.uproject`: UE 5.3 project descriptor with EnhancedInput & Niagara.
- `Source/Sudarshan/Sudarshan.Build.cs`: Module build definitions.
- `Source/Sudarshan/Public/SudarshanGameModeBase.h` & `Private/SudarshanGameModeBase.cpp`: 1-hour Maha-Yuddha rules.
- `Config/`: `DefaultEngine.ini`, `DefaultGame.ini`, `DefaultInput.ini`.

### Phase 02: Divine Sudarshan Chakra
- `SM_SudarshanChakra.obj` & `.mtl` (`Content/Sudarshan/Meshes/`): 3D geometry with 24 curved Katili blades, Om core, blue sapphires.
- `M_SudarshanChakra_Gold.json`, `M_SudarshanChakra_Blades.json`, `M_SudarshanChakra_EnergyAura.json` (`Content/Sudarshan/Materials/`).
- `NS_ChakraDivineAura.json`, `NS_ChakraBladeTrails.json` (`Content/Sudarshan/Effects/`).
- `SC_Chakra_SpinLoop.json`, `SC_Chakra_Throw.json`, `SC_Chakra_Charge.json`, `SC_Chakra_Return.json` (`Content/Sudarshan/Audio/`).
- `ASudarshanChakraActor` (`Source/Sudarshan/Public/SudarshanChakraActor.h` & `.cpp`).
- `BP_SudarshanChakra.json` & `Anim_SudarshanChakra_States.json`.

### Phase 03: Character Controller & Divine Locomotion
- `ASudarshanCharacter` (`Source/Sudarshan/Public/Character/SudarshanCharacter.h` & `.cpp`): Third-person rig, CameraBoom (450cm), FollowCamera, Walk (600), Sprint (1100), Divine Dash (2600), Stamina system, `ChakraFingerSocket_R`.

### Phase 04: Advanced Combat & Precision Slicing
- `USudarshanCombatComponent` (`Source/Sudarshan/Public/Combat/SudarshanCombatComponent.h` & `.cpp`): Crosshair aim raycast, supersonic throw, magnetic parabolic recall, 108 Blades MahaStorm shield, chain ricochet slicing.

### Phase 05: Enemy AI Minions
- `AAsuraBaseCharacter` (`Source/Sudarshan/Public/AI/AsuraBaseCharacter.h` & `.cpp`): Kaliya Serpents, horned Asuras, pursuit AI, venom spit, dissolution FX.
- `AAsuraAIController` (`Source/Sudarshan/Public/AI/AsuraAIController.h` & `.cpp`).

### Phase 06: Boss Encounters
- `AMahaKaliyaBoss` (`Source/Sudarshan/Public/Bosses/MahaKaliyaBoss.h` & `.cpp`): 5-headed serpent titan (2500 HP), toxic nova, tail sweep, enrage trigger at 50% HP.
- `AAghasuraBoss` (`Source/Sudarshan/Public/Bosses/AghasuraBoss.h` & `.cpp`): Cavernous python titan (4000 HP), earth tremor stomp.

### Phase 07: Divine Universe & Dual Realms
- `APortalActor` (`Source/Sudarshan/Public/World/PortalActor.h` & `.cpp`): Rotating torus gateway, vortex FX, overlap teleportation.
- `ASudarshanWorldManager` (`Source/Sudarshan/Public/World/SudarshanWorldManager.h` & `.cpp`): Earth Universe (Kurukshetra) & Celestial Universe (Vaikuntha) streaming.
- `Celestial_Realm_Vaikuntha.png` (`Content/Sudarshan/Screenshots/`): 1280x720 capture of floating islands, golden temple, portal, and boss.
- `index.html`: Fully playable real-time WebGL engine integrating all 7 phases with touch & PC controls.
