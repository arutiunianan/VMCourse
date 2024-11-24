#define POP_STK() stack.Pop()
#define PUSH_STK(num) stack.Push(num)

DEF_CMD(HLT, 0, 0, {
        printf("\nend\n");
        return 0;
    }
)

DEF_CMD(PUSH, 1, 1, {
        PUSH_STK(GetValidArgument(arg_type, instr));
    }
)

DEF_CMD(POP, 2, 1, {
        Elem_t num = POP_STK();
        SetReg(instr.arg, num);
    }
)
 
DEF_CMD(ADD, 3, 0, {
        Elem_t val1 = POP_STK();
        Elem_t val2 = POP_STK();
        PUSH_STK(val1 + val2);
    }
)

DEF_CMD(MUL, 4, 0, {
        Elem_t val1 = POP_STK();
        Elem_t val2 = POP_STK();
        PUSH_STK(val1 * val2);
    }
)

DEF_CMD(SUB, 5, 0, {
        Elem_t val1 = POP_STK();
        Elem_t val2 = POP_STK();
        PUSH_STK(val2 - val1);
    }
)

DEF_CMD(DIV, 6, 0, {
        Elem_t val1 = POP_STK();
        Elem_t val2 = POP_STK();
        PUSH_STK(val2 / val1);
    }
)

DEF_CMD(SQRT, 7, 0, {
        Elem_t val = POP_STK();
        PUSH_STK(sqrt(val));
    }
)

DEF_CMD(OUT, 9, 0, {
        Elem_t num = POP_STK();
        std::cout << num;
    }
)

DEF_CMD(IN, 10, 0, {
        Elem_t num = 0;
        printf("IN: ");
        if( scanf("%lf", &num) != 1)
        {
            //SetErrorBit(&cpu_log->errors, CPU_WRONG_INPUT);
        }
        PUSH_STK(num);
    }
)

DEF_CMD(JMP, 12, 1,
    current_line = GetValidArgument(arg_type, instr) - 1;
)

DEF_CMD(JA, 13, 1, {
        Elem_t num1 = POP_STK();
        Elem_t num2 = POP_STK();
        if(num1 > num2)
        {
            current_line = GetValidArgument(arg_type, instr) - 1;
        }
    }
)

DEF_CMD(JB, 14, 1, {
        Elem_t num1 = POP_STK();       
        Elem_t num2 = POP_STK();         
        if(num1 < num2)      
        {
            current_line = GetValidArgument(arg_type, instr) - 1;
        }
    }
)

DEF_CMD(JAE, 15, 1, {
        Elem_t num1 = POP_STK();       
        Elem_t num2 = POP_STK();            
        if(num1 >= num2)      
        {
            current_line = GetValidArgument(arg_type, instr) - 1;
        }
    }
)

DEF_CMD(JBE, 16, 1, {
        Elem_t num1 = POP_STK();       
        Elem_t num2 = POP_STK();            
        if(num1 <= num2)      
        {
            current_line = GetValidArgument(arg_type, instr) - 1;
        }
    }
)

DEF_CMD(JE, 17, 1, {
        Elem_t num1 = POP_STK();       
        Elem_t num2 = POP_STK();
        if(num1 == num2)
        {
            current_line = GetValidArgument(arg_type, instr) - 1;
        }
    }
)

DEF_CMD(JNE, 18, 1, {
        Elem_t num1 = POP_STK();       
        Elem_t num2 = POP_STK();
        if(num1 != num2) {
            current_line = GetValidArgument(arg_type, instr) - 1;
        }
    }
)

DEF_CMD(CALL, 19, 1, {
        PUSH_STK(current_line);
        current_line = GetValidArgument(arg_type, instr) - 1;
    }
)

DEF_CMD(RET, 20, 0,
    if (stack.get_size() >= 1) {
        Elem_t ret_address = POP_STK();
        current_line = (int)ret_address;
    }
)

DEF_CMD(OUTC, 21, 0,
    if (stack.get_size() >= 1) {
        Elem_t num_to_output = POP_STK();
        printf("%c", (char)num_to_output);
    }
)

#undef DEF_CMD

#undef POP_STK
#undef PUSH_STK