from distutils.core import setup, Extension

module1 = Extension('algoengine',
                    sources = ['algoenginemodule.c'])

setup (name = 'AlgoEngine',
       version = '1.0',
       description = 'AlgoEngine package',
       ext_modules = [module1])
