# POS CLI

## Introduction

**(P)oint (O)f (S)ale Accessories CLI** is a sell management on linux which
capability with old hardware allow low-end pc run soomthly

---

## Installation

### 1. Install dependencies

### (Arch Linux)

```bash
yay -S ncurses qrencode make git g++
git clone https://github.com/TinaGrim/POS_accessories_CLI.git
cd POS_accessories_CLI
```

### (Debian)

```bash
sudo apt update && sudo apt install libncurses-dev libqrencode-dev make git g++
git clone https://github.com/TinaGrim/POS_accessories_CLI.git
cd POS_accessories_CLI
```

### 2. Run Program

```bash
make run && make clean
```
