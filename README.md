# Mesh Simplification

This is the Final Project for Computer Graphics.

## Usage

### Requirements

No special requirements. All third-party source codes are already included in this project.

### Compile

Simply type

    $ make 

add everything is done.

### Usage

    ./ms <input> <output> <percentage> [-mid]

Please specify the `input` and `output` file path (.obj files ONLY) and the percentage you want to simplify:
    
    percentage = number of planes(faces) AFTER simplifing / number of planes(faces) BEFORE simplifing

The `-mid` option means you want to use the middle point as estimatation(say the following sections for more details about the algorithm).

## Features

- Using quadrics for better topology stay.

- When estimate the new vertex v from two original vertices v1 and v2, we can use linear optimizing for better estimate.

- Using priorty queue to manage pairs to ensure low time complexity.
