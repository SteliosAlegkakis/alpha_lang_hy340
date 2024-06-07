## alpha_compiler_hy340
## Phase 4-5

## How to build
in the root folder: make all

## How to run
Compiler: ./alphac folder_name.asc (generates an a.abc binary file)
To generate the files quads.txt and instructions.txt: ./alphac -g folder_name.asc
Virtual machine: ./alphavm a.abc

## Problems
Number keys in tables don't get printed.
In some cases there are undefined arguments where they should not be (Maybe some mistakes with temps)
