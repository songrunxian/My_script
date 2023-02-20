library(tidyverse)
library(readr)

file_list <- system( "ls *.count", intern=TRUE )
merge_df <- read_delim(file_list[1], delim = "\t", escape_double = FALSE,comment = "#", trim_ws = TRUE)
write.table(merge_df, "./file1.txt", sep = "\t")
for (i in 2:length(file_list)) {
	temp_df <- read_delim(file_list[i], delim = "\t", escape_double = FALSE,comment = "#", trim_ws = TRUE)
	write.table(temp_df, "./file2.txt", sep = "\t")
	merge_df <- left_join(merge_df, temp_df, by="geneid")
}
write.table(merge_df, "./file.txt", sep = "\t")
