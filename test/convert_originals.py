import os
import os.path as pt
import itertools as it

from PIL import Image


ROOT = pt.abspath(pt.dirname(__file__))


def main():
    # images from https://homepages.cae.wisc.edu/~ece533/images/
    path = pt.join(ROOT, 'images', 'original')
    mode = 'RGB', 'L'
    quality = [50, 75, 95]
    optimize = True, False
    progressive = True, False
    subsampling = 0, 1, 2
    options = iter(it.product(mode, quality, optimize, progressive, subsampling))
    for f in os.listdir(path):
        m, q, o, p, s = next(options)
        im = Image.open(pt.join(path, f)).convert(m)
        im.save(pt.join(ROOT, 'images', pt.splitext(f)[0]+'.jpg'),
                quality=q, optimize=o, progressive=p, subsampling=s)


if __name__ == '__main__':
    main()
