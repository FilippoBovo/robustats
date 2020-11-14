from setuptools import Extension, setup

try:
    import numpy.distutils.misc_util
except ModuleNotFoundError:
    from setuptools import dist

    dist.Distribution().fetch_build_eggs(["numpy"])
    import numpy.distutils.misc_util


with open("README.md", "r") as f:
    long_description = f.read()


setup(
    name="robustats",
    version="0.1.6",
    description="Robustats is a Python library for high-performance computation" " of robust statistical estimators.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    classifiers=[
        "Programming Language :: Python :: 3",
    ],
    url="https://github.com/FilippoBovo/robustats",
    download_url="https://github.com/FilippoBovo/robustats/archive/" "v0.1.5.tar.gz",
    author="Filippo Bovo",
    author_email="bovo.filippo@gmail.com",
    license="MIT",
    packages=["robustats"],
    install_requires=["numpy"],
    ext_modules=[
        Extension(
            name="_robustats", sources=["c/_robustats.c", "c/robustats.c", "c/base.c"], extra_compile_args=["-std=c99"]
        )
    ],
    include_dirs=numpy.distutils.misc_util.get_numpy_include_dirs(),
)
