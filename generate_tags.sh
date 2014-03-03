#!/bin/sh
find . | grep ".*\.\(h\|c\)" | xargs etags -f TAGS
