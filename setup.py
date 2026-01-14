from setuptools import Extension, setup
import numpy

# Minimal setup.py for C extensions only
# All metadata is in pyproject.toml
setup(
    ext_modules=[
        Extension(
            name="_robustats",
            sources=["c/_robustats.c", "c/robustats.c", "c/base.c"],
            extra_compile_args=["-std=c99"],
            include_dirs=[numpy.get_include()],
            define_macros=[("NPY_NO_DEPRECATED_API", "NPY_1_7_API_VERSION")],
        )
    ],
)
