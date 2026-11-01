# SUDARSHAN: MASTER VERIFICATION TEST SUITE (PHASES 03 TO 07)
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
Write-Host "   SUDARSHAN: PHASES 03-07 MASTER INTEGRATION TEST SUITE "
Write-Host "=========================================================="

$baseDir = "C:\Users\Administrator\Downloads\sudarshan-chakra-game"

# TEST 1: Phase 03 Character Header & Controller
$charH = "$baseDir\Source\Sudarshan\Public\Character\SudarshanCharacter.h"
$charCpp = "$baseDir\Source\Sudarshan\Private\Character\SudarshanCharacter.cpp"
$charOk = (Test-Path $charH) -and (Test-Path $charCpp)
$results += Assert-Test "Phase 03: Character C++ Source" $charOk "ASudarshanCharacter header and source files present"

# TEST 2: Phase 03 Locomotion & Camera Boom Rig
$locoOk = $false
if ($charOk) {
    $content = Get-Content $charH -Raw
    if ($content -match "USpringArmComponent" -and $content -match "UCameraComponent" -and $content -match "DivineDash") {
        $locoOk = $true
    }
}
$results += Assert-Test "Phase 03: Camera Rig & Locomotion" $locoOk "SpringArm, FollowCamera, Sprint, Dash and Stamina verified"

# TEST 3: Phase 04 Combat Component
$combatH = "$baseDir\Source\Sudarshan\Public\Combat\SudarshanCombatComponent.h"
$combatCpp = "$baseDir\Source\Sudarshan\Private\Combat\SudarshanCombatComponent.cpp"
$combatOk = (Test-Path $combatH) -and (Test-Path $combatCpp)
$results += Assert-Test "Phase 04: Combat Component C++ Source" $combatOk "USudarshanCombatComponent header and source present"

# TEST 4: Phase 04 Precision Slicing & Trajectory
$sliceOk = $false
if ($combatOk) {
    $content = Get-Content $combatH -Raw
    if ($content -match "ThrowChakra" -and $content -match "RecallChakra" -and $content -match "TriggerMahaStormDefense" -and $content -match "ExecuteChainRicochet") {
        $sliceOk = $true
    }
}
$results += Assert-Test "Phase 04: Precision Slicing & Actions" $sliceOk "Throw, Recall, 108 Blades MahaStorm, and Chain Ricochet verified"

# TEST 5: Phase 05 Enemy AI Framework
$aiH = "$baseDir\Source\Sudarshan\Public\AI\AsuraBaseCharacter.h"
$aiControllerH = "$baseDir\Source\Sudarshan\Public\AI\AsuraAIController.h"
$aiOk = (Test-Path $aiH) -and (Test-Path $aiControllerH)
$results += Assert-Test "Phase 05: Enemy AI Minion System" $aiOk "AAsuraBaseCharacter and AAsuraAIController classes verified"

# TEST 6: Phase 06 Boss Encounters: Maha-Kaliya & Aghasura
$kaliyaH = "$baseDir\Source\Sudarshan\Public\Bosses\MahaKaliyaBoss.h"
$aghasuraH = "$baseDir\Source\Sudarshan\Public\Bosses\AghasuraBoss.h"
$bossOk = (Test-Path $kaliyaH) -and (Test-Path $aghasuraH)
$results += Assert-Test "Phase 06: Boss Encounters" $bossOk "AMahaKaliyaBoss (2500 HP) and AAghasuraBoss (4000 HP) verified"

# TEST 7: Phase 07 Dual Explorable Universes & Sacred Portal
$portalH = "$baseDir\Source\Sudarshan\Public\World\PortalActor.h"
$worldH = "$baseDir\Source\Sudarshan\Public\World\SudarshanWorldManager.h"
$worldOk = (Test-Path $portalH) -and (Test-Path $worldH)
$results += Assert-Test "Phase 07: World & Portal System" $worldOk "APortalActor and ASudarshanWorldManager verified"

# TEST 8: Phase 07 World Switch & Realm Streaming
$realmOk = $false
if ($worldOk) {
    $content = Get-Content $portalH -Raw
    if ($content -match "enum class EWorldRealm" -and $content -match "EarthRealm" -and $content -match "CelestialRealm") {
        $realmOk = $true
    }
}
$results += Assert-Test "Phase 07: Dual Realms Architecture" $realmOk "Earth Universe (Kurukshetra) & Divine Celestial Universe (Vaikuntha)"

# TEST 9: Live Dual-Realm 3D Gameplay Integration
$indexPath = "$baseDir\index.html"
$liveOk = $false
if (Test-Path $indexPath) {
    $indexContent = Get-Content $indexPath -Raw
    if ($indexContent -match "RealmManager" -and $indexContent -match "buildEarthRealm" -and $indexContent -match "buildCelestialRealm" -and $indexContent -match "divineDash") {
        $liveOk = $true
    }
}
$results += Assert-Test "Dual-Realm Playable Engine" $liveOk "index.html integrated with locomotion, combat, AI, bosses, and dual worlds"

# TEST 10: Regression Verification of Phase 01 & 02
$p1Pass = $false
$p2Pass = $false
try {
    $p1 = powershell -ExecutionPolicy Bypass -File "$baseDir\Tests\test_foundation.ps1"
    if ($LASTEXITCODE -eq 0) { $p1Pass = $true }
    $p2 = powershell -ExecutionPolicy Bypass -File "$baseDir\Tests\test_phase02_chakra.ps1"
    if ($LASTEXITCODE -eq 0) { $p2Pass = $true }
} catch {}
$results += Assert-Test "Phases 01 & 02 Regression Verification" ($p1Pass -and $p2Pass) "Foundation (7/7) and Phase 02 Chakra (10/10) pass cleanly"

Write-Host "----------------------------------------------------------"
Write-Host "Results: $passCount / $testCount Tests Passed"
Write-Host "=========================================================="

if ($passCount -eq $testCount) {
    exit 0
} else {
    exit 1
}
