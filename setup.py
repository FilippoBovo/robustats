import os

from distutils.core import setup, Extension
import numpy.distutils.misc_util


# C files
source_dir = "c"
source_files = ["_robustats.c", "robustats.c", "base.c"]
source_paths = [os.path.join(source_dir, file) for file in source_files]


setup(
    name = 'robustats',
    version = '0.1',
    description = 'Robust statistics',
    classifiers=[
        'Programming Language :: Python :: 3',
    ],
    url='https://github.com/FilippoBovo/robustats',
    author = 'Filippo Bovo',
    author_email = 'bovo.filippo@gmail.com',
    license='MIT',
    packages=['robustats'],
    install_requires=['numpy'],
    ext_modules=[
        Extension(
            name="_robustats",
            sources=source_paths
        )
    ],
    include_dirs=numpy.distutils.misc_util.get_numpy_include_dirs(),
)
