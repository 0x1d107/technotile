project('technotile','cpp',version:'0.0.1')
src = [
    'src/Entity.cpp',
    'src/main.cpp',
    'src/World.cpp',
    'src/UI.cpp',
    'src/UIImage.cpp',
    'src/UIText.cpp',
    'src/UIGrid.cpp',
    'src/Tile.cpp',
    'src/UIBlockSelector.cpp',
    'src/UITextArea.cpp',
    'src/Tiles.cpp'
    
]
src+= ['src/json11/json11.cpp']
sdldep = dependency('SDL2')
imgdep = dependency('SDL2_image')
ttfdep = dependency('SDL2_ttf')
deps = [sdldep,imgdep,ttfdep]
executable('technotile',src,dependencies:deps)