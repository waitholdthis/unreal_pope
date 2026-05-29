# Unreal Pope Defensive Simulation Design

## Purpose

This project is a defensive training and planning simulation for counter-UAS awareness, base protection workflows, sensor coverage, and incident response rehearsal.

The simulation must not provide real-world attack planning guidance. It should avoid real vulnerability mapping, real restricted coordinates, real response procedures, or optimization of attack paths against an actual installation.

## Safety Boundaries

Allowed:

- Fictionalized or abstracted base layouts inspired by airfield/base geometry.
- Defensive training scenarios.
- Counter-UAS sensor placement and coverage visualization.
- Threat objects with generic behavior profiles.
- Tabletop-style response timing and alert workflows.
- After-action review metrics for detection, classification, and response.

Not allowed in this project:

- Real attack route optimization against Pope Army Airfield/Fort Bragg.
- Real target prioritization, asset vulnerability ranking, or bypass guidance.
- Real coordinates for sensitive facilities.
- Classified, controlled, or operational procedures.
- Guidance that improves hostile drone attack effectiveness.

## Product Vision

A UE 5.7 simulation sandbox where authorized users can place generic drone threat actors onto an abstracted map, run defensive scenarios, visualize detection/response timelines, and evaluate base-defense readiness in a non-operational training environment.

## Core User Modes

### Scenario Builder

Users create defensive tabletop scenarios:

- Place drone spawn zones.
- Place generic protected zones.
- Place sensor zones.
- Place response assets.
- Configure weather, visibility, time of day, and sensor degradation.
- Save/load scenario presets.

### Simulation Runtime

The simulation runs the scenario:

- Generic drone actors move using configurable behavior profiles.
- Sensor volumes detect, classify, and track drone actors.
- Alert events appear in the UI.
- Response timelines are tracked.
- Outcome metrics are recorded.

### After-Action Review

The tool presents defensive performance metrics:

- Time to first detection.
- Time to classification.
- Time to alert.
- Coverage gaps in abstract regions.
- False positives / false negatives.
- Response-zone overlaps.
- Scenario replay timeline.

## Map Strategy

Use an abstracted training map, not an exact operational digital twin.

Recommended implementation:

- Create `L_TrainingAirfield_Abstract`.
- Use broad shapes: runway, apron, roads, tree lines, generic buildings, perimeter zones.
- Do not include sensitive real facility details.
- Label areas generically: `Runway`, `Operations Zone`, `Maintenance Zone`, `Housing Edge`, `Perimeter Sector A/B/C`.

## Unreal Systems

### Core C++ Classes

- `AZeusSimulationGameMode`
- `AZeusScenarioManager`
- `AZeusDroneThreatActor`
- `UZeusDroneMovementComponent`
- `AZeusSensorVolume`
- `AZeusProtectedZone`
- `AZeusResponseAsset`
- `UZeusSimulationClockComponent`
- `UZeusScenarioSaveGame`
- `UZeusAfterActionReportSubsystem`

### Data Assets

- `UDroneThreatProfile`
- `USensorProfile`
- `UScenarioPreset`
- `UWeatherProfile`
- `UResponseAssetProfile`

### UI Widgets

- `WBP_ScenarioBuilderHUD`
- `WBP_PlacementPalette`
- `WBP_SimulationTimeline`
- `WBP_AlertFeed`
- `WBP_AfterActionReport`

## Drone Threat Model

Keep drone behavior generic and defensive-training oriented.

Example properties:

- Speed range.
- Altitude band.
- Visibility/noise signature.
- Battery duration.
- Navigation profile: direct, patrol, loiter, random, perimeter-follow.
- EW susceptibility.

Avoid:

- Real evasion tactics.
- Real route optimization.
- Real target selection logic.

## Sensor Model

Example sensor types:

- Visual observation zone.
- Radar-style detection zone.
- Acoustic zone.
- RF detection zone.
- EO/IR camera cone.

Sensor logic:

- Detection probability by range.
- Classification delay.
- Weather/time-of-day modifiers.
- Line-of-sight checks if appropriate.
- False-positive simulation.

## First Implementation Milestone

Milestone 1: Defensive Scenario Sandbox

1. Create an abstract training airfield level.
2. Add top-down/free camera mode.
3. Add placement mode for drone spawn points, sensor volumes, and protected zones.
4. Add generic drone actor with simple path-following.
5. Add sensor volume detection events.
6. Add alert feed UI.
7. Add after-action metrics for detection and response timing.

## Verification

A successful Milestone 1 demo should show:

- User places a drone spawn point.
- User places a sensor volume.
- User starts the simulation.
- Drone follows a generic route.
- Sensor detects drone when it enters coverage.
- UI displays an alert.
- After-action report shows detection time and event timeline.
