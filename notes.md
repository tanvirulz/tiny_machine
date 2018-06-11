# Notes

I think it is a good Idea to note down some of the programming tricks
that I learn while working on this project. Also, any interesting 
reading material related to this work will be saved here. 

## Programming Tricks

### Binary file loading in C

If you want to save the content of a binary file into an array. You would
first need to allocate memory for it. To get the size of the file in
bytes the following c tricks would work. 


    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);

To seek back:

    fseek(fp, 0L, SEEK_SET);

To go bak all they to the beginning:

    rewind(fp);

### `printf()` string concatenation

You can concatanate string literals by just placing them side by side
inside the `printf()` function. 

    printf("pc a" " survived!!\n");

Here `"pc a"` and `"survived!!\n"` are two different string literals. 

## Reading

## General


