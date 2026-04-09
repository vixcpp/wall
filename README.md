# wall

Public real-time wall powered by Vix.cpp.

Post a message. See it appear instantly for everyone.

## What is this?

**wall** is a minimal production demo of Vix.cpp.

It is a live public page where anyone can:

* write a short message
* send a quick reaction ⚡
* see updates in real time

No account. No setup. Just open and test.

This project exists to answer one simple question:

> **How does Vix behave in production?**

## Live demo

Coming soon:

```
https://vixcpp.com/live
```

## Features

* Real-time messaging (WebSocket)
* Instant broadcast to all connected users
* Simple HTTP API
* Input validation (safe by default)
* Rate limiting (anti-spam)
* SQLite persistence (messages + stats)
* Presence tracking (connected users)
* Lightweight frontend (no framework)

## Stack

Built entirely with **Vix.cpp**:

* HTTP server
* WebSocket server
* JSON handling
* Validation
* Middleware
* Async runtime

No external frameworks.

## Project structure

```
wall/
├── config/        # runtime configuration
├── data/          # sqlite db + logs
├── include/       # headers
├── src/           # implementation
├── static/        # frontend (html/js/css)
├── scripts/       # dev + run scripts
├── tests/         # unit + integration
├── examples/      # usage demos
```

## Quick start

### 1. Clone

```bash
git clone https://github.com/vixcpp/wall.git
cd wall
```

### 2. Install dependencies

```bash
vix install
```

### 3. Run

```bash
vix run src/wall/main.cpp
```

## API

### Post message

```
POST /api/messages
```

```json
{
  "user": "gaspard",
  "text": "hello world"
}
```

### Get messages

```
GET /api/messages
```

### Stats

```
GET /api/stats
```

### WebSocket

```
ws://localhost:8080/ws
```

Events:

* `wall.message` → new message
* `wall.reaction` → reaction
* `wall.presence` → users count

## Rules

* username: 2–20 characters
* message: 1–160 characters
* rate limited per IP
* no authentication
* public and ephemeral

## Why this project?

Most demos are fake or too simple.

This one is different.

It runs:

* on a real VPS
* with real users
* with real traffic
* with real-time updates

If it works here, it works in production.

## Philosophy

Keep it simple.

* no unnecessary abstractions
* no framework overhead
* no hidden magic

Just a clean backend powered by Vix.cpp.

## License

MIT

## Author

Gaspard Kirira
Creator of Vix.cpp
Building the offline-first runtime for the real world

## Try it

When live:

> Open the page
> Write one message
> Watch it appear instantly everywhere

That’s Vix.cpp in production.
