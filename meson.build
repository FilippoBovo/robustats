project('purelib-and-platlib', 'c', default_options: ['c_std=c99'])

py = import('python').find_installation(pure: false)

incdir_numpy = run_command(py,
  ['-c', 'import os; os.chdir(".."); import numpy; print(numpy.get_include())'],
  check : true
).stdout().strip()

inc_np = include_directories(incdir_numpy)

py.install_sources(['robustats/robustats.py', 'robustats/__init__.py'])

py.extension_module(
    '_robustats',
    ['c/_robustats.c', 
    'c/robustats.c', 
    'c/base.c'],
    install: true,
    include_directories: inc_np
)
