# Intent Extractor

## Cloning repo

Be sure to clone this repository with the following command due to submodules 

`git clone --recursive https://github.com/LOuFKg4TkPff7WovEL5djgcpHFnjVsJSay/intent-extractor.git`

## Building

This project requires CMake version >= 3.20. Older versions may work, but are not tested.

`cmake -G $GENERATOR_OF_CHOICE -S $PATH_TO_THIS_REPO -B $PATH_TO_BUILD_DIR`

`cmake --build $PATH_TO_BUILD_DIR`

## Running the cli utility

The cli binary will be available in your build directory under `$PATH_TO_BUILD_DIR/bin/intent_extractor`. The process 
will read from stdin/cin and reply to your queries as per instructions. E.g.:

```
How may I help you today?
> What is the weather Today?
Intent: Get Weather TimeDate:Today

How may I help you today?
> 
```