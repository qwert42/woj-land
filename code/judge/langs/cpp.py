from ._fundamental import def_compiled_lang
from .c import rf

rf.access = -1
rf.arch_prctl = -1


def_compiled_lang(id_=2,
                  canonical_name='C++',
                  code_name='cpp',
                  ext='cpp',
                  compile_cmd=['g++', '-o', '{target}', '{source}',
                               '-static', '-w', '-O2', '-DOJ'],
                  **rf)
