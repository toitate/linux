#!/bin/sh

# arg 0 is comment of commit

git add .
git commit -m "$0"
git push origin master
