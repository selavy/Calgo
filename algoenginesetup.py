from distutils.core import setup, Extension

module1 = Extension('algoengine',
                    sources = ['algoenginemodule.c', './engine/engine.c', './hash_table/hash/hash.c', './hash_table/hash_table.c', './queue/queue.c', './portfolio/portfolio.c', 'database/database.c'], include_dirs=['./include', './engine', './portfolio', './queue', './hash_table', './hash_table/hash', './database'])

setup (name = 'AlgoEngine',
       version = '1.0',
       description = 'AlgoEngine package',
       ext_modules = [module1])
