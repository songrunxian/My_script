#!/bin/bash
#

sort <(cut -d '-' -f 1 <(cut -f 1 chrM_1.gff)) | uniq > gnlist

pre=${1%.bam}
filename=${pre}.count
samtools view ${1} > tmpfile
count=0
echo "# Program:quantitative.sh v1.0.0;" >> ${filename}
echo "geneid	${1}" >> ${filename}
for i in `cat gnlist`;do
	count=`grep -c ${i} <(cut -f 3 tmpfile)`
	echo "${i}	${count}" >> ${filename}
	count=0
done

rm gnlist tmpfile
