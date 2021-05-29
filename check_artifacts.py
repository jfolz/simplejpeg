"""
Checks whether wheels for all supported Python versions and
all supported platforms were produced.
"""
import argparse
from pathlib import Path
import re
import itertools as it
import sys


PACKAGE_DIR = Path(__file__).parent.absolute()


def read(*names):
    with Path(PACKAGE_DIR, *names).open(encoding='utf8') as f:
        return f.read()


# pip's single-source version method as described here:
# https://python-packaging-user-guide.readthedocs.io/single_source_version/
def find_version(*file_paths):
    version_file = read(*file_paths)
    version_match = re.search(r'^__version__ = [\'"]([^\'"]*)[\'"]',
                              version_file, re.M)
    if version_match:
        return version_match.group(1)
    raise RuntimeError('Unable to find version string.')


def wheel_version_platforms(name):
    parts = name.stem.split('-')
    for tag in parts[-1].split('.'):
        yield parts[2], tag  # (python_version, platform)


def check_wheels(package, dist_dir, python_versions, platforms, exclude):
    exclude = set(tuple(ex.split('-')) for ex in exclude)
    wheels = set(it.chain.from_iterable(
        wheel_version_platforms(p)
        for p in dist_dir.glob(package + '*.whl')
    ))
    missing = []
    for combination in it.product(python_versions, platforms):
        if combination not in exclude and combination not in wheels:
            missing.append(combination)
    found = ', '.join('%s %s' % w for w in sorted(wheels))
    print('Found wheels:', found, flush=True)
    if missing:
        print('Error: Missing wheels:', ', '.join(map(str, missing)),
              file=sys.stderr, flush=True)
        sys.exit(1)


def check_source(package, dist_dir):
    source_archive = package + '.tar.gz'
    if (dist_dir / source_archive).is_file():
        print('Found source distribution', source_archive, flush=True)
    else:
        print('Error: Source distribution %s not found' % source_archive,
              file=sys.stderr, flush=True)
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
    parser.add_argument(
        '-e', '--exclude',
        nargs='+',
        help='Platform-tag combinations to exclude from check, '
             'e.g., cp39-manylinux1_x86_64'
    )

    args = parser.parse_args()
    package = 'simplejpeg-' + find_version('simplejpeg', '__init__.py')
    dist_dir = Path(args.distdir)
    print('Locating %s artifacts in %s' % (package, dist_dir))
    print('Python versions:', ', '.join(args.python_versions))
    print('Platforms:', ', '.join(args.platforms))
    print('Exclude:', ', '.join(args.exclude))
    check_wheels(package, dist_dir, args.python_versions, args.platforms, args.exclude)
    sys.stdout.flush()
    check_source(package, dist_dir)


if __name__ == '__main__':
    main()
