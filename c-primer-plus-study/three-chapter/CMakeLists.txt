add_library(
        three-chapter 
        Platinum.c Platinum.h 
        Print1.c Print1.h
        Bases.c Bases.h
        TooBig.c TooBig.h
        Print2.c Print2.h
        ExecTest.c
        )

add_executable(ThreeChapter ExecTest.c)