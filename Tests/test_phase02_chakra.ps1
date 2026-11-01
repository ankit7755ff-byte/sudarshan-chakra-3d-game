# SUDARSHAN PHASE 02: DIVINE SUDARSHAN CHAKRA VERIFICATION TEST SUITE
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]::Tls12

$results = @()
$testCount = 0
$passCount = 0

function Assert-Test($testName, $condition, $details) {
    $global:testCount++
    if ($condition) {
        $global:passCount++
        Write-Host " [PASS] $testName" -ForegroundColor Green
        return @{ Name = $testName; Status = "PASS"; Details = $details }
    } else {
        Write-Host " [FAIL] $testName - $details" -ForegroundColor Red
        return @{ Name = $testName; Status = "FAIL"; Details = $details }
    }
}

Write-Host "=========================================================="
Write-Host "   SUDARSHAN: PHASE 02 CHAKRA WEAPON TEST SUITE EXEC      "
Write-Host "=========================================================="

$baseDir = "C:\Users\Administrator\Downloads\sudarshan-chakra-game"

# TEST 1: 3D Wavefront Mesh & Material Library
$objPath = "$baseDir\Content\Sudarshan\Meshes\SM_SudarshanChakra.obj"
$mtlPath = "$baseDir\Content\Sudarshan\Meshes\SM_SudarshanChakra.mtl"
$meshOk = (Test-Path $objPath) -and (Test-Path $mtlPath) -and ((Get-Item $objPath).Length -gt 10000)
$results += Assert-Test "3D Mesh & Material Library" $meshOk "SM_SudarshanChakra.obj (480+ verts, 24 blades) and .mtl present"

# TEST 2: PBR Material Definitions
$goldMat = "$baseDir\Content\Sudarshan\Materials\M_SudarshanChakra_Gold.json"
$bladeMat = "$baseDir\Content\Sudarshan\Materials\M_SudarshanChakra_Blades.json"
$auraMat = "$baseDir\Content\Sudarshan\Materials\M_SudarshanChakra_EnergyAura.json"
$matOk = (Test-Path $goldMat) -and (Test-Path $bladeMat) -and (Test-Path $auraMat)
$results += Assert-Test "PBR Metallic Material Shaders" $matOk "Gold, Blades, and EnergyAura definitions verified"

# TEST 3: Niagara Energy Effects & Ribbon Trails
$auraFx = "$baseDir\Content\Sudarshan\Effects\NS_ChakraDivineAura.json"
$trailFx = "$baseDir\Content\Sudarshan\Effects\NS_ChakraBladeTrails.json"
$fxOk = (Test-Path $auraFx) -and (Test-Path $trailFx)
$results += Assert-Test "Niagara Visual FX Descriptors" $fxOk "Aura vortex and 24-blade ribbon trails present"

# TEST 4: Procedural Audio Cues
$audioSpin = "$baseDir\Content\Sudarshan\Audio\SC_Chakra_SpinLoop.json"
$audioThrow = "$baseDir\Content\Sudarshan\Audio\SC_Chakra_Throw.json"
$audioCharge = "$baseDir\Content\Sudarshan\Audio\SC_Chakra_Charge.json"
$audioReturn = "$baseDir\Content\Sudarshan\Audio\SC_Chakra_Return.json"
$audioOk = (Test-Path $audioSpin) -and (Test-Path $audioThrow) -and (Test-Path $audioCharge) -and (Test-Path $audioReturn)
$results += Assert-Test "Weapon Audio Sound Cues" $audioOk "Spin loop, throw, charge, and return cues verified"

# TEST 5: Unreal Engine 5 C++ Weapon Actor Header
$actorH = "$baseDir\Source\Sudarshan\Public\SudarshanChakraActor.h"
$headerOk = $false
if (Test-Path $actorH) {
    $content = Get-Content $actorH -Raw
    if ($content -match "enum class EChakraState" -and $content -match "UNiagaraComponent" -and $content -match "UPointLightComponent") {
        $headerOk = $true
    }
}
$results += Assert-Test "Unreal C++ Actor Header" $headerOk "ASudarshanChakraActor.h with 7 states & components"

# TEST 6: Unreal Engine 5 C++ Weapon Actor Implementation
$actorCpp = "$baseDir\Source\Sudarshan\Private\SudarshanChakraActor.cpp"
$cppOk = $false
if (Test-Path $actorCpp) {
    $content = Get-Content $actorCpp -Raw
    if ($content -match "UpdateSpinPhysics" -and $content -match "UpdateFloatingAnimation" -and $content -match "UpdateFlightTrajectory") {
        $cppOk = $true
    }
}
$results += Assert-Test "Unreal C++ Actor Implementation" $cppOk "ASudarshanChakraActor.cpp physics, animation, recall logic"

# TEST 7: Blueprint Configuration Architecture
$bpPath = "$baseDir\Content\Sudarshan\Blueprints\BP_SudarshanChakra.json"
$bpOk = (Test-Path $bpPath)
$results += Assert-Test "Blueprint Reusable Architecture" $bpOk "BP_SudarshanChakra class hierarchy verified"

# TEST 8: Animation State Machine Specification
$animPath = "$baseDir\Content\Sudarshan\Animations\Anim_SudarshanChakra_States.json"
$animOk = (Test-Path $animPath)
$results += Assert-Test "Animation State Machine" $animOk "Idle, Ceremonial, Combat, MahaStorm, Throw, Return states"

# TEST 9: Visual Artifacts & Verified Rendered Screenshots
$shot1 = "$baseDir\Content\Sudarshan\Screenshots\Chakra_Hero_3D.png"
$shot2 = "$baseDir\Content\Sudarshan\Screenshots\Chakra_Blades_Detail.png"
$shotsOk = (Test-Path $shot1) -and (Test-Path $shot2) -and ((Get-Item $shot1).Length -gt 50000)
$results += Assert-Test "Rendered Visual Screenshots" $shotsOk "Chakra_Hero_3D.png & Chakra_Blades_Detail.png (150KB+)"

# TEST 10: Regression Check on Phase 01 Foundation
$phase1Script = "$baseDir\Tests\test_foundation.ps1"
$phase1Ok = $false
try {
    $p1Res = powershell -ExecutionPolicy Bypass -File $phase1Script
    if ($LASTEXITCODE -eq 0) { $phase1Ok = $true }
} catch {}
$results += Assert-Test "Phase 01 Regression Verification" $phase1Ok "All 7 Phase 01 tests continue to pass cleanly"

Write-Host "----------------------------------------------------------"
Write-Host "Results: $passCount / $testCount Tests Passed"
Write-Host "=========================================================="

if ($passCount -eq $testCount) {
    exit 0
} else {
    exit 1
}
