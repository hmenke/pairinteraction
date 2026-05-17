# SPDX-FileCopyrightText: 2026 PairInteraction Developers
# SPDX-License-Identifier: LGPL-3.0-or-later

from __future__ import annotations

import argparse
import os
import subprocess
import time
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description="Smoke test the frozen PairInteraction application.")
    parser.add_argument("executable", type=Path)
    parser.add_argument("--startup-seconds", type=float, default=8.0)
    parser.add_argument("--shutdown-seconds", type=float, default=10.0)
    args = parser.parse_args()

    env = os.environ.copy()
    env.setdefault("PAIRINTERACTION_TEST_MODE", "1")
    env.setdefault("QT_QPA_PLATFORM", "offscreen")

    process = subprocess.Popen(  # noqa: S603
        [str(args.executable)],
        env=env,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.PIPE,
        text=True,
    )

    time.sleep(args.startup_seconds)

    if process.poll() is not None:
        stderr = process.stderr.read() if process.stderr is not None else ""
        raise SystemExit(f"Frozen application exited too early with code {process.returncode}.\n{stderr}")

    process.terminate()
    try:
        process.wait(timeout=args.shutdown_seconds)
    except subprocess.TimeoutExpired:
        process.kill()
        process.wait(timeout=args.shutdown_seconds)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
