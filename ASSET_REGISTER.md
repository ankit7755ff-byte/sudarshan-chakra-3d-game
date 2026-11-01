# ASSET REGISTER: SUDARSHAN

## Phase 02 Weapon Assets: Divine Sudarshan Chakra

### 3D Meshes & Geometry
- `SM_SudarshanChakra.obj` (`Content/Sudarshan/Meshes/SM_SudarshanChakra.obj`): High-poly 3D Sudarshan Chakra geometry (489 vertices, 611 polygonal face elements). Multi-tiered Vedic lotus hub, 8 radial connecting spokes, concentric bevelled golden ring, and 24 flame-curved 3D Katili razor blades.
- `SM_SudarshanChakra.mtl` (`Content/Sudarshan/Meshes/SM_SudarshanChakra.mtl`): Material library defining `M_SudarshanChakra_Gold`, `M_SudarshanChakra_Blades`, and `M_SudarshanChakra_Core`.

### PBR Materials & Shaders
- `M_SudarshanChakra_Gold.json` (`Content/Sudarshan/Materials/`): Vedic Sacred Gold PBR shader (BaseColor `#ffd700`, Metallic 0.95, Roughness 0.15, Specular 0.90, Emissive Gold Glow).
- `M_SudarshanChakra_Blades.json` (`Content/Sudarshan/Materials/`): High-specular tempered razor-sharp steel shader (Metallic 1.0, Roughness 0.08, Specular 0.99, Anisotropy 0.65).
- `M_SudarshanChakra_EnergyAura.json` (`Content/Sudarshan/Materials/`): Additive unlit translucent sacred sun aura with fresnel edge glow.

### Niagara Visual FX Systems
- `NS_ChakraDivineAura.json` (`Content/Sudarshan/Effects/`): Torus vortex particle emitter radiating golden solar flares and spinning light rays.
- `NS_ChakraBladeTrails.json` (`Content/Sudarshan/Effects/`): High-speed ribbon emitter generating 24 distinct trailing flame arcs from blade apexes.

### Audio Cues & Sound Systems
- `SC_Chakra_SpinLoop.json` (`Content/Sudarshan/Audio/`): Looping hypersonic metallic whir modulated dynamically by Current RPM (60 to 1800 RPM).
- `SC_Chakra_Throw.json` (`Content/Sudarshan/Audio/`): Supersonic blade slice and release whoosh (white noise burst + descending pitch sweep).
- `SC_Chakra_Charge.json` (`Content/Sudarshan/Audio/`): Divine harmonic resonance frequency swell for pre-launch aim lock.
- `SC_Chakra_Return.json` (`Content/Sudarshan/Audio/`): Resonant magnetic snap with harmonic conch chime.

### Unreal Engine 5 Actor & Blueprint Classes
- `ASudarshanChakraActor` (`Source/Sudarshan/Public/SudarshanChakraActor.h` & `Private/SudarshanChakraActor.cpp`): Production C++ Actor with 7 operating states, harmonic bobbing, precession tilt, supersonic flight trajectory, and magnetic recall.
- `BP_SudarshanChakra.json` (`Content/Sudarshan/Blueprints/`): Blueprint class hierarchy with pre-configured static mesh, Niagara components, point light, and audio attachments.

### Animation State Machine
- `Anim_SudarshanChakra_States.json` (`Content/Sudarshan/Animations/`): State configuration for IdleFloating (60 RPM), CeremonialSpin (180 RPM), CombatSpin (720 RPM), MahaStorm (1800 RPM), ThrowPreparation (960 RPM), Flying (1440 RPM), and Returning (1440 RPM).

### Verified Visual Rendered Screenshots
- `Chakra_Hero_3D.png` (`Content/Sudarshan/Screenshots/Chakra_Hero_3D.png`): 1280x720 cinematic hero render of the 3D Sudarshan Chakra weapon with PBR gold, 24 blades, and solar rim lighting.
- `Chakra_Blades_Detail.png` (`Content/Sudarshan/Screenshots/Chakra_Blades_Detail.png`): Close-up capture demonstrating blade geometry and bevelled serrations.
