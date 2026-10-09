# DungeonEscape

Learning project for Unreal Engine 5.6 — a dungeon with doors, levers and locks, built
to practice C++ in UE: `ActorComponent`/`AActor`, `UCLASS`/`UPROPERTY`/`UFUNCTION`,
`BeginPlay`/`Tick`, overlaps and collision, and the C++ ↔ Blueprint workflow.

Based on the stock UE5 First Person template (`Source/DungeonEscape/`), with custom
classes and a level added on top (`Content/MyAssets/`).

## Custom code

`Source/DungeonEscape/Mover.h/.cpp` — an `ActorComponent` that moves its owning actor
(e.g. a door) between a start position and `StartLocation + MoveOffset`:

- `MoveOffset`, `MoveTime` — `EditAnywhere` properties for offset and travel time
- `BeginPlay()` stores the start location; `TickComponent()` drives toward the current
  target via `FMath::VInterpConstantTo`
- `GetShouldMove()`/`SetShouldMove()` — toggles the target between open and closed
  position (called externally, from `TriggerComponent`)

`Source/DungeonEscape/TriggerComponent.h/.cpp` — a `BoxComponent` trigger that
activates/deactivates an attached `Mover` based on a tag (`PressurePlateActivator`):

- `MoverActor` — reference to the actor holding the `Mover` component, resolved in
  `BeginPlay()`
- `IsPressurePlate` — enables the `OnComponentBeginOverlap`/`EndOverlap` subscription
  (pressure plate: step on it — triggered, step off — untriggered)
- `Trigger(bool)` — the common entry point, calls `Mover->SetShouldMove()`; invoked
  both from the plate's overlaps and directly from `ALock`

`Source/DungeonEscape/Lock.h/.cpp` — a lock (`AActor`): holds a `TriggerComponent` and
the matching key mesh (`KeyItemMesh`), compares `KeyItemName` against the player's
inventory on interact, and `SetIsKeyPlaced()` both shows the key on the model and
fires the trigger (opens the door/passage).

`Source/DungeonEscape/CollectableItem.h/.cpp` — a simple pickup (`AActor` tagged
`CollectableItem` with an `ItemName` field), destroyed on pickup and added to the
player's inventory.

`Source/DungeonEscape/DungeonEscapeCharacter.h/.cpp` — on top of the template
character, adds interaction: `Interact()` does a spherical sweep trace from the
camera (`MaxInteractDistance`, `InteractSphereRadius`), picks up a `CollectableItem`
into `ItemList`, or inserts a matching key into an `ALock`.

## Level

`Content/MyAssets/` — a test level (`TestLevel.umap`) with Blueprint wrappers on top
of the C++ classes: `BP_PressurePlate`, `BP_TestDoorLock`, `BP_LockStatueStand`,
`BP_GargoyleStatue`, `BP_GlassStatue`, `BP_MetalStatue`, `BP_SecretWall`, `BP_Player`.

## Tech notes

- Engine: UE 5.6 (engine installed at `D:\UE_5.6`, no `GenerateProjectFiles.bat` —
  `.vscode`/`.sln` are generated via
  `UnrealBuildTool.exe -mode=GenerateProjectFiles`)
- Git LFS for binary assets (`.uasset`, `.umap`, textures, audio, `.fbx`)
- Generated folders (`Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`) are
  gitignored

## Run

Open `DungeonEscape.uproject` in UE 5.6 (regenerate VS/VS Code project files if
needed).
