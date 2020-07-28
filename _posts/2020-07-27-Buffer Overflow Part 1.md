---
sha256hash: 
  - e1d4b9013107c0247d406430107eed8cfde5f3b0e2bb37e2695e20f96626fa75
  - cfb5bed96a7f22460fac2af79b1d7936d705a4ae81d3a940681d7674072b447a
  - 7f4973078e4de9f9a2bc3941328c133aefd75a7b61ffcc3779e6ae663703b3fa
  - 7280da191b0afedb88b749fd3eb8d192494a39e4a8a52a4d5408112a3b48a2c5
tags: buffer-overflow assignment
aside:
  toc: true
sidebar:
  nav: layouts
excerpt_separator: <!--more-->
author: jsahil730
key: assignment000002
---

Oh hey, welcome to the world of Buffer Overflows. Let's embark on our journey
to the world of binaries with the most basic exploits ever - Stack Overflows.
We'll learn a lot of stuff, including totally ~~useless~~ awesome assembly, and
how binaries work :wink:
<!--more-->

Oh I hope you know what are buffer overflows, for if you don't head over to the [Bin-Exp]({{ site.baseurl }}{% post_url 2020-07-23-Binary Exploitation %}) please.

And if you're not familiar with assignments on this wiki, head over to [what are assignments]({{ site.baseurl }}{% post_url 2038-07-17-what are assignments %}).

First things first, encounter a few tasks(totally on stack overflows), read their source codes and use your brains to get the flag :)

## Task 1
Yo, here we begin with the basics, identify a buffer overflow(BOF) and find out how
to get the flag. 

Find the relevant files at [bof1](https://github.com/CSEA-IITB/IITBreachers-wiki/tree/master/assignments/Buffer Overflow Part 1/bof1) and connect to service using netcat to 34.238.150.251 at port 3333 by using command `nc 34.238.150.251 3333`{:.info}

{% assign index = 0 %}

{% include checkflag.html %}

## Task 2
Oh, this task takes things a little further, where you have to match the exact value to get the flag :) 

Find the relevant files at [bof2](https://github.com/CSEA-IITB/IITBreachers-wiki/tree/master/assignments/Buffer Overflow Part 1/bof2) and connect at `nc 34.238.150.251 3334`{:.info}

{% assign index = 1 %}

{% include checkflag.html %}

## Task 3
Here you have to worry about endianness :D

Find the relevant files at [bof3](https://github.com/CSEA-IITB/IITBreachers-wiki/tree/master/assignments/Buffer Overflow Part 1/bof3) and connect at `nc 34.238.150.251 3335`{:.info}

{% assign index = 2 %}

{% include checkflag.html %}

## Task 4
Can you alter the execution of the program to call the win function?

Find the relevant files at [bof4](https://github.com/CSEA-IITB/IITBreachers-wiki/tree/master/assignments/Buffer Overflow Part 1/bof4) and connect at `nc 34.238.150.251 3336`{:.info}

{% assign index = 3 %}

{% include checkflag.html %}