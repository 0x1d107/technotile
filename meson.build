project('technotile','cpp')
src = [
    'src/main.cpp',
    'src/World.cpp',
    'src/UI.cpp',
    'src/UIImage.cpp',
    'src/UIGrid.cpp',
    'src/Tile.cpp',
]
src+= ['src/json11/json11.cpp']
sdldep = dependency('SDL2')
imgdep = dependency('SDL2_image')
deps = [sdldep,imgdep]
executable('technotile',src,dependencies:deps)