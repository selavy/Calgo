from distutils.core import setup, Extension

module1 = Extension('qsolve',
                    sources = ['qsolvemodule.c', './engine/engine.c', './hash_table/hash/hash.c', './hash_table/hash_table.c', './queue/queue.c', './portfolio/portfolio.c', 'database/database.c'], include_dirs=['./include', './engine', './portfolio', './queue', './hash_table', './hash_table/hash', './database'])

setup (name = 'QSolve',
       version = '1.0',
       description = 'QSolve Engine package',
       ext_modules = [module1])
