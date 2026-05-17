# KneeFlip Rehab

```text
          .-.
         /'v'\
        (/   \)
      ='="="=

     K N E E F L I P
       R E H A B
```

KneeFlip Rehab is a Flipper Zero external FAP app for following knee rehabilitation routines prescribed by a clinician.

It is a small timer and journaling tool: a place to start recovery timers, keep simple session notes, and eventually export plain CSV logs from the Flipper Zero microSD card.

> **Disclaimer:** KneeFlip Rehab is a timer and journaling tool only. It does not provide medical advice, diagnosis, or treatment. Always follow the recovery plan provided by your doctor, surgeon, or physical therapist.

## Current status

This repository currently contains the first working app build:

- `application.fam` app metadata
- main app entry point
- main menu
- About screen with the required disclaimer
- Ice and elevation timers with start, pause, resume, cancel, and completion states
- Quad sets hold/rest timer for clinician-prescribed routines
- Heel slides manual counter

Journaling inputs, CSV export, and history are planned next.

## Planned features

Implemented:

- Ice timer
- Elevation timer
- Quad sets timer
- Heel slides counter

Planned:

- Pain before/after input, 0-10
- Swelling input: none, mild, moderate, severe
- Manual range-of-motion input in degrees
- Session summary
- CSV export to microSD
- Recent session history

## Product boundaries

KneeFlip Rehab must stay neutral and user-directed:

- It does not suggest exercises.
- It does not prescribe timing, repetitions, or recovery plans.
- It does not diagnose, treat, prevent, or cure medical conditions.
- It only helps users follow and record routines already provided by a clinician.

If pain after a session is much higher than pain before, the app should only show this neutral reminder:

```text
Pain increased. Stop the session and follow your clinician's instructions.
```

## Building

This app is intended to build as an external Flipper Zero FAP with uFBT:

```sh
ufbt
```

## App menu

```text
KneeFlip Rehab

> Ice Timer
  Elevation
  Quad Sets
  Heel Slides
  Pain Log
  History
  About
```
