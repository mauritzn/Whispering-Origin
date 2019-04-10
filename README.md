# Whispering Origin


## Specifications

- 1280x720 (720p) non-scalable window.
- Striving for concurrent 60 frames per second.
- The player should always be centered on the screen (the world “moves” around the player).
- 32x32 grid-layout for the world.

A 2D top-down RPG game, with a tile-based world.


**[HP]:** High Priority **[MP]:** Medium Priority **[LP]:** Low Priority
**I:** Initiated **C:** Completed

---

## Features

- Map parsing _**[HP] C**_
- Code cleanup _**[HP]**_
- Fix everything into classes _**[HP] C**_
- Debug Mode _[HP] **C**_
- Player class _[HP] **C**_
- World movement _(“char movement”) [HP] **C**_
- Inventory System _[HP] **C**_
- Collision handling _[HP] **I**_
<br /><br />
- XP System _[MP] **C**_
- Progress bar and yield for tiles _[MP] **C**_
- Money system _[MP]_
<br /><br />
- Rudimentary Monster class _[LP]_
- Player & Monster Health Bar _[LP]_
- Dialog creation _[LP]_
- Multi-threading _[LP]_
- Installer _[LP]_
- Cross-platform support _[LP]_

<br />


## Skills *(max skill cap 20)*

- Woodcutting
- Mining
- Fishing
- Simple Cooking
- Smithing

<br />


## Skill mechanics

The skill’s level will tell you which tool you can use and which item “tier” you can “use”.

When cutting trees, mining ores or fishing the “spot”/”item” has a specific amount of resources available.

When killing monsters, monsters will have a set of items which can have a random chance of dropping.

When cooking, there will always be a chance of food getting burned *(perhaps)*.

When smithing, there can be a chance of failing doing said craft.

<br />


## Inventory system

- **Slots:** 12 item slots, 4 tool slots
- **Items stack:** yes
- **Max stack size:** 10

Stores items you get from resources like trees, ores, fishing spots and of course items that “drop” from monsters. Resource items stack, each stack can contain 10 items, after that a new stack is created. However weapons and tools do not stack.

<br />


## Polynomial Progression

The experience system will go after this formula: 
*(current level * 3) ^ 3*


That in return will mean that the system will go after a polynomial progress which is cubed, much similar to the system made with the old game Armada which had *(current level * 8) ^ 3*.

**Tested exp:** https://repl.it/@Dreameh/FastWhiteGnuassembler

<br />


## Items

### Ores *{{TYPE}} (resource amount)*

- Tin *(max: 3) [used with copper to make bronze]*
- Copper *(max: 3) [used with tin to make bronze]*
- Iron *(max: 2)*
- Coal *(max: 2) [used with iron to make steel]*


### Trees *{{TYPE}} (resource amount)*

- Oak *(max: 5)*
- Willow *(max: 4)*
- Maple *(max: 3)*


### Fish *{{TYPE}} (resource amount)*

- Salmon *(max: 3)*
- Cod *(max: 3)*


### Money

- Gold *(max: 2 Million)*

<br />


## Controls

WASD: Up, Left, Down, Right
E: Interaction (Talking to NPCs & Non-combat related matters)
Space: Attack
Left Shift: Block (To be investigated)
F4: Toggle Debug Mode
Esc: Toggle menu (or exit screen)