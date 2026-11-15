# Game Collection Tracker

An application for tracking games within a collection. Features include adding/removing games, modifying titles, searching for games, and listing all existing games.

## Build
```bash
cmake -B build
cmake --build build
```

## Usage

### Commands
 - `add <title>` Adds a game to the collection.
- `remove <title>` Removes a game from the collection.
- `modify <current-title>` **→ enter** `<new-title>` Replaces an existing game's title.  
- `search <title>` Lists fully and partially matching games, e.g. Wow matches both WoW and WoW classic.
- `list` : Lists all games in the collection.

### Rules
- `<title>`
  - Must contain only standard chars, including spaces
  - Must not contain newline characters
  - Must not exceed 100 characters
  - Must not contain only whitespace
  - Must not duplicate an existing title