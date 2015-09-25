check_dep = dependency('check')

inc = include_directories('../anitomy')

testexe = executable('testexe', 'test.c',
                     include_directories : inc, 
                     link_with : anitomylib,
                     dependencies : check_dep)
test('Anitomy test', testexe)
