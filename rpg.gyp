{
  'conditions': 
  [
    [
      'OS=="linux"',
      {
        'make_global_settings': 
        [
          [ 'CXX', '/usr/bin/clang++' ],
          [ 'LINK', '/usr/bin/clang++' ],
        ]
      }
    ]
  ],
  'target_defaults':
  {
    'default_configuration': 'Debug',
    'configurations':
    {
      'Debug':
      {
        'defines':
        [
          'DEBUG'
        ],
        'conditions': 
        [
          [
            'OS=="linux"',
            {
              'cflags': [
                '-g',
                '-O0',
                '-fPIC',
                '-std=c++03',
                '-march=nocona'
              ]
            }     
          ]
        ]
      },
      'Release':
      {
        'defines':
        [
          'NDEBUG',
        ],
        'conditions': 
        [
          [
            'OS=="linux"',
            {
              'cflags': [
                '-funroll-loops',
                '-O3',
                '-Wall',
                '-fPIC',
                '-std=c++03',
                '-march=nocona'
              ]
            }     
          ]
        ]
      }
    }
  },
  'targets': 
  [
    {
      'target_name': 'engine',
      'type': 'shared_library',
      'defines': 
      [
      ],
      'dependencies':
      [
      ],
      'include_dirs':
      [
        './'
      ],
      'sources':
      [
        'engine/building.cc',
        'engine/camera.cc',
        'engine/character.cc',
        'engine/engine.cc',
        'engine/entity.cc',
        'engine/exception.cc',
        'engine/level.cc',
        'engine/lua.cc',
        'engine/object.cc',
        'engine/renderer.cc',
        'engine/shader.cc',
        'engine/world.cc'
      ],   
      'conditions': 
      [
        [
          'OS=="linux"',
          {
            'libraries':
            [
              '-lGLEW',
              '-llua',
              '-lpng'
            ]
          }
        ]
      ]
    },
    {
      'target_name': 'game',
      'type': 'executable',
      'defines':
      [
      ],
      'dependencies':
      [
        'engine'
      ],
      'include_dirs':
      [
        './'
      ],
      'sources':
      [
        'game/game.cc',
        'game/overworld.cc',
        'game/underworld.cc'
      ],    
      'conditions': 
      [
        [
          'OS=="linux"',
          {
            'libraries':
            [
              '-lglfw',
              '-lGLEW'
            ]
          }
        ]
      ]
    }
  ]  
}
