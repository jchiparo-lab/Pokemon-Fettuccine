#!/usr/bin/env python3
"""
Make a .bps patch that turns a clean Pokémon Emerald ROM into the built hack.

Run from the project root:
    python3 tools/fettuccine/make_bps.py CLEAN.gba pokeemerald.gba OUT.bps

Testers apply the patch to their own clean ROM with Rom Patcher JS or Flips,
so the hack can be shared without sharing Nintendo's game.

The patch is simple rather than small: wherever the built ROM still matches the
clean ROM at the same spot, it says "copy from the clean ROM", and everywhere
else it stores the new bytes. Zipping the patch shrinks it a lot. After writing
the patch, the script applies it to the clean ROM and checks that the result
matches the built ROM exactly, so a bad patch is never shipped.
"""

import re
import sys
import zlib

BLOCK = 16  # compare the two ROMs this many bytes at a time

SOURCE_READ, TARGET_READ, SOURCE_COPY, TARGET_COPY = range(4)


def write_number(out, n):
    while True:
        x = n & 0x7F
        n >>= 7
        if n == 0:
            out.append(0x80 | x)
            return
        out.append(x)
        n -= 1


def read_number(data, pos):
    n, shift = 0, 1
    while True:
        x = data[pos]
        pos += 1
        n += (x & 0x7F) * shift
        if x & 0x80:
            return n, pos
        shift <<= 7
        n += shift


def crc(data):
    return (zlib.crc32(data) & 0xFFFFFFFF).to_bytes(4, "little")


def add_run(runs, mode, start, end):
    if start >= end:
        return
    if runs and runs[-1][0] == mode and mode != TARGET_COPY and runs[-1][2] == start:
        runs[-1][2] = end
    else:
        runs.append([mode, start, end])


def add_compared_runs(runs, source, target, start, end):
    # Split a stretch into blocks that either match the source at the same
    # offset (SourceRead) or don't (TargetRead).
    for pos in range(start, end, BLOCK):
        block_end = min(pos + BLOCK, end)
        same = source[pos:block_end] == target[pos:block_end]
        add_run(runs, SOURCE_READ if same else TARGET_READ, pos, block_end)


def make_patch(source, target):
    runs = []
    pos = 0
    # Long runs of one repeated byte (empty filler space) are stored as one
    # new byte plus "repeat it", unless the clean ROM already has them there.
    for m in re.finditer(rb"(.)\1{63,}", target, re.S):
        add_compared_runs(runs, source, target, pos, m.start())
        if source[m.start():m.end()] == target[m.start():m.end()]:
            add_run(runs, SOURCE_READ, m.start(), m.end())
        else:
            add_run(runs, TARGET_READ, m.start(), m.start() + 1)
            add_run(runs, TARGET_COPY, m.start(), m.end())
        pos = m.end()
    add_compared_runs(runs, source, target, pos, len(target))

    out = bytearray(b"BPS1")
    write_number(out, len(source))
    write_number(out, len(target))
    write_number(out, 0)  # no metadata
    target_rel = 0
    for mode, start, end in runs:
        if mode == TARGET_COPY:
            # Copy the byte just before this run, over and over.
            write_number(out, ((end - start - 2) << 2) | mode)
            offset = start - target_rel
            write_number(out, (abs(offset) << 1) | (offset < 0))
            target_rel = start + (end - start - 1)
            continue
        write_number(out, ((end - start - 1) << 2) | mode)
        if mode == TARGET_READ:
            out += target[start:end]
    out += crc(source)
    out += crc(target)
    out += crc(out)
    return bytes(out)


def apply_patch(source, patch):
    if patch[:4] != b"BPS1" or crc(patch[:-4]) != patch[-4:]:
        raise ValueError("not a valid BPS patch")
    pos = 4
    source_size, pos = read_number(patch, pos)
    target_size, pos = read_number(patch, pos)
    metadata_size, pos = read_number(patch, pos)
    pos += metadata_size
    if source_size != len(source) or crc(source) != patch[-12:-8]:
        raise ValueError("patch is for a different source ROM")

    target = bytearray()
    source_rel = target_rel = 0
    end = len(patch) - 12
    while pos < end:
        data, pos = read_number(patch, pos)
        mode, length = data & 3, (data >> 2) + 1
        if mode == SOURCE_READ:
            start = len(target)
            target += source[start:start + length]
        elif mode == TARGET_READ:
            target += patch[pos:pos + length]
            pos += length
        else:
            offset, pos = read_number(patch, pos)
            offset = -(offset >> 1) if offset & 1 else offset >> 1
            if mode == SOURCE_COPY:
                source_rel += offset
                target += source[source_rel:source_rel + length]
                source_rel += length
            else:
                target_rel += offset
                for _ in range(length):
                    target.append(target[target_rel])
                    target_rel += 1

    if len(target) != target_size or crc(target) != patch[-8:-4]:
        raise ValueError("patched ROM doesn't match the expected result")
    return bytes(target)


def main():
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    clean_path, built_path, out_path = sys.argv[1:]
    with open(clean_path, "rb") as f:
        source = f.read()
    with open(built_path, "rb") as f:
        target = f.read()

    patch = make_patch(source, target)
    if apply_patch(source, patch) != target:
        sys.exit("error: the patch doesn't rebuild the ROM correctly")
    with open(out_path, "wb") as f:
        f.write(patch)
    print(f"wrote {out_path} ({len(patch) / 1_000_000:.1f} MB), verified OK")


if __name__ == "__main__":
    main()
