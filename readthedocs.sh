#!/bin/bash
BUILD_DIR=build
DOCS_DIR=doc
DOCS_MAIN=html/index.html
BROWSER=xdg-open

if [ ! -d "$BUILD_DIR" ]; then
  echo "[*] Creating build folder"
  mkdir "$BUILD_DIR" && cd "$_"
  cmake .. && cd ..
fi

if [ ! -d "$BUILD_DIR/$DOCS_DIR/" ]; then
  echo "[*] Building docs"
  make doc
fi

if [ $# -gt 0 ]; then
  echo "[*] Opening doc with $1"
  BROWSER=$1
else
  echo "[*] Opening doc with default browser"
fi

echo file:$(pwd)/"$BUILD_DIR/$DOCS_DIR/$DOCS_MAIN"

$BROWSER "$(pwd)/$BUILD_DIR/$DOCS_DIR/$DOCS_MAIN" & disown

