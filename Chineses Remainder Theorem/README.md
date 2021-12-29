How to use generator.cpp:

# Generate checker
1) Generate .exe file from [GeneralCRT.cpp](https://github.com/ppap-1264589/interesting-solution/blob/main/Chineses%20Remainder%20Theorem/GeneralCRT.cpp), using your IDE

2) Copy .exe file into a project's directory where you want to generate testcases

3) Rename the .exe file with the "Task name" you want to generate.

# Generate testcases
1) Make sure you are working on project which is contain checker (.exe file), using code from [test_generator.cpp](https://github.com/ppap-1264589/interesting-solution/blob/main/Chineses%20Remainder%20Theorem/test_generator.cpp)
2) Enter your "Task name" on line ```18```

   Your "Task name" must have the same name as .exe file you have copied into your project's directory
   
3) Enter how many testcases you want to generate on line ```184```, it is ```maxtest```.


4) Finally, testcases would be writen in the same project's directory, with ```maxtest``` folders, each folder have an .inp file and an .out file, named by your "Task name".
