# copyright ################################# #
# This file is part of the Xfields Package.   #
# Copyright (c) CERN, 2021.                   #
# ########################################### #

from setuptools import setup, find_packages, Extension
from pathlib import Path

#######################################
# Prepare list of compiled extensions #
#######################################
gsl= Extension('gsl',
                    include_dirs=['/opt/homebrew/Cellar/gsl/2.7.1/include'],
                    libraries=['gsl', 'gslcblas'],
                    library_dirs=['/opt/homebrew/Cellar/gsl/2.7.1/lib'],
                    sources=['lumicalc.h', 'beambeam3d.h'])


extensions = [gsl]


#########
# Setup #
#########

version_file = Path(__file__).parent / 'xfieldsdev/_version.py'
dd = {}
with open(version_file.absolute(), 'r') as fp:
    exec(fp.read(), dd)
__version__ = dd['__version__']

setup(
    name='xfieldsdev',
    version=__version__,
    description='Field Maps and Particle In Cell',
    long_description=("Python package for the computation of fields generated "
                      "by particle ensembles in accelerators.\n\n"
                      "This package is part of the Xsuite collection."),
    url='https://xsuite.readthedocs.io/',
    packages=find_packages(),
    ext_modules = extensions,
    include_package_data=True,
    install_requires=[
        'numpy>=1.0',
        'scipy',
        'pandas',
        'xobjects>=0.0.4',
        'xtrack>=0.0.1',
        ],
    author='G. Iadarola et al.',
    license='Apache 2.0',
    download_url="https://pypi.python.org/pypi/xfieldsdev",
    project_urls={
            "Bug Tracker": "https://github.com/xsuite/xsuite/issues",
            "Documentation": 'https://xsuite.readthedocs.io/',
            "Source Code": "https://github.com/xsuite/xfieldsdev",
        },
    extras_require={
            'tests': ['pytest'],
        },
    )
