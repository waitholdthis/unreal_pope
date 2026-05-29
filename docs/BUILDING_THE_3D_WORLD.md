# Building the 3D Defensive Training World

This project now includes C++ systems for a realistic-feeling but non-operational 3D airfield/base defensive simulation environment.

## Safety Model

The world is intentionally abstracted. It should evoke a large North Carolina airfield/base training environment without reproducing sensitive real-world base details, real facility placement, real vulnerabilities, or attack optimization.

## Core Actors

After rebuilding the project in Unreal, these classes are available in the Place Actors panel / C++ classes:

- `AZeusTrainingWorldActor` — procedural abstract airfield/base world generator.
- `AZeusDroneThreatActor` — generic drone threat actor with safe training movement patterns.
- `AZeusSensorVolume` — defensive detection volume.
- `AZeusProtectedZone` — generic protected training area marker.
- `AZeusScenarioManager` — starts/stops scenario and records detection events.

## First 3D Level Setup

1. Open the project through:

```bash
cd /Users/parkermacmini/unreal_pope
./Scripts/mac-open-editor.sh
```

2. In Unreal, create a new level:

```text
Content/Maps/L_TrainingAirfield_Abstract
```

3. Drag/place these actors into the level:

```text
AZeusTrainingWorldActor at location 0,0,0
AZeusScenarioManager at location 0,0,200
AZeusSensorVolume at location -1200,600,150
AZeusSensorVolume at location 2200,1600,150
AZeusProtectedZone at location 0,2200,20
AZeusDroneThreatActor at location -7800,-3600,850
```

4. Press Play.

5. In the Details panel or Blueprint, call `StartScenario` on the scenario manager to begin recording detection events.

## Visual World Tuning

`AZeusTrainingWorldActor` exposes editable properties:

- `WorldLength`
- `WorldWidth`
- `RunwayLength`
- `RunwayWidth`
- `HangarCount`
- `TreeLineCount`

Increase `TreeLineCount` for a denser perimeter. Increase `HangarCount` for a larger support area.

## Current Simulation Behavior

- The drone follows a generic safe training route.
- Sensors detect drones based on spherical radius.
- The scenario manager records first detection events.
- The world actor generates runway, taxiway, apron, generic buildings, sector markers, and perimeter tree lines.

## Next Milestone

Milestone 2 should add:

- UMG command-center HUD.
- Start/stop scenario buttons.
- Event timeline display.
- Sensor coverage material overlays.
- Blueprint data assets for drone/sensor profiles.
- Save/load scenario presets.
- Top-down tactical camera pawn.
