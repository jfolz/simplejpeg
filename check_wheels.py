"""
Checks whether wheels for all supported Python versions and
all supported platforms were produced.
"""
import argparse
from pathlib import Path
import itertools as it
import sys


def version_platform(name):
    parts = name.stem.split('-')
    return parts[2], parts[4]  # (python_version, platform)


def check_wheels(dist_dir, python_versions, platforms):
    wheels = {version_platform(p) for p in dist_dir.glob('*.whl')}
    missing = []
    for combination in it.product(python_versions, platforms):
        if combination not in wheels:
            missing.append(combination)
    found = ', '.join('%s %s' % w for w in sorted(wheels))
    print('Found wheels:', found)
    if missing:
        print('Error: Missing wheels:', ', '.join(map(str, missing)),
              file=sys.stderr)
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        'distdir',
        help='Directory to check for wheels.'
    )
    parser.add_argument(
        '-v', '--python-versions',
        nargs='+',
        help='Supported Python versions.'
    )
    parser.add_argument(
        '-p', '--platforms',
        nargs='+',
        help='Supported platforms.'
    )

    args = parser.parse_args()
    check_wheels(Path(args.distdir), args.python_versions, args.platforms)


if __name__ == '__main__':
    main()
