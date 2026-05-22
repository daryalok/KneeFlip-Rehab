# KneeFlip Rehab

```text
          .-.
         /'v'\
        (/   \)
        ='="="=     __
                   _|  |_
                  /______\

     K N E E F L I P
        R E H A B
```

KneeFlip Rehab is a Flipper Zero external FAP app for clinician-prescribed knee rehabilitation routines. It is a small timer and journaling tool for following timed sessions, pacing user-configured exercise blocks, logging pain and swelling, recording range-of-motion progress, and exporting recovery notes as CSV.

> **Safety disclaimer:** KneeFlip Rehab is a timer and journaling tool only. It does not provide medical advice, diagnosis, or treatment. Always follow the recovery plan provided by your doctor, surgeon, or physical therapist.

## Features

- Ice timer
- Elevation timer
- Quad sets timer for clinician-prescribed routines
- Heel slides manual counter
- Pain before/after log
- Swelling log
- Manual ROM input
- CSV export to microSD
- History screen
- Optional future GPIO sensor support

## App Screens

Implemented:

- Main menu
- Ice timer
- Elevation timer
- Quad sets timer
- Heel slides counter
- About screen with safety disclaimer

Planned:

- Pain before/after input
- Swelling input
- Manual ROM input
- Session summary
- CSV export
- Recovery history

Screenshot placeholders:

- `screenshots/main-menu.png`
- `screenshots/ice-timer.png`
- `screenshots/quad-sets.png`
- `screenshots/session-summary.png`
- `screenshots/about.png`

## Data Export

KneeFlip Rehab is planned to write append-only CSV logs to the Flipper Zero microSD card. The data format should stay plain, readable, and easy to copy into a note, spreadsheet, or message for a clinician.

Example CSV shape:

```csv
timestamp,session_type,pain_before,pain_after,swelling,rom_degrees,notes
2026-05-22T12:00:00Z,ice,3,3,mild,,completed timer
2026-05-22T12:30:00Z,quad_sets,2,3,mild,85,user-entered routine
```

If pain after a session is much higher than pain before, the app should only show this neutral reminder:

```text
Pain increased. Stop the session and follow your clinician's instructions.
```

## Installation

During development, build and install the FAP with uFBT:

```sh
ufbt launch
```

For manual installation, copy the built FAP from `dist/kneeflip_rehab.fap` to the Flipper Zero SD card under:

```text
/ext/apps/Tools/kneeflip_rehab.fap
```

After catalog approval, the app should be installable through Flipper Lab and the Flipper Mobile Apps.

## Build

Install uFBT, then run:

```sh
ufbt
```

Useful checks:

```sh
ufbt format
ufbt lint
ufbt
```

## Development Status

KneeFlip Rehab is an early prototype. Timer-based blocks are being implemented first, followed by journaling, CSV export, and recovery history.

Current version: `0.1.0`

## Roadmap

- Stabilize timer screens on hardware
- Add pain before/after input
- Add swelling input
- Add manual ROM input
- Add session summary
- Add append-only CSV export
- Add recent session history
- Capture official qFlipper screenshots
- Prepare Flipper Application Catalog PR
- Explore optional GPIO sensor support without automatic medical interpretation

## Safety Notes

- The app does not suggest exercises.
- The app does not prescribe timing, repetitions, or recovery plans.
- The app does not diagnose, treat, prevent, or cure medical conditions.
- Exercise labels are timers/counters for routines already provided by a clinician.
- Do not include private medical data in public bug reports, screenshots, logs, or pull requests.

## Catalog Submission

This repository contains the app source code and public project files. A best-effort catalog manifest draft lives at:

```text
docs/catalog/manifest.yml
```

Before opening a pull request to `flipperdevices/flipper-application-catalog`, replace the placeholder GitHub URL and commit SHA, capture official qFlipper screenshots, and validate the manifest in a local checkout of the catalog repository.

## License

MIT License. See [LICENSE](LICENSE).
