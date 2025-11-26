#!/usr/bin/env bash
set -euo pipefail
flag() {
	for f in "$@"; do
		[[ -e ".flags/$f" ]] || return 1
	done
}
mkdir -p dist
rm dist/*
for i in Debug Release; do
	mkdir -p build/Desktop-$i
done
if [[ -f "build/Desktop-Release/qt" ]]; then
	EXEC=Release
else
	EXEC=Debug
fi
E="dist/characters-${EXEC,,}"
cp build/Desktop-$EXEC/qt $E
if flag local; then
	./$E
fi