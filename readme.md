### This is just a basic implementation of a web request DLL(Dynamic Link Library) using C.

### It is designed to facilitate web request within MQL5. I built to because i didn't understand how the web request library works in MQL5.

### This dll should work on other programming languages.

## Installation

### To install this DLL on windows run this command in the root directory

> g++ -shared -o webRequest.dll webRequest.cpp -lws2_32

## Usage

### Place the DLL file in your MQL5 project folder and import the DLL

### Import DLL

<pre>
#import "webRequest.dll"
    int WebRequestGet();
    int WebRequestPost(float a, float b, float c);
#import

## Make web request
float post_request = WebRequestPost(2.0435, 1.0231, 5.0422)
float get_request = WebRequestGet()
<pre>

## In this DLL request urls are hard coded. You can check it out and make updates to the code.
