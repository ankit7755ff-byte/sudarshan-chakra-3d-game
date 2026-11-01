# ASSET REGISTER: SUDARSHAN (COMPLETE 12-PHASE INVENTORY)

## 1. Engine & Core Framework
- `Sudarshan.uproject`: Unreal Engine 5.3 project descriptor.
- `Source/Sudarshan/Sudarshan.Build.cs`: Module build definitions.
- `Source/Sudarshan/Public/Sudarshan.h` & `Private/Sudarshan.cpp`: Core primary game module.
- `Source/Sudarshan/Public/SudarshanGameModeBase.h` & `Private/SudarshanGameModeBase.cpp`: 1-hour Maha-Yuddha game mode.
- `Source/Sudarshan/Public/Core/SudarshanGameInstance.h` & `Private/Core/SudarshanGameInstance.cpp`: Scalability and platform manager.
- `Config/`: `DefaultEngine.ini`, `DefaultGame.ini`, `DefaultInput.ini`.

## 2. 3D Meshes & Geometry
- `SM_SudarshanChakra.obj` & `.mtl` (`Content/Sudarshan/Meshes/`): High-poly 3D Sudarshan Chakra geometry (489 vertices, 611 faces, 24 curved Katili blades, ॐ core, blue sapphires).
- `KurukshetraTerrain`: Ground plane with Dharma Mandala perimeter.
- `CelestialVaikunthaIslands`: Floating islands, golden Shikhara temple, and golden bridges.

## 3. PBR Materials & Shaders
- `M_SudarshanChakra_Gold.json`: Sacred Gold PBR shader (Metallic 0.95, Roughness 0.15).
- `M_SudarshanChakra_Blades.json`: Tempered steel razor edge shader (Metallic 1.0, Roughness 0.08).
- `M_SudarshanChakra_EnergyAura.json`: Additive unlit solar halo shader.

## 4. Visual Effects (Niagara Systems)
- `NS_ChakraDivineAura.json`: Torus vortex particle emitter.
- `NS_ChakraBladeTrails.json`: 24-blade trailing ribbon emitter.
- `NS_ChakraImpactSparks.json`: Impact cutting sparks burst.
- `PortalVortexFX`: Rotating sacred interdimensional vortex.

## 5. Audio Cues & Soundscapes
- `SC_Chakra_SpinLoop.json`, `SC_Chakra_Throw.json`, `SC_Chakra_Charge.json`, `SC_Chakra_Return.json`.
- `AVedicAudioManager`: Dynamic theme switcher (Flute, Damru, Shankh Naad).

## 6. Gameplay Actors & Components
- `ASudarshanChakraActor`: Production 3D weapon actor with 7 operating states.
- `ASudarshanCharacter`: Third-person player character with CameraBoom, FollowCamera, Walk, Sprint, Divine Dash.
- `USudarshanCombatComponent`: Aim reticle, supersonic throw, recall, 108 Blades shield, chain ricochet.
- `AAsuraBaseCharacter` & `AAsuraAIController`: Minion enemy AI with pursuit and venom spit.
- `AMahaKaliyaBoss` (2500 HP) & `AAghasuraBoss` (4000 HP): Multi-stage boss titans with Boss Health Bar.
- `APortalActor` & `ASudarshanWorldManager`: Dual explorable realms and portal warp.
- `AYamunaWaterBody`: Real-time wave and water purification dynamics.
- `USudarshanSaveGame` & `USudarshanHUDWidget`: Progression saving and Vedic HUD.

## 7. Visual Rendered Artifacts
- `Chakra_Hero_3D.png` & `Chakra_Blades_Detail.png` (1280x720).
- `Celestial_Realm_Vaikuntha.png` (1280x720).
- `index.html`: Playable real-time WebGL engine integrating all 12 phases with touch and PC controls.
