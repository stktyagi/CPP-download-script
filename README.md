# CPP-download-script

This is a simple C++ program to download files from a URL using libcurl. It demonstrates how to use libcurl to perform HTTP GET requests and save the downloaded content to a file.

## Prerequisites

Before running the program, make sure you have the following installed:

- C++ compiler
- libcurl library

## Installation

1. Clone this repository to your local machine:

2. Compile the program using a C++ compiler. For example:

3. Run the compiled executable, providing the URL of the file to download and the path of the output file as command-line arguments.


## Usage

To use the program, simply run the compiled executable with the URL of the file you want to download and the path where you want to save the downloaded file. For example(linux specific):

$ g++ -o download_video main.cpp -lcurl 

$ ./download_video
