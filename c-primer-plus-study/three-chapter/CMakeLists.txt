add_library(
        three-chapter 
        Platinum.c Platinum.h 
        Print1.c Print1.h
        Bases.c Bases.h
        TooBig.c TooBig.h
        Print2.c Print2.h
        CharCode.c CharCode.h
        AltNames.c AltNames.h
        ExecTest.c
        )

add_executable(ThreeChapter ExecTest.c)