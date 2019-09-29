# @Author: AnthonyKenny98
# @Date:   2019-09-29 09:45:16
# @Last Modified by:   AnthonyKenny98
# @Last Modified time: 2019-09-29 10:09:46


# Iterate through directories within /Writeups
for dir in */; do

    # Change into that subdirectory
    cd "$dir"

    # Make all .tex files in dubdirectory
    for texFile in *.tex; do
        echo 'making '$texFile
        make foo=$texFile >>/dev/null
    done

    # Return to /Writeups directory
    cd ..
done
