check_dep = dependency('check')
json_dep = dependency('json-glib-1.0')

inc = include_directories('../anitomy')

testexe = executable('testexe', 'test.c',
                     include_directories : inc, 
                     link_with : anitomylib,
                     dependencies : [check_dep, json_dep])
test('Anitomy test', testexe)
