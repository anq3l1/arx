# ARX

**ARX** is a simple Linux package manager written in **C++**.

The project is currently in early development and is mainly created as a learning project to understand how Linux package managers work internally.

## Features

Currently ARX can:

* Download packages from URLs
* Read package information from `packages.json`
* Download files using **libcurl**
* Extract `.tar.gz` source archives
* Run `./configure`
* Build packages using `make`
* Work with package metadata stored in JSON

## How it works

When you run:

```bash
./apk install hello
```

APK performs the following steps:

```text
Package name
     ↓
packages.json
     ↓
Get package URL
     ↓
Download archive
     ↓
Extract archive
     ↓
./configure
     ↓
make
```

## Package Repository

Packages are currently described in `packages.json`.

Example:

```json
{
    "hello": {
        "name": "hello",
        "url": "https://ftp.gnu.org/gnu/hello/hello-2.12.3.tar.gz",
        "version": "2.12.3"
    }
}
```

The package manager reads the package name, version and download URL from this file.

## Project Structure

```text
apk/
├── include/
│   ├── configure.h
│   ├── install.h
│   └── json.h
│
├── src/
│   ├── main.cpp
│   ├── install.cpp
│   ├── configure.cpp
│   └── json.cpp
│
├── packages.json
├── LICENSE
└── README.md
```

## Requirements

APK currently requires:

* Linux
* C++ compiler with C++17 support
* libcurl
* nlohmann/json
* `tar`
* `make`
* Autoconf / `configure`

### Arch Linux

Install the required dependencies:

```bash
sudo pacman -S gcc curl nlohmann-json make
```

## Building

Clone the repository:

```bash
git clone https://github.com/anq3l1/apk.git
cd apk
```

Compile:

```bash
g++ src/*.cpp -Iinclude -lcurl -o arx
```

Run:

```bash
./arx install hello
```

## Example

```text
$ ./apk install hello

Download: hello...
Download complete!

Configurate...
...
Run: Make...
...
```

APK downloads the source archive, extracts it and runs the project's build process.

## Current Limitations

APK is still under development.

Currently:

* Package metadata is stored in a local `packages.json`
* Only basic package downloading is implemented
* The build system is mainly focused on Autoconf projects
* Dependency resolution is not implemented
* Package removal is not implemented
* Installed package tracking is not implemented
* Automatic updates are not implemented
* Security/signature verification is not implemented
* The installation stage is still under development

The project should therefore be considered **experimental**.

## Roadmap

* [ ] Better error handling
* [ ] Package installation
* [ ] Package removal
* [ ] Installed package database
* [ ] Dependency resolution
* [ ] Package search
* [ ] Package information
* [ ] Package updates
* [ ] Remote package repository
* [ ] CMake support
* [ ] Meson support
* [ ] Automatic build-system detection
* [ ] Package checksums
* [ ] Package signature verification
* [ ] Configuration files
* [ ] Better CLI interface

Planned commands:

```bash
apk install <package>
apk remove <package>
apk search <package>
apk info <package>
apk list
apk update
apk upgrade
```

## Why?

The goal of APK is not to replace existing package managers such as `pacman`, `apt` or `dnf`.

The project is being developed as a way to learn:

* C++
* Linux
* Linux internals
* Processes
* File systems
* HTTP
* JSON
* Software compilation
* Package management
* Build systems
* Unix/Linux architecture

## License

This project is licensed under the **GNU General Public License v3.0**.

See [`LICENSE`](LICENSE) for more information.

## Author

Created by **anq3l1**.

GitHub: [@anq3l1](https://github.com/anq3l1)
