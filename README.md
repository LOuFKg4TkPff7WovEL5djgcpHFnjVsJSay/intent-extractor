# Intent Extractor

## Build Instructions

### Dependencies
* C++ compiler with C++17 standard support
* CMake >= 3.20

**Note:** This project was tested on GCC 11.1 on Arch Linux. It should work with older version that also support the
C++17 standard. Windows is not tested, but should work fine with Visual Studio 2019.

### Cloning repo

Be sure to clone this repository with the following command due to submodules 

`git clone --recursive https://github.com/LOuFKg4TkPff7WovEL5djgcpHFnjVsJSay/intent-extractor.git`

### Building

This project requires CMake version >= 3.20. Older versions may work, but are not tested.

`cmake -G $GENERATOR_OF_CHOICE -S $PATH_TO_THIS_REPO -B $PATH_TO_BUILD_DIR`

`cmake --build $PATH_TO_BUILD_DIR`

### Running the cli utility

The cli binary will be available in your build directory under `$PATH_TO_BUILD_DIR/bin/intent_extractor`. The process 
will read from stdin/cin and reply to your queries as per instructions. E.g.:

```
How may I help you today?
> What is the weather Today?
Intent: Get Weather TimeDate:Today

How may I help you today?
> 
```

## Description

This project uses a simple keyword search to locate trigger words for intents. Once the intent has been located it can 
further analyse the tokens for more useful/contextual information.

The input text is processed by a tokenizer which:
* Transforms everything to lowercase 
* Ignores punctuation 
* Removes "filler" words (e.g: the, a, etc)
* Optionally performs some form of stemming

Once we have all the tokens we look for the first we look for a matching keyword that corresponds to an intent. This
approach is very simplistic and limited. It can reply to some queries with useful information, but to further extend 
its usefulness, other more advanced method should be employed such as Naive Bayes or some form of machine learning. 

Intents can be registered at startup, so it is possible to add new behavior later. This could be potentially be turned
into a plugin based system. The current system should work as in on Unix with GCC/CLANG, but on Windows with MSVC some
changes might be required to the interfaces due to platform local limitations. 

All string as internalized to enable us to perform fast string comparisons, since we this is a quite common operation.

### Included Intent Recognizers
Please consult the implementation of each intent in `intents` folder for more details.
#### Weather
Is triggered by keywords `weather` and `temperature`. Will also try to locate information about the date/time and the 
location.
```
How may I help you today?
> What is the weather Today?
Intent: Get Weather TimeDate:Today

How may I help you today?
> In Paris what are the temperatures?
Intent: Get Weather Location:Paris
```

### Facts
Is triggered by the keyword `fact`. Will also use simplistic search to try to find a related subject, if said subject is
located after the keyword. 

```
How may I help you today?
> What are some facts about birds?
Intent: Get Fact Subject:birds
```