#!/bin/bash
date=`date +%Y-%m-%d_%H%M%S`
mkdir ${date}
mv *.log ${date}
mv *.log.wf ${date}
gzip ${date}/*
