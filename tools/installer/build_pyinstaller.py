# SPDX-FileCopyrightText: 2026 PairInteraction Developers
# SPDX-License-Identifier: LGPL-3.0-or-later

from __future__ import annotations

import sys
from pathlib import Path

import PyInstaller.__main__


def main() -> int:
    repo_root = Path(__file__).resolve().parents[2]
    build_root = repo_root / "build" / "installer"
    dist_root = repo_root / "dist" / "installer"
    spec_root = build_root / "spec"
    entrypoint = repo_root / "tools" / "installer" / "entrypoint.py"

    build_root.mkdir(parents=True, exist_ok=True)
    dist_root.mkdir(parents=True, exist_ok=True)
    spec_root.mkdir(parents=True, exist_ok=True)

    arguments = [
        "--noconfirm",
        "--clean",
        "--onedir",
        "--windowed",
        "--name",
        "PairInteraction",
        "--distpath",
        str(dist_root),
        "--workpath",
        str(build_root / "work"),
        "--specpath",
        str(spec_root),
        "--collect-all",
        "pairinteraction",
        "--collect-all",
        "pairinteraction_gui",
        "--collect-metadata",
        "pairinteraction",
        "--collect-metadata",
        "matplotlib",
        "--collect-metadata",
        "numpy",
        "--collect-metadata",
        "scipy",
        "--collect-metadata",
        "PySide6",
        "--hidden-import",
        "matplotlib.backends.backend_qt",
        "--hidden-import",
        "matplotlib.backends.backend_qtagg",
        str(entrypoint),
    ]

    if sys.platform == "darwin":
        arguments.extend(["--osx-bundle-identifier", "org.pairinteraction.PairInteraction"])

    PyInstaller.__main__.run(arguments)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
