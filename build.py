import os
import sys
import subprocess
from pathlib import Path

def run_clean():
    os.system('rmdir /s /q build')
    Path("build").mkdir(parents=True, exist_ok=True)

def run_cmake():
    Path("build").mkdir(parents=True, exist_ok=True)
    output = subprocess.check_output('python -m pybind11 --includes', shell=True, text=True)
    _, python_include, pybidn11_include = output.split('-I')
    pybidn11_include = pybidn11_include.strip('\n')
    python_lib = '%s\libs'%os.path.dirname(python_include)
    print('#### python_include: ', python_include)
    print('#### pybidn11_include: ', pybidn11_include)
    print('#### python_lib: ', python_lib)
    cmake_cmd  = 'cmake '
    cmake_cmd += '-DPYTHON_INCLUDE="%s" '%python_include
    cmake_cmd += '-DPYBIND11_INCLUDE="%s" '%pybidn11_include
    cmake_cmd += '-DPYTHON_LIB="%s" '%python_lib
    cmake_cmd += '..\src '
    print('#### cmake_cmd: ', cmake_cmd)
    os.system('cd build && %s'%cmake_cmd)

def run_vsbuild():
    os.system('cd build && msbuild pydxva.sln')

if __name__ == '__main__':
    if len(sys.argv)>1:
        if sys.argv[1] == 'clean':
            run_clean()
        elif sys.argv[1] == 'gen':
            run_cmake()
        elif sys.argv[1] == 'all':
            run_cmake()
            run_vsbuild()
    else:
        run_vsbuild()
    print('done')