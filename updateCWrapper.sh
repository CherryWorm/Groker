#!/bin/bash

test -d lib/c/ailib || rm -rf lib/c/ailib
mkdir -p lib/c/ailib

cp -v ../Turnierserver/CAiLibrary/build/*.so lib/c/ailib/
cp -v ../Turnierserver/CAiLibrary/*.h lib/c/ailib/

