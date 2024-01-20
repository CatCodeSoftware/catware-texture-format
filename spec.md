# CatWare Texture Format (CTF) Specification

- 3 bytes - “CTF” header
- 2 bytes - Major version
- 2 bytes - Minor version

Version 1.0 spec
- Uses little endian byte order

- Data
  - 2 bytes - width
  - 2 bytes - height
  - 1 byte - scaling method
    - 0 = Nearest
    - 1 = Linear
  - 1 byte - Wrap mode
    - 0 - Stretch
    - 1 - Tile
  - ? bytes - Image data in RGBA
